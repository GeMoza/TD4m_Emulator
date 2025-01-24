// Commands/CommandBase.h

#pragma once

#include "../Core/Registers.h"
#include "../Core/Memory.h"
#include "../Logging/Logger.h"

public ref class Command abstract {
protected:
    Registers^ registers;
    Memory^ memory;
    Logger^ logger;

public:
    Command(Registers^ reg, Memory^ mem, Logger^ log) : registers(reg), memory(mem), logger(log) {}

    // Выполнить команду
    virtual void Execute() = 0;

    // Разрушитель (*≧▽≦)
    virtual ~Command() {}

};