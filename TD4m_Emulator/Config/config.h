#include <iostream>

#pragma once

/// <summary>
/// Файл конфигурации
/// </summary>

// Глобальные переменные
ref class Globals
{
public:
	static System::Drawing::Color BlackColor = System::Drawing::Color::Black;
	static System::Drawing::Color RedColor = System::Drawing::Color::Red;
};

constexpr const char* COMMANDS_TAB = "CommandsTab.xlsx";
constexpr short ROM_CAPACITY = 256;
constexpr short RAM_CAPACITY = 256;

constexpr short MAX_VALUE_4BIT = 16;
constexpr short MAX_VALUE_8BIT = 256;