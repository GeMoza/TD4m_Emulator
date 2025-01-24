// Core/Memory.cpp

#include "Memory.h"

using namespace System;

Memory::Memory(UInt16 romSize, UInt16 ramSize) {
    ROM = gcnew array<Byte>(romSize);
    RAM = gcnew array<Byte>(ramSize);
    Reset();
}

Byte Memory::ReadROM(Byte address) {
    if (address < 0 || address >= ROM->Length) {
        throw gcnew ArgumentOutOfRangeException("address", "ROM address out of range");
    }
    return ROM[address];
}

void Memory::WriteROM(Byte address, Byte value) {
    if (address < 0 || address >= ROM->Length) {
        throw gcnew ArgumentOutOfRangeException("address", "ROM address out of range");
    }
    ROM[address] = value;
}

Byte Memory::ReadRAM(Byte address) {
    if (address < 0 || address >= RAM->Length) {
        throw gcnew ArgumentOutOfRangeException("address", "RAM address out of range");
    }
    return RAM[address];
}

void Memory::WriteRAM(Byte address, Byte value) {
    if (address < 0 || address >= RAM->Length) {
        throw gcnew ArgumentOutOfRangeException("address", "RAM address out of range");
    }
    RAM[address] = value;
}

void Memory::Reset() {
    Array::Clear(ROM, 0, ROM->Length);
    Array::Clear(RAM, 0, RAM->Length);
}