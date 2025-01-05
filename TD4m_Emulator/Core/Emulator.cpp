// Core/Emulator.cpp

#pragma once

#include "Emulator.h"
#include <fstream>
#include <msclr/marshal_cppstd.h>

using namespace System;
using namespace System::IO;
using namespace msclr::interop;


Emulator::Emulator(Byte romSize, Byte ramSize, String^ commandsPath, Logger^ log) {
    logger = log;
    logger->Log("Initializing emulator...");

    // Инициализация регистров
    registers = gcnew Registers(logger);

    // Инициализация памяти
    memory = gcnew Memory(romSize, ramSize);

    // Инициализация обработчика команд
    commandProcessor = gcnew CommandProcessor(registers, memory, logger, commandsPath);

    // Сброс состояния
    Reset();

    logger->Log("Emulator initialized successfully.");
}


void Emulator::Execute(String^ operation) {
    logger->Log("Executing operation: " + operation);

    // Получение команды из обработчика
    Command^ command = commandProcessor->GetCommand(operation);
    if (command == nullptr) {
        logger->Log("Invalid operation: " + operation);
        return;
    }

    // Выполнение команды
    ExecuteCommand(command);

    // Увеличение счетчика команд (если требуется)
    registers->PC++;
}


void Emulator::Execute(Byte code) {
    logger->Log("Executing operation with code: " + code);

    // Получение команды из обработчика
    Command^ command = commandProcessor->GetCommand(code);
    if (command == nullptr) {
        logger->Log("Invalid operation code: " + code);
        return;
    }

    // Выполнение команды
    ExecuteCommand(command);

    // Увеличение счетчика команд (если требуется)
    registers->PC++;
}


void Emulator::Reset() {
    logger->Log("Resetting emulator...");

    // Сброс регистров
    registers->Reset();

    // Сброс памяти
    memory->Reset();

    logger->Log("Emulator reset successfully.");
}


void Emulator::ExecuteCommand(Command^ command) {
    try {
        command->Execute(); // Вызов метода Execute команды
        logger->Log("Command executed successfully.");
    }
    catch (Exception^ ex) {
        logger->Log("Error executing command: " + ex->Message);
    }
}




void Emulator::SaveToFile(String^ filePath) {
    logger->Log("Saving emulator state to file: " + filePath);

    // Конвертация пути в формат std::string
    std::string nativePath = marshal_as<std::string>(filePath);

    try {
        // Проверка расширения файла
        String^ extension = Path::GetExtension(filePath)->ToLower();

        if (extension == ".txt" || extension == ".hex" || extension == ".hxd") {
            std::ofstream outFile(nativePath);

            if (!outFile.is_open()) {
                throw gcnew IOException("Failed to open file for writing.");
            }

            // Сохраняем данные ПЗУ (ROM) в шестнадцатеричном виде
            for (Byte i = 0; i < memory->ROMLength; i++) {
                outFile << std::hex << std::uppercase
                    << static_cast<int>(memory->ReadROM(i)) << " ";
                if ((i + 1) % 16 == 0) {
                    outFile << std::endl; // Разделение строк для удобства чтения
                }
            }

            outFile.close();
            logger->Log("Emulator state saved successfully.");
        }
        else {
            throw gcnew ArgumentException("Unsupported file extension: " + extension);
        }
    }
    catch (Exception^ ex) {
        logger->Log("Error saving to file: " + ex->Message);
    }
}


void Emulator::LoadFromFile(String^ filePath) {
    logger->Log("Loading emulator state from file: " + filePath);

    // Конвертация пути в формат std::string
    std::string nativePath = marshal_as<std::string>(filePath);

    try {
        // Проверка расширения файла
        String^ extension = Path::GetExtension(filePath)->ToLower();

        if (extension == ".txt" || extension == ".hex" || extension == ".hxd") {
            std::ifstream inFile(nativePath);

            if (!inFile.is_open()) {
                throw gcnew IOException("Failed to open file for reading.");
            }

            // Чтение данных ПЗУ (ROM)
            Byte address = 0;
            std::string hexValue;
            while (inFile >> hexValue) {
                if (address >= memory->ROMLength) {
                    throw gcnew IOException("File contains more data than ROM capacity.");
                }

                // Преобразование из шестнадцатеричной строки в Byte
                Byte value = static_cast<Byte>(std::stoi(hexValue, nullptr, 16));
                memory->WriteROM(address++, value);
            }

            inFile.close();
            logger->Log("Emulator state loaded successfully.");
        }
        else {
            throw gcnew ArgumentException("Unsupported file extension: " + extension);
        }
    }
    catch (Exception^ ex) {
        logger->Log("Error loading from file: " + ex->Message);
    }
}