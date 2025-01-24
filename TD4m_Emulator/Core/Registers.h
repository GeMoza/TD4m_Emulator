#pragma once

#include "../Logging/Logger.h"
#include "../Config/config.h"
#include "CommandBase.h"

using System::Byte;

public ref class Registers {
public:
    property Byte A {
        Byte get() { return a; }
        void set(Byte value) {
            if (value > MAX_VALUE_4BIT) {
                logger->LogRangeError("A", MAX_VALUE_4BIT);
            }
            a = value;
        }
    }

    property Byte B {
        Byte get() { return b; }
        void set(Byte value) {
            if (value > MAX_VALUE_4BIT) {
                logger->LogRangeError("B", MAX_VALUE_4BIT);
            }
            b = value;
        }
    }

    property Byte PC {
        Byte get() { return pc; }
        void set(Byte value) {
            if (value > MAX_VALUE_8BIT) {
                logger->LogRangeError("PC", MAX_VALUE_8BIT);
            }
            pc = value;
        }
    }

    property Byte XY {
        Byte get() { return xy; }
        void set(Byte value) {
            if (value > MAX_VALUE_8BIT) {
                logger->LogRangeError("XY", MAX_VALUE_8BIT);
            }
            xy = value;
        }
    }

    property Byte OUTP {
        Byte get() { return out; }
        void set(Byte value) {
            if (value > MAX_VALUE_4BIT) {
                logger->LogRangeError("OUT", MAX_VALUE_4BIT);
            }
            out = value;
        }
    }

    // Методы для работы с двумя 4-битными значениями в XY
    Byte GetXYHigh() { return (xy >> 4) & 0xF; }
    Byte GetXYLow() { return xy & 0xF; }

    void SetXYHigh(Byte value) {
        if (value > MAX_VALUE_4BIT) {
            logger->LogRangeError("High nibble of XY", MAX_VALUE_4BIT);
        }
        xy = (xy & 0x0F) | (value << 4);
    }

    void SetXYLow(Byte value) {
        if (value > MAX_VALUE_4BIT) {
            logger->LogRangeError("Low nibble of XY", MAX_VALUE_4BIT);
        }
        xy = (xy & 0xF0) | (value & 0xF);
    }

    // Массив значений ввода (каждое значение — 4 бита)
    property array<Byte>^ INP {
        array<Byte>^ get() { return in; }
        void set(array<Byte>^ values) {
            if (values != nullptr) {
                for each (Byte value in values) {
                    if (value >= MAX_VALUE_4BIT) {
                        logger->LogRangeError("in", MAX_VALUE_4BIT);
                    }
                }
            }
            in = values;
        }
    }

    // Метод для обновления количества полей ввода
    void UpdateInputFields(int count) {
        if (count < 0) {
            logger->LogRangeError("in", MAX_VALUE_4BIT);
        }
        in = gcnew array<Byte>(count);
        logger->Log("Input fields updated. New count: " + count);
    }

    Registers(Logger^ log) : logger(log) {
        Reset(true);
    }

    void Reset(bool inputs) {
        A = 0;
        B = 0;
        PC = 0;
        XY = 0;
        OUTP = 0;
        currentIn = 0;
        Z = false;
        C = false;
        if (inputs) {
            in = gcnew array<Byte>(0);
        }
    }

    property bool Z;    // Флаг обнуления
    property bool C;    // Флаг переполнения

    property System::Int16 currentIn;
protected:
    Byte a;   // Внутреннее поле для регистра A
    Byte b;   // Внутреннее поле для регистра B
    Byte pc;  // Внутреннее поле для регистра PC
    Byte xy;  // Внутреннее поле для регистра XY
    Byte out; // Регистр OUT
    array<Byte>^ in; // Массив для значений ввода
    Logger^ logger; // Ссылка на Logger
};
