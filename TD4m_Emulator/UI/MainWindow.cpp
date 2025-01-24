// UI/MainWindow.cpp

#pragma once

#include "MainWindow.h"

#include <msclr/marshal_cppstd.h>
#include <msclr/event.h>
#include <fstream>
#include <string>
#include <regex>

using namespace System::Collections::Generic;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace msclr::interop;
using namespace System::IO;
using namespace System;

// Инициализация
System::Void TD4mEmulator::MainWindow::Initialize()
{
	// Установить для tSCB_clockGenerator_mode три положения и ReadOnly
	// Отрисовать поля ввода

    Logger^ logger = gcnew Logger("log.txt");
    logger->AttachToInterface(gcnew Action<String^>(this, &MainWindow::LogToUI));

    // Инициализация эмулятора
    mEm = gcnew Emulator(256, 256, "commands.xlsx", logger);

    // Инициализация диалогового окна
    oFD_OpenFile = gcnew OpenFileDialog();
    oFD_OpenFile->Filter = "Supported Files|*.txt;*.hex;*.hxd|All Files|*.*";
    oFD_OpenFile->Title = "Select a file";

    mRomMemoryView = gcnew MemoryView(pnl_ROM_rows, mEm, false);
    mRamMemoryView = gcnew MemoryView(pnl_RAM_rows, mEm, true);
    mRomMemoryView->SetMode(MemoryView::DataDisplayMode::TEXT);
    mRomMemoryView->Build();
    mRamMemoryView->Build();

    tSCB_clockGenerator_mode->SelectedIndex = 0;
}

// Открыть файл
System::Void TD4mEmulator::MainWindow::Data_Load(System::Object^ sender, System::EventArgs^ e) 
{
    String^ filePath = RequestOpenFile();
    auto logger = mEm->GetLogger();

    if (String::IsNullOrEmpty(filePath)) {
        return; // Ошибки уже записаны в лог
    }

    mEm->Reset();
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
        this->tSL_selectedFile->Text = filePath;
        mRomMemoryView->Build();

        
        RefreshInputs();
        RefreshRegisters();
    }
    catch (Exception^ ex) {
        logger->Log("Error loading data: " + ex->Message);
    }
}

// Сохранить в файл
System::Void TD4mEmulator::MainWindow::Data_Save(System::Object^ sender, System::EventArgs^ e) {
    String^ filePath = this->tSL_selectedFile->Text;
    if (!System::IO::File::Exists(filePath)) {
        filePath = RequestSaveFile();
    }
    if (String::IsNullOrEmpty(filePath)) {
        return;
    }
    this->tSL_selectedFile->Text = filePath;
    mEm->SaveToFile(filePath);
}

// Сохранить как
System::Void TD4mEmulator::MainWindow::Data_SaveAs(System::Object^ sender, System::EventArgs^ e) {
    String^ filePath = RequestSaveFile();
    if (String::IsNullOrEmpty(filePath)) {
        return;
    }
    this->tSL_selectedFile->Text = filePath;
    mEm->SaveToFile(filePath);
}

// Выход
System::Void TD4mEmulator::MainWindow::Exit(System::Object^ sender, System::EventArgs^ e) {
    Application::Exit();
}



// Смена вида ПЗУ
System::Void TD4mEmulator::MainWindow::ROM_ChangeStyle(System::Object^ sender, System::EventArgs^ e) {
    auto item = (ToolStripMenuItem^)sender;
    if (!item->Checked) {
        return;
    }

    // TODO: заменить на цикл
    if (item == tSM_ROM_view_binary) {
        tSM_ROM_view_gex->CheckState = CheckState::Unchecked;
        tSM_ROM_view_gex->Checked = false;
        tSM_ROM_view_text->CheckState = CheckState::Unchecked;
        tSM_ROM_view_text->Checked = false;
        mRomMemoryView->SetMode(MemoryView::DataDisplayMode::BINARY);
    }
    else if (item == tSM_ROM_view_gex) {
        tSM_ROM_view_binary->CheckState = CheckState::Unchecked;
        tSM_ROM_view_binary->Checked = false;
        tSM_ROM_view_text->CheckState = CheckState::Unchecked;
        tSM_ROM_view_text->Checked = false;
        mRomMemoryView->SetMode(MemoryView::DataDisplayMode::HEX);
    }
    else {
        tSM_ROM_view_binary->CheckState = CheckState::Unchecked;
        tSM_ROM_view_binary->Checked = false;
        tSM_ROM_view_gex->CheckState = CheckState::Unchecked;
        tSM_ROM_view_gex->Checked = false;
        mRomMemoryView->SetMode(MemoryView::DataDisplayMode::TEXT);
    }
    item->CheckState = CheckState::Checked;
}

