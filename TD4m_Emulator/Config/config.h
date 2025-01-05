#include <iostream>

#pragma once

/// <summary>
/// Файл конфигурации
/// </summary>

using namespace System;

// Глобальные переменные
ref class Globals
{
public:
	static System::Drawing::Color BlackColor = System::Drawing::Color::Black;
	static System::Drawing::Color RedColor = System::Drawing::Color::Red;
};

std::string COMMANDS_TAB = "CommandsTab.xlsx";
short ROM_CAPACITY = 256;
short RAM_CAPACITY = 256;

short MAX_VALUE_4BIT = 16;
short MAX_VALUE_8BIT = 256;