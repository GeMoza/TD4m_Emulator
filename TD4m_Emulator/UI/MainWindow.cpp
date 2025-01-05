// UI/MainWindow.cpp

#pragma once

#include "MainWindow.h"

#include <msclr/marshal_cppstd.h>
#include <fstream>
#include <string>
#include <regex>

using namespace System::Windows::Forms;
using namespace msclr::interop;
using namespace System::IO;


// Инициализаци
System::Void TD4mEmulator::MainWindow::Initialize()
{
	// Установить для tSCB_clockGenerator_mode три положения и ReadOnly
	// Отрисовать поля ввода

    // Инициализация эмулятора
    mEm = gcnew Emulator(256, 256, "commands.xlsx", gcnew Logger("log.txt"));

    // Инициализация диалогового окна
    oFD_OpenFile = gcnew OpenFileDialog();
    oFD_OpenFile->Filter = "Supported Files|*.txt;*.hex;*.hxd|All Files|*.*";
    oFD_OpenFile->Title = "Select a file";
}

// Открыть файл
System::Void TD4mEmulator::MainWindow::Data_Load(System::Object^ sender, System::EventArgs^ e) 
{
    String^ filePath = tSTB_selectedFile->Text;
    auto logger = mEm->GetLogger();

    // Проверка существования файла и его корректности
    if (!FileExists(filePath)) {
        return; // Ошибки уже записаны в лог
    }

    // Открываем файл и загружаем данные
    try {
        std::string nativePath = marshal_as<std::string>(filePath);
        std::ifstream file(nativePath);

        if (!file.is_open()) {
            logger->Log("Error: Failed to open the file: " + filePath);
            return;
        }

        Byte address = 0;
        std::string hexValue;

        while (file >> hexValue) {
            // Проверяем, что значение действительно шестнадцатеричное
            if (!std::regex_match(hexValue, std::regex("^[0-9A-Fa-f]{1,2}$"))) {
                logger->Log("Error: Invalid hexadecimal value in file: " + gcnew String(hexValue.c_str()));
                return;
            }

            // Преобразуем в Byte и записываем в память
            Byte value = static_cast<Byte>(std::stoi(hexValue, nullptr, 16));
            if (address >= mEm->GetMemory()->ROMLength) {
                logger->Log("Error: File contains more data than ROM capacity.");
                return;
            }
            mEm->GetMemory()->WriteROM(address++, value);
        }

        file.close();
        logger->Log("Data loaded successfully from: " + filePath);
    }
    catch (Exception^ ex) {
        logger->Log("Error loading data: " + ex->Message);
    }
}

// Сохранить в файл
System::Void TD4mEmulator::MainWindow::Data_Save(System::Object^ sender, System::EventArgs^ e) {}

// Сохранить как
System::Void TD4mEmulator::MainWindow::Data_SaveAs(System::Object^ sender, System::EventArgs^ e) {}

// Выход
System::Void TD4mEmulator::MainWindow::Exit(System::Object^ sender, System::EventArgs^ e) {}



// Смена вида ПЗУ
System::Void TD4mEmulator::MainWindow::ROM_ChangeStyle(System::Object^ sender, System::EventArgs^ e) {}

// Очистка ПЗУ
System::Void TD4mEmulator::MainWindow::ROM_Clear(System::Object^ sender, System::EventArgs^ e) {}

// Смена вида ОЗУ
System::Void TD4mEmulator::MainWindow::RAM_ChangeStyle(System::Object^ sender, System::EventArgs^ e) {}

// Очистка ОЗУ - а надо ли вообще?
System::Void TD4mEmulator::MainWindow::RAM_Clear(System::Object^ sender, System::EventArgs^ e) {}



// Перезагрузка таблицы команд
System::Void TD4mEmulator::MainWindow::CommandTab_Reload(System::Object^ sender, System::EventArgs^ e) {}

// Настройки - пока не знаю, что сюда надо
System::Void TD4mEmulator::MainWindow::Settings(System::Object^ sender, System::EventArgs^ e) {}



// Таблица команд
System::Void TD4mEmulator::MainWindow::CommandTab_Show(System::Object^ sender, System::EventArgs^ e) {}

// О программе
System::Void TD4mEmulator::MainWindow::Info(System::Object^ sender, System::EventArgs^ e) {}



// Старт
System::Void TD4mEmulator::MainWindow::Generator_Start(System::Object^ sender, System::EventArgs^ e) {}

// Стоп
System::Void TD4mEmulator::MainWindow::Generator_Stop(System::Object^ sender, System::EventArgs^ e) {}

// Сброс
System::Void TD4mEmulator::MainWindow::Generator_Restart(System::Object^ sender, System::EventArgs^ e) {}



// Проверка существования файла
bool TD4mEmulator::MainWindow::FileExists(String^ filePath)
{
    auto logger = mEm->GetLogger();

    // Если путь пустой, открыть диалоговое окно
    if (String::IsNullOrWhiteSpace(filePath)) {
        if (oFD_OpenFile->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
            filePath = oFD_OpenFile->FileName;
            logger->Log("File selected: " + filePath);
        }
        else {
            logger->Log("No file selected.");
            return false;
        }
    }

    // Проверка существования файла
    if (!System::IO::File::Exists(filePath)) {
        logger->Log("Error: File does not exist: " + filePath);
        return false;
    }

    // Проверка расширения файла
    String^ extension = Path::GetExtension(filePath)->ToLower();
    if (extension != ".txt" && extension != ".hex" && extension != ".hxd") {
        logger->Log("Error: Unsupported file extension: " + extension);
        return false;
    }

    return true;
}