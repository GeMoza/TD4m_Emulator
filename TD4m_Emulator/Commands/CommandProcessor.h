// Commands/CommandProcessor.h

#pragma once

#include "Commands.h"

using namespace System;
using namespace System::Collections::Generic;

ref class CommandProcessor {
public:
    CommandProcessor(Registers^ reg, Memory^ mem, Logger^ log, String^ commandsPath);

    Command^ GetCommand(Byte code);
    Command^ GetCommand(String^ mnemonic);

    Byte GetCode(String^ mnemonic);
    String^ GetMnemonic(Byte code);

    bool IsValidCommand(Byte code);
    bool IsValidCommand(String^ mnemonic);

protected:
    void Initialize(String^ commandsPath);
    Command^ ParseCommand(Byte code, String^ mnemonic);

    // Словари
    Dictionary<Byte, Command^>^ codeToCommand;       // Словарь команд по коды
    Dictionary<String^, Byte>^ mnemonicToCode;       // Словарь кодов по мнемонике
    //Dictionary<String^, IntPtr>^ registerMap;        // Словарь поддерживаемых переменных

    Registers^ registers;
    Memory^ memory;
    Logger^ logger;

public:

    short BinaryStringToShort(String^ binaryStr);
};