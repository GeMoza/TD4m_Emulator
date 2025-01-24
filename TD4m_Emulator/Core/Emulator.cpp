// Core/Emulator.cpp

#pragma once

#include "Emulator.h"
#include <fstream>
#include <iomanip>
#include <msclr/marshal_cppstd.h>

using namespace System;
using namespace System::IO;
using namespace msclr::interop;


Emulator::Emulator(UInt16 romSize, UInt16 ramSize, String^ commandsPath, Logger^ log) {
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
    /*Command^ command = commandProcessor->GetCommand(code);
    if (command == nullptr) {
        logger->Log("Invalid operation code: " + code);
        return;
    }*/

    if (true) { // временное решение для тестирования интерфейса
        // ---------------------------------------------------------------------------
        Byte major = code >> 4;
        Byte im    = code & 0xF;
        bool Z     = true;
        // результат по-умолчанию, включающий флаг
        Byte result = 0;
        switch (major) {
        case 0b0000: // ADD A, Im
            result = registers->A + im;
            registers->A = result & 0xF;
            break;
        case 0b0001: // MOV A, B  и  ADD A,B,N
            result = registers->B + im;
            registers->A = result & 0xF;
            Z = im;
            break;
        case 0b0010: // IN A  и  IN A+N
            result = registers->INP[registers->currentIn] + im;
            registers->A = result & 0xF;
            registers->currentIn = (registers->currentIn + 1) % registers->INP->Length;
            Z = im;
            break;
        case 0b0011: // MOV A,Im
            registers->A = im & 0xF;
            Z = 0;
            break;
        case 0b0100: // MOV B,A  и  ADD B,A,N
            result = registers->A + im;
            registers->B = result & 0xF;
            Z = im;
            break;
        case 0b0101: // ADD B, Im
            result = registers->B + im;
            registers->B = result & 0xF;
            Z = im;
            break;
        case 0b0110: // IN B  и  IN B+N
            result = registers->INP[registers->currentIn] + im;
            registers->B = result & 0xF;
            registers->currentIn = (registers->currentIn + 1) % registers->INP->Length;
            Z = im;
            break;
        case 0b0111: // MOV B, Im
            registers->B = im;
            break;
        case 0b1000:
            switch (im) {
            case 0b0000: // ADD A, B
                result = registers->A + registers->B;
                registers->A = result & 0xF;
                break;
            case 0b0001: // NEG A
                result = ((unsigned)(-registers->A)) & 0xF;
                registers->A = result;
                break;
            case 0b0010: // NOT A
                result = ~registers->A;
                registers->A = result & 0xF;
                break;
            case 0b0011: // OR A, B
                result = registers->A | registers->B;
                registers->A = result;
                break;
            case 0b0100: // AND A, B
                result = registers->A & registers->B;
                registers->A = result;
                break;
            case 0b0101: // XOR A, B
                result = registers->A ^ registers->B;
                registers->A = result;
                break;
            case 0b0110: // SUB A, B
                result = registers->A - registers->B;
                registers->A = result & 0xF;
                break;
            case 0b0111: // OUT A
                registers->OUTP = registers->A;
                Z = 0;
                break;
            case 0b1000: // LD A
                registers->A = memory->ReadRAM(registers->XY);
                Z = 0;
                break;
            case 0b1001: // ST A
                memory->WriteRAM(registers->XY, registers->A);
                Z = 0;
                break;
            case 0b1010: // LD B
                registers->B = memory->ReadRAM(registers->XY);
                Z = 0;
                break;
            case 0b1011: // ST B
                memory->WriteRAM(registers->XY, registers->B);
                Z = 0;
                break;
            case 0b1100: // MOV X, A
                registers->SetXYHigh(registers->A);
                Z = 0;
                break;
            case 0b1101: // MOV Y, A
                registers->SetXYLow(registers->A);
                Z = 0;
                break;
            case 0b1110: // INC XY
                registers->XY++;
                Z = 0;
                break;
            case 0b1111: // JMP XY
                registers->PC = registers->XY;
                return; // Прервать без изменения других регистров
            }
            break;
        case 0b1001: // OUT B  и  OUT B+N
            registers->OUTP = registers->B + im;
            Z = 0;
            break;
        case 0b1010: // JZ Im
            if (registers->Z == 1) {
                registers->PC = (registers->PC & 0xF0) | im;
            }
            else {
                registers->PC++;
            }
            return; // Прервать без изменения других регистров
        case 0b1011: // OUT Im
            registers->OUTP = im;
            Z = 0;
            break;
        case 0b1100: // MOV Y, Im
            registers->SetXYLow(im);
            Z = 0;
            break;
        case 0b1101: // MOV X, Im
            registers->SetXYHigh(im);
            Z = 0;
            break;
        case 0b1110: // JNC Im
            if (registers->C == 0) {
                registers->PC = (registers->PC & 0xF0) | im;
            }
            else {
                registers->PC++;
            }
            return; // Прервать без изменения других регистров
        case 0b1111: // JMP Im
            registers->PC = (registers->PC & 0xF0) | im;
            logger->Log("Jump to " + registers->PC.ToString());
            return; // Здесь тоже
        }
        registers->C = (result & 0xF0) != 0;
        registers->Z = (result & 0xF) == 0 && Z;
        // ------------------------------------------------------------------------------
    }
    else {
        // Выполнение команды
        //ExecuteCommand(command);
    }

    // Увеличение счетчика команд (если требуется)
    registers->PC++;
}


void Emulator::Reset() {
    logger->Log("Resetting emulator...");

    // Сброс регистров
    registers->Reset(true);

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
            for (Int16 i = 0; i < memory->ROMLength; i++) {
                outFile << std::setw(2) << std::setfill('0') << std::hex << std::uppercase
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