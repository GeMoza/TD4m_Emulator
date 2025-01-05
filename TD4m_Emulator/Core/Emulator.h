// Core/Emulator.h

#pragma once

#include "../Commands/CommandProcessor.h"

using namespace System;

ref class Emulator {
public:
	Emulator(Byte romSize, Byte ramSize, String^ commandsPath, Logger^ log);

	void Execute(String^ operation);
	void Execute(Byte code);

	void Reset();

    void SaveToFile(String^ filePath);
    void LoadFromFile(String^ filePath);


    // Методы для доступа к полям
    Registers^ GetRegisters() { return registers; }
    void SetRegisters(Registers^ value) { registers = value; }

    Memory^ GetMemory() { return memory; }
    void SetMemory(Memory^ value) { memory = value; }

    Logger^ GetLogger() { return logger; }
    void SetLogger(Logger^ value) { logger = value; }

    CommandProcessor^ GetCommandProcessor() { return commandProcessor; }
    void SetCommandProcessor(CommandProcessor^ value) { commandProcessor = value; }

protected:
    Registers^ registers;
    Memory^ memory;
    CommandProcessor^ commandProcessor;
    Logger^ logger;

    void ExecuteCommand(Command^ command);
};