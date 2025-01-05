// Commands/CommandProcessor.cpp

#pragma once

#include "CommandProcessor.h"
#include <fstream>
#include <msclr/marshal_cppstd.h>

using namespace System;
using namespace msclr::interop;
using namespace System::Text::RegularExpressions;
using namespace System::Data::OleDb;
using namespace System::Data;

CommandProcessor::CommandProcessor(Registers^ reg, Memory^ mem, Logger^ log, String^ commandsPath)
    : registers(reg), memory(mem), logger(log) {
    // Инициализация словарей
    codeToCommand = gcnew Dictionary<Byte, Command^>();
    mnemonicToCode = gcnew Dictionary<String^, Byte>();

    // Вызов инициализации
    Initialize(commandsPath);
}

void CommandProcessor::Initialize(String^ filePath) {
    // Строка подключения для работы с .xlsx файлами
    String^ connectionString = "Provider=Microsoft.ACE.OLEDB.12.0;Data Source=" + filePath + ";Extended Properties='Excel 12.0 Xml;HDR=YES;IMEX=1';";
    OleDbConnection^ connection = gcnew OleDbConnection(connectionString);

    try {
        connection->Open();
        String^ query = "SELECT * FROM [Sheet1$]"; // Укажите имя листа Excel
        OleDbCommand^ command = gcnew OleDbCommand(query, connection);
        OleDbDataAdapter^ adapter = gcnew OleDbDataAdapter(command);
        DataTable^ table = gcnew DataTable();
        adapter->Fill(table);

        logger->Log("Parsing commands from Excel file: " + filePath);

        // Чтение строк начинается с 3 строки (индексация с 0, поэтому i = 2)
        for (int i = 2; i < table->Rows->Count; i++) {
            DataRow^ row = table->Rows[i];

            // Проверяем, что строка содержит достаточно данных
            if (row->ItemArray->Length < 4) {
                logger->Log("Invalid row format at index " + i + ". Skipping...");
                continue;
            }

            String^ rawCode = row[1]->ToString();       // 2-й столбец, который может содержать "N" или "Im"
            Byte baseCode = static_cast<Byte>(BinaryStringToShort(row[2]->ToString())); // Код из 3-го столбца
            String^ mnemonic = row[3]->ToString();     // Мнемоника из 4-го столбца

            // Если код содержит "N" или "Im", обрабатываем как диапазон
            if (rawCode == "N" || rawCode == "Im") {
                for (Byte variant = 0; variant <= 15; variant++) {
                    Byte finalCode = (baseCode & 0xF0) | (variant & 0x0F); // Вставляем значение варианта в младшие биты
                    Command^ command = ParseCommand(finalCode, mnemonic);
                    if (command != nullptr) {
                        codeToCommand[finalCode] = command;
                        mnemonicToCode[mnemonic + variant.ToString()] = finalCode; // Например, "MOV0", "MOV1" и т.д.
                    }
                }
            }
            else {
                // Обычный код, не содержащий "N" или "Im"
                Byte finalCode = baseCode;
                Command^ command = ParseCommand(finalCode, mnemonic);
                if (command != nullptr) {
                    codeToCommand[finalCode] = command;
                    mnemonicToCode[mnemonic] = finalCode;
                }
            }
        }

        logger->Log("Command initialization from Excel completed.");
    }
    catch (Exception^ ex) {
        logger->LogAndThrow("ExcelError", "Failed to parse Excel file: " + ex->Message);
    }
    finally {
        connection->Close();
    }
}


Command^ CommandProcessor::ParseCommand(Byte code, String^ mnemonic) {
    logger->Log("Parsing command: Code=" + code + ", Mnemonic=" + mnemonic);

    // Определение команд с использованием классов из Commands.h
    if (mnemonic->StartsWith("ADD") || mnemonic->StartsWith("MOV") || mnemonic->StartsWith("IN") ||
        mnemonic->StartsWith("OUT") || mnemonic->StartsWith("LD") || mnemonic->StartsWith("ST") ||
        mnemonic->StartsWith("INC")) {
        return gcnew CommandMAD(registers, memory, logger);
    }
    else if (mnemonic->StartsWith("JMP") || mnemonic->StartsWith("JZ") || mnemonic->StartsWith("JNC")) {
        return gcnew CommandMNA(registers, memory, logger);
    }
    else if (mnemonic->StartsWith("NEG") || mnemonic->StartsWith("SUB")) {
        return gcnew CommandNegSub(registers, memory, logger);
    }
    else if (mnemonic->StartsWith("NOT") || mnemonic->StartsWith("OR") ||
        mnemonic->StartsWith("AND") || mnemonic->StartsWith("XOR")) {
        return gcnew CommandLogic(registers, memory, logger);
    }

    // Если мнемоника не распознана
    logger->Log("Unknown mnemonic: " + mnemonic);
    return nullptr;
}


// Получение команды по коду
Command^ CommandProcessor::GetCommand(Byte code) {
    if (codeToCommand->ContainsKey(code)) {
        return codeToCommand[code];
    }
    logger->Log("Command not found for code: " + code);
    return nullptr;
}

// Получение команды по мнемонике
Command^ CommandProcessor::GetCommand(String^ mnemonic) {
    if (mnemonicToCode->ContainsKey(mnemonic)) {
        Byte code = mnemonicToCode[mnemonic];
        return GetCommand(code);
    }
    logger->Log("Command not found for mnemonic: " + mnemonic);
    return nullptr;
}

// Получение кода команды по мнемонике
Byte CommandProcessor::GetCode(String^ mnemonic) {
    if (mnemonicToCode->ContainsKey(mnemonic)) {
        return mnemonicToCode[mnemonic];
    }
    logger->Log("Code not found for mnemonic: " + mnemonic);
    return 0; // Возвращаем 0 в случае ошибки
}

// Получение мнемоники команды по её коду
String^ CommandProcessor::GetMnemonic(Byte code) {
    if (codeToCommand->ContainsKey(code)) {
        for each (KeyValuePair<String^, Byte> pair in mnemonicToCode) {
            if (pair.Value == code) {
                return pair.Key;
            }
        }
    }
    logger->Log("Mnemonic not found for code: " + code);
    return nullptr; // Возвращаем nullptr в случае ошибки
}

// Проверка валидности команды по коду
bool CommandProcessor::IsValidCommand(Byte code) {
    return codeToCommand->ContainsKey(code);
}

// Проверка валидности команды по мнемонике
bool CommandProcessor::IsValidCommand(String^ mnemonic) {
    return mnemonicToCode->ContainsKey(mnemonic);
}













short CommandProcessor::BinaryStringToShort(String^ binaryStr) {
    try {
        // Проверяем, что строка не пустая
        if (String::IsNullOrWhiteSpace(binaryStr)) {
            logger->Log("Binary string is empty or null.");
            return 0; // Возвращаем 0 в случае ошибки
        }

        // Преобразуем строку в число (двоичная система счисления)
        return Convert::ToInt16(binaryStr, 2);
    }
    catch (FormatException^) {
        logger->Log("Invalid binary string format: " + binaryStr);
        return 0; // Возвращаем 0 в случае ошибки
    }
    catch (OverflowException^) {
        logger->Log("Binary string is too large: " + binaryStr);
        return 0; // Возвращаем 0 в случае ошибки
    }
}
