// Commands/CommandProcessor.h

#pragma once

#include "Commands.h"

using System::String;
using System::Collections::Generic::Dictionary;

ref class CommandProcessor {
public:
    CommandProcessor(Registers^ reg, Memory^ mem, Logger^ log, String^ commandsPath);

    Command^ GetCommand(System::Byte code);
    Command^ GetCommand(System::String^ mnemonic);

    Byte GetCode(System::String^ mnemonic);
    String^ GetMnemonic(System::Byte code);

    bool IsValidCommand(System::Byte code);
    bool IsValidCommand(System::String^ mnemonic);

protected:
    void Initialize(System::String^ commandsPath);
    Command^ ParseCommand(System::Byte code, System::String^ mnemonic);

    // Словари
    Dictionary<System::Byte, Command^>^ codeToCommand;       // Словарь команд по коды
    Dictionary<System::String^, System::Byte>^ mnemonicToCode;       // Словарь кодов по мнемонике
    //Dictionary<String^, IntPtr>^ registerMap;        // Словарь поддерживаемых переменных

    Registers^ registers;
    Memory^ memory;
    Logger^ logger;

public:

    short BinaryStringToShort(System::String^ binaryStr);
};