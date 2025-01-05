// Core/Memory.h

#pragma once

using namespace System;

public ref class Memory {
public:
    Memory(Byte romSize, Byte ramSize);

    Byte ReadROM(Byte address);
    void WriteROM(Byte address, Byte value);

    Byte ReadRAM(Byte address);
    void WriteRAM(Byte address, Byte value);

    void Reset();

    // Свойство для длины ROM
    property int ROMLength{
        int get() { return ROM->Length; }
    }

        // Свойство для длины RAM
        property int RAMLength{
            int get() { return RAM->Length; }
    }

protected:
    array<Byte>^ ROM;
    array<Byte>^ RAM;
};