// Очистка ПЗУ
System::Void TD4mEmulator::MainWindow::ROM_Clear(System::Object^ sender, System::EventArgs^ e) {
    Memory^ memory = mEm->GetMemory();
    for (int i = 0; i < memory->ROMLength; i++) {
        memory->WriteROM(i, 0);
        mRamMemoryView->Update(i);
    }
}

// Смена вида ОЗУ
System::Void TD4mEmulator::MainWindow::RAM_ChangeStyle(System::Object^ sender, System::EventArgs^ e) {
    auto item = (ToolStripMenuItem^)sender;
    if (!item->Checked) {
        return;
    }

    // TODO: заменить на цикл
    if (item == tSM_RAM_view_binary) {
        tSM_RAM_view_gex->CheckState = CheckState::Unchecked;
        tSM_RAM_view_gex->Checked = false;
        mRamMemoryView->SetMode(MemoryView::DataDisplayMode::BINARY);
    }
    else {
        tSM_RAM_view_binary->CheckState = CheckState::Unchecked;
        tSM_RAM_view_binary->Checked = false;
        mRamMemoryView->SetMode(MemoryView::DataDisplayMode::HEX);
    }
    item->CheckState = CheckState::Checked;
}

// Очистка ОЗУ
System::Void TD4mEmulator::MainWindow::RAM_Clear(System::Object^ sender, System::EventArgs^ e) {
    Memory^ memory = mEm->GetMemory();
    for (int i = 0; i < memory->RAMLength; i++) {
        memory->WriteRAM(i, 0);
        mRamMemoryView->Update(i);
    }
}



// Перезагрузка таблицы команд
System::Void TD4mEmulator::MainWindow::CommandTab_Reload(System::Object^ sender, System::EventArgs^ e) {}

// Настройки - пока не знаю, что сюда надо
System::Void TD4mEmulator::MainWindow::Settings(System::Object^ sender, System::EventArgs^ e) {}



// Таблица команд
System::Void TD4mEmulator::MainWindow::CommandTab_Show(System::Object^ sender, System::EventArgs^ e) {}

// О программе
System::Void TD4mEmulator::MainWindow::Info(System::Object^ sender, System::EventArgs^ e) {}

System::Void TD4mEmulator::MainWindow::Generator_ChangeMode(System::Object^ sender, System::EventArgs^ e) {
    auto box = (ToolStripComboBox^)sender;
    Int16 index = box->SelectedIndex;
    switch (index) {
    case 0: // ручной
        cl_clockTimer->Stop();
        break;
    case 1: // 1 в секунду
        cl_clockTimer->Interval = 1000;
        break;
    case 2: // 10 в секунду
        cl_clockTimer->Interval = 100;
        break;
    }
}

System::Void TD4mEmulator::MainWindow::RefreshRegisters() {
    Registers^ registers = mEm->GetRegisters();

    Byte pc = registers->PC;
    Byte xy = registers->XY;

    Byte a = registers->A;
    Byte b = registers->B;
    Byte out = registers->OUTP;
    bool c = registers->C;
    bool z = registers->Z;

    tB_register_PC->Text = String::Format(
        "{0} {1}", Convert::ToString(pc >> 4, 2)->PadLeft(4, '0'), Convert::ToString(pc & 0xF, 2)->PadLeft(4, '0')
    );
    tB_register_A->Text = Convert::ToString(a & 0xF, 2)->PadLeft(4, '0');
    tB_register_B->Text = Convert::ToString(b & 0xF, 2)->PadLeft(4, '0');
    tB_port_output->Text = Convert::ToString(out & 0xF, 2)->PadLeft(4, '0');
    tB_flag_C->Text = c ? "1" : "0";
    tB_flag_Z->Text = z ? "1" : "0";

    mRomMemoryView->Highlight(pc);
    mRamMemoryView->Highlight(xy);
    mRamMemoryView->Update(xy);
}

System::Void TD4mEmulator::MainWindow::Clock_Tick(System::Object^ sender, System::EventArgs^ e) {
    Memory^ memory = mEm->GetMemory();
    Registers^ registers = mEm->GetRegisters();
    Byte prev_pc = registers->PC;

    mEm->Execute(memory->ReadROM(prev_pc));

    RefreshRegisters();
}

// Старт
System::Void TD4mEmulator::MainWindow::Generator_Start(System::Object^ sender, System::EventArgs^ e) {
    if (tSCB_clockGenerator_mode->SelectedIndex == 0) {
        Clock_Tick(nullptr, nullptr);
    }
    else {
        cl_clockTimer->Start();
    }
}

// Стоп
System::Void TD4mEmulator::MainWindow::Generator_Stop(System::Object^ sender, System::EventArgs^ e) {
    cl_clockTimer->Stop();
}

// Сброс
System::Void TD4mEmulator::MainWindow::Generator_Restart(System::Object^ sender, System::EventArgs^ e) {
    mEm->GetRegisters()->Reset(false);
    RefreshRegisters();
}

System::Void TD4mEmulator::MainWindow::LogToUI(String^ line) {
    tB_Log->AppendText(line);
    tB_Log->AppendText(Environment::NewLine);
}

String^ TD4mEmulator::MainWindow::RequestOpenFile() {
    auto logger = mEm->GetLogger();

    if (oFD_OpenFile->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
        String^ filePath = oFD_OpenFile->FileName;
        logger->Log("File selected: " + filePath);

        // Проверка существования файла
        if (!System::IO::File::Exists(filePath)) {
            logger->Log("Error: File does not exist: " + filePath);
            return "";
        }

        // Проверка расширения файла
        String^ extension = Path::GetExtension(filePath)->ToLower();
        if (extension != ".txt" && extension != ".hex" && extension != ".hxd") {
            logger->Log("Error: Unsupported file extension: " + extension);
            return "";
        }
        return filePath;
    }
    else {
        logger->Log("No file selected.");
        return "";
    }
}

String^ TD4mEmulator::MainWindow::RequestSaveFile() {
    auto logger = mEm->GetLogger();

    if (sFD_SaveFile->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
        String^ filePath = sFD_SaveFile->FileName;
        logger->Log("File selected: " + filePath);

        // Проверка расширения файла
        String^ extension = Path::GetExtension(filePath)->ToLower();
        if (extension != ".txt" && extension != ".hex" && extension != ".hxd") {
            logger->Log("Error: Unsupported file extension: " + extension);
            return "";
        }
        return filePath;
    }
    else {
        logger->Log("No file selected.");
        return "";
    }
}


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

// обновление списка для входного порта
// TODO: вынести основную часть кода в Emulator
System::Void TD4mEmulator::MainWindow::RefreshInputs() {
    Memory^ memory = mEm->GetMemory();
    Registers^ registers = mEm->GetRegisters();

    List<Int16> fields;
    for (Int16 i = 0; i < memory->ROMLength; i++) {
        Byte opcode = memory->ReadROM(i);
        Byte major = opcode >> 4;
        if (major == 0b0110 || major == 0b0010) {
            fields.Add(i);
        }
    }
    registers->UpdateInputFields(fields.Count);
    pnl_inputs->SuspendLayout();
    pnl_inputs->Controls->Clear();
    for (Int16 i = 0; i < fields.Count; i++) {
        // TODO: вынести куда-нибудь. Код почти идентичен коду в MemoryView::Build.

        // Метка позиции в памяти
        Label^ lb_position = gcnew Label();
        lb_position->Width = 27;
        lb_position->Height = 36;
        lb_position->TextAlign = ContentAlignment::MiddleLeft;
        lb_position->Text = fields[i].ToString("D3");
        pnl_inputs->Controls->Add(lb_position);

        // Панель двоичного представления данных
        FlowLayoutPanel^ pnl_bits = gcnew FlowLayoutPanel();
        pnl_bits->Height = 25;
        pnl_bits->Padding.All = 0;
        pnl_bits->Margin.All = 0;
        pnl_bits->FlowDirection = FlowDirection::TopDown;
        pnl_bits->Width = 80;

        List<CheckBox^> boxes;

        for (int bit = 0; bit < 4; bit++) {
            CheckBox^ box = gcnew CheckBox();
            box->Width = 14;
            boxes.Add(box);
        }
        // Расставляются от старшего бита к младшему
        for (int bit = 3; bit >= 0; bit--) {
            CheckBox^ box = boxes[bit];
            box->Name = "B" + (i * 4 + bit);
            box->CheckedChanged += gcnew System::EventHandler(this, &TD4mEmulator::MainWindow::Input_Bit_Changed);
            pnl_bits->Controls->Add(box);
        }
        pnl_inputs->Controls->Add(pnl_bits);
    }
    pnl_inputs->ResumeLayout();
}

System::Void TD4mEmulator::MainWindow::Input_Bit_Changed(System::Object^ sender, System::EventArgs^ e) {
    Registers^ registers = mEm->GetRegisters();

    Byte bits_per_word = 4;

    CheckBox^ box = (CheckBox^)sender;
    Int16 bit_index = Convert::ToInt16(box->Name->Substring(1));
    Byte position = bit_index / bits_per_word;
    bit_index &= 3;
    Byte bit = 1 << bit_index;
    Byte value = registers->INP[position];
    if (box->Checked) {
        value |= bit;
    }
    else {
        value &= ~bit;
    }
    registers->INP[position] = value;
}
