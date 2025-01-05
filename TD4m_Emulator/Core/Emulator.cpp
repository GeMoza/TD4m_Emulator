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

    // ������������� ���������
    registers = gcnew Registers(logger);

    // ������������� ������
    memory = gcnew Memory(romSize, ramSize);

    // ������������� ����������� ������
    commandProcessor = gcnew CommandProcessor(registers, memory, logger, commandsPath);

    // ����� ���������
    Reset();

    logger->Log("Emulator initialized successfully.");
}


void Emulator::Execute(String^ operation) {
    logger->Log("Executing operation: " + operation);

    // ��������� ������� �� �����������
    Command^ command = commandProcessor->GetCommand(operation);
    if (command == nullptr) {
        logger->Log("Invalid operation: " + operation);
        return;
    }

    // ���������� �������
    ExecuteCommand(command);

    // ���������� �������� ������ (���� ���������)
    registers->PC++;
}


void Emulator::Execute(Byte code) {
    logger->Log("Executing operation with code: " + code);

    // ��������� ������� �� �����������
    Command^ command = commandProcessor->GetCommand(code);
    if (command == nullptr) {
        logger->Log("Invalid operation code: " + code);
        return;
    }

    // ���������� �������
    ExecuteCommand(command);

    // ���������� �������� ������ (���� ���������)
    registers->PC++;
}


void Emulator::Reset() {
    logger->Log("Resetting emulator...");

    // ����� ���������
    registers->Reset();

    // ����� ������
    memory->Reset();

    logger->Log("Emulator reset successfully.");
}


void Emulator::ExecuteCommand(Command^ command) {
    try {
        command->Execute(); // ����� ������ Execute �������
        logger->Log("Command executed successfully.");
    }
    catch (Exception^ ex) {
        logger->Log("Error executing command: " + ex->Message);
    }
}




void Emulator::SaveToFile(String^ filePath) {
    logger->Log("Saving emulator state to file: " + filePath);

    // ����������� ���� � ������ std::string
    std::string nativePath = marshal_as<std::string>(filePath);

    try {
        // �������� ���������� �����
        String^ extension = Path::GetExtension(filePath)->ToLower();

        if (extension == ".txt" || extension == ".hex" || extension == ".hxd") {
            std::ofstream outFile(nativePath);

            if (!outFile.is_open()) {
                throw gcnew IOException("Failed to open file for writing.");
            }

            // ��������� ������ ��� (ROM) � ����������������� ����
            for (Byte i = 0; i < memory->ROMLength; i++) {
                outFile << std::hex << std::uppercase
                    << static_cast<int>(memory->ReadROM(i)) << " ";
                if ((i + 1) % 16 == 0) {
                    outFile << std::endl; // ���������� ����� ��� �������� ������
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

    // ����������� ���� � ������ std::string
    std::string nativePath = marshal_as<std::string>(filePath);

    try {
        // �������� ���������� �����
        String^ extension = Path::GetExtension(filePath)->ToLower();

        if (extension == ".txt" || extension == ".hex" || extension == ".hxd") {
            std::ifstream inFile(nativePath);

            if (!inFile.is_open()) {
                throw gcnew IOException("Failed to open file for reading.");
            }

            // ������ ������ ��� (ROM)
            Byte address = 0;
            std::string hexValue;
            while (inFile >> hexValue) {
                if (address >= memory->ROMLength) {
                    throw gcnew IOException("File contains more data than ROM capacity.");
                }

                // �������������� �� ����������������� ������ � Byte
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