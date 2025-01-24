#pragma once

#include "../Core/Emulator.h"
#include "MemoryView.h"

namespace TD4mEmulator {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MainWindow
	/// </summary>
	public ref class MainWindow : public System::Windows::Forms::Form
	{
	public:
		MainWindow(void)
		{
			InitializeComponent();
			Initialize();
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MainWindow()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::GroupBox^ gB_register_A;
	private: System::Windows::Forms::TextBox^ tB_register_A;
	private: System::Windows::Forms::Panel^ pnl_Register;
	private: System::Windows::Forms::Label^ lb_TD4m_Emulator;
	private: System::Windows::Forms::Label^ lb_Register;
	private: System::Windows::Forms::GroupBox^ gB_register_B;
	private: System::Windows::Forms::TextBox^ tB_register_B;
	private: System::Windows::Forms::GroupBox^ gB_flag_Z;
	private: System::Windows::Forms::TextBox^ tB_flag_Z;
	private: System::Windows::Forms::GroupBox^ gB_flag_C;
	private: System::Windows::Forms::TextBox^ tB_flag_C;
	private: System::Windows::Forms::GroupBox^ gB_register_PC;
	private: System::Windows::Forms::TextBox^ tB_register_PC;
	private: System::Windows::Forms::GroupBox^ gB_register_XY;
	private: System::Windows::Forms::TextBox^ tB_register_XY;
	private: System::Windows::Forms::GroupBox^ gB_port_input;
	private: System::Windows::Forms::GroupBox^ gB_port_output;
	private: System::Windows::Forms::TextBox^ tB_port_output;

	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::Panel^ pnl_ROM;
	private: System::Windows::Forms::Label^ lb_ROM;
	private: System::Windows::Forms::ToolStrip^ tS_Down_1;
	private: System::Windows::Forms::ToolStripLabel^ tSL_selectedFile;

	private: System::Windows::Forms::ToolStripSeparator^ TSSep_1;
	private: System::Windows::Forms::ToolStripLabel^ tSL_clockGenerator;
	private: System::Windows::Forms::MenuStrip^ mS_Up_1;
	private: System::Windows::Forms::ToolStripMenuItem^ tSM_file;
	private: System::Windows::Forms::ToolStripMenuItem^ tSM_file_open;
	private: System::Windows::Forms::ToolStripSeparator^ tSM_Sep_1;
	private: System::Windows::Forms::ToolStripMenuItem^ tSM_file_save;
	private: System::Windows::Forms::ToolStripMenuItem^ tSM_file_saveAss;
	private: System::Windows::Forms::ToolStripSeparator^ tSM_Sep_2;
	private: System::Windows::Forms::ToolStripMenuItem^ tSM_file_exit;
	private: System::Windows::Forms::ToolStripMenuItem^ tSM_service;
	private: System::Windows::Forms::ToolStripMenuItem^ tSM_service_options;
	private: System::Windows::Forms::ToolStripMenuItem^ справкаToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ tSM_reference_commandTab;
	private: System::Windows::Forms::ToolStripSeparator^ tSM_Sep_3;
	private: System::Windows::Forms::ToolStripMenuItem^ tSM_reference;
	private: System::Windows::Forms::ToolStripComboBox^ tSCB_clockGenerator_mode;
	private: System::Windows::Forms::ToolStripButton^ tSB_clockGenerator_start;
	private: System::Windows::Forms::ToolStripButton^ tSB_clockGenerator_reset;
	private: System::Windows::Forms::ToolStripButton^ tSB_clockGenerator_stop;
	private: System::Windows::Forms::FlowLayoutPanel^ pnl_ROM_rows;

	private: System::Windows::Forms::ToolStripSeparator^ tSSep_2;
	private: System::Windows::Forms::ToolStripMenuItem^ tSM_RM;
	private: System::Windows::Forms::ToolStripMenuItem^ tSM_service_reload;
	private: System::Windows::Forms::ToolStripMenuItem^ tSM_service_reload_commandTab;
	private: System::Windows::Forms::ToolStripMenuItem^ tSM_ROM_view;
	private: System::Windows::Forms::ToolStripMenuItem^ tSM_ROM_view_text;
	private: System::Windows::Forms::ToolStripMenuItem^ tSM_ROM_view_binary;
	private: System::Windows::Forms::ToolStripMenuItem^ tSM_ROM_view_gex;
	private: System::Windows::Forms::ToolStripMenuItem^ tSM_ROM_clear;
	private: System::Windows::Forms::Panel^ pnl_RAM;
	private: System::Windows::Forms::FlowLayoutPanel^ pnl_RAM_rows;

	private: System::Windows::Forms::Label^ lb_RAM;
	private: System::Windows::Forms::ToolStripSeparator^ toolStripMenuItem2;
	private: System::Windows::Forms::ToolStripMenuItem^ tSM_RAM_view;
	private: System::Windows::Forms::ToolStripMenuItem^ tSM_RAM_view_binary;
	private: System::Windows::Forms::ToolStripMenuItem^ tSM_RAM_view_gex;
	private: System::Windows::Forms::ToolStripMenuItem^ tSM_RAM_clear;
	private: System::Windows::Forms::OpenFileDialog^ oFD_OpenFile;
	private: System::Windows::Forms::SaveFileDialog^ sFD_SaveFile;
	private: System::Windows::Forms::TextBox^ tB_Log;
	private: System::Windows::Forms::Timer^ cl_clockTimer;
	private: System::Windows::Forms::FlowLayoutPanel^ pnl_inputs;

	private: System::ComponentModel::IContainer^ components;

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainWindow::typeid));
			this->gB_register_A = (gcnew System::Windows::Forms::GroupBox());
			this->tB_register_A = (gcnew System::Windows::Forms::TextBox());
			this->pnl_Register = (gcnew System::Windows::Forms::Panel());
			this->gB_port_input = (gcnew System::Windows::Forms::GroupBox());
			this->pnl_inputs = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->gB_port_output = (gcnew System::Windows::Forms::GroupBox());
			this->tB_port_output = (gcnew System::Windows::Forms::TextBox());
			this->gB_register_XY = (gcnew System::Windows::Forms::GroupBox());
			this->tB_register_XY = (gcnew System::Windows::Forms::TextBox());
			this->gB_flag_Z = (gcnew System::Windows::Forms::GroupBox());
			this->tB_flag_Z = (gcnew System::Windows::Forms::TextBox());
			this->gB_flag_C = (gcnew System::Windows::Forms::GroupBox());
			this->tB_flag_C = (gcnew System::Windows::Forms::TextBox());
			this->gB_register_PC = (gcnew System::Windows::Forms::GroupBox());
			this->tB_register_PC = (gcnew System::Windows::Forms::TextBox());
			this->gB_register_B = (gcnew System::Windows::Forms::GroupBox());
			this->tB_register_B = (gcnew System::Windows::Forms::TextBox());
			this->lb_Register = (gcnew System::Windows::Forms::Label());
			this->lb_TD4m_Emulator = (gcnew System::Windows::Forms::Label());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->tB_Log = (gcnew System::Windows::Forms::TextBox());
			this->pnl_ROM = (gcnew System::Windows::Forms::Panel());
			this->pnl_ROM_rows = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->lb_ROM = (gcnew System::Windows::Forms::Label());
			this->tS_Down_1 = (gcnew System::Windows::Forms::ToolStrip());
			this->tSL_selectedFile = (gcnew System::Windows::Forms::ToolStripLabel());
			this->TSSep_1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->tSL_clockGenerator = (gcnew System::Windows::Forms::ToolStripLabel());
			this->tSCB_clockGenerator_mode = (gcnew System::Windows::Forms::ToolStripComboBox());
			this->tSB_clockGenerator_start = (gcnew System::Windows::Forms::ToolStripButton());
			this->tSB_clockGenerator_stop = (gcnew System::Windows::Forms::ToolStripButton());
			this->tSB_clockGenerator_reset = (gcnew System::Windows::Forms::ToolStripButton());
			this->tSSep_2 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->mS_Up_1 = (gcnew System::Windows::Forms::MenuStrip());
			this->tSM_file = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tSM_file_open = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tSM_Sep_1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->tSM_file_save = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tSM_file_saveAss = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tSM_Sep_2 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->tSM_file_exit = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tSM_RM = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tSM_ROM_view = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tSM_ROM_view_text = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tSM_ROM_view_binary = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tSM_ROM_view_gex = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tSM_ROM_clear = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem2 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->tSM_RAM_view = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tSM_RAM_view_binary = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tSM_RAM_view_gex = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tSM_RAM_clear = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tSM_service = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tSM_service_reload = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tSM_service_reload_commandTab = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tSM_service_options = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->справкаToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tSM_reference_commandTab = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tSM_Sep_3 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->tSM_reference = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->pnl_RAM = (gcnew System::Windows::Forms::Panel());
			this->pnl_RAM_rows = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->lb_RAM = (gcnew System::Windows::Forms::Label());
			this->oFD_OpenFile = (gcnew System::Windows::Forms::OpenFileDialog());
			this->sFD_SaveFile = (gcnew System::Windows::Forms::SaveFileDialog());
			this->cl_clockTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->gB_register_A->SuspendLayout();
			this->pnl_Register->SuspendLayout();
			this->gB_port_input->SuspendLayout();
			this->gB_port_output->SuspendLayout();
			this->gB_register_XY->SuspendLayout();
			this->gB_flag_Z->SuspendLayout();
			this->gB_flag_C->SuspendLayout();
			this->gB_register_PC->SuspendLayout();
			this->gB_register_B->SuspendLayout();
			this->panel1->SuspendLayout();
			this->pnl_ROM->SuspendLayout();
			this->tS_Down_1->SuspendLayout();
			this->mS_Up_1->SuspendLayout();
			this->pnl_RAM->SuspendLayout();
			this->SuspendLayout();
			// 
			// gB_register_A
			// 
			this->gB_register_A->Controls->Add(this->tB_register_A);
			this->gB_register_A->Location = System::Drawing::Point(10, 30);
			this->gB_register_A->Margin = System::Windows::Forms::Padding(5);
			this->gB_register_A->Name = L"gB_register_A";
			this->gB_register_A->Padding = System::Windows::Forms::Padding(10, 4, 10, 4);
			this->gB_register_A->Size = System::Drawing::Size(120, 50);
			this->gB_register_A->TabIndex = 0;
			this->gB_register_A->TabStop = false;
			this->gB_register_A->Text = L"Регистр A";
			// 
			// tB_register_A
			// 
			this->tB_register_A->BackColor = System::Drawing::SystemColors::ControlLight;
			this->tB_register_A->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->tB_register_A->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tB_register_A->Location = System::Drawing::Point(10, 16);
			this->tB_register_A->Margin = System::Windows::Forms::Padding(5);
			this->tB_register_A->MaxLength = 4;
			this->tB_register_A->Name = L"tB_register_A";
			this->tB_register_A->ReadOnly = true;
			this->tB_register_A->Size = System::Drawing::Size(100, 19);
			this->tB_register_A->TabIndex = 0;
			this->tB_register_A->Text = L"0000";
			this->tB_register_A->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// pnl_Register
			// 
			this->pnl_Register->BackColor = System::Drawing::SystemColors::ControlLight;
			this->pnl_Register->Controls->Add(this->gB_port_input);
			this->pnl_Register->Controls->Add(this->gB_port_output);
			this->pnl_Register->Controls->Add(this->gB_register_XY);
			this->pnl_Register->Controls->Add(this->gB_flag_Z);
			this->pnl_Register->Controls->Add(this->gB_flag_C);
			this->pnl_Register->Controls->Add(this->gB_register_PC);
			this->pnl_Register->Controls->Add(this->gB_register_B);
			this->pnl_Register->Controls->Add(this->lb_Register);
			this->pnl_Register->Controls->Add(this->gB_register_A);
			this->pnl_Register->Location = System::Drawing::Point(10, 69);
			this->pnl_Register->Margin = System::Windows::Forms::Padding(5);
			this->pnl_Register->Name = L"pnl_Register";
			this->pnl_Register->Padding = System::Windows::Forms::Padding(5);
			this->pnl_Register->Size = System::Drawing::Size(300, 330);
			this->pnl_Register->TabIndex = 8;
			// 
			// gB_port_input
			// 
			this->gB_port_input->Controls->Add(this->pnl_inputs);
			this->gB_port_input->Location = System::Drawing::Point(142, 150);
			this->gB_port_input->Margin = System::Windows::Forms::Padding(5);
			this->gB_port_input->Name = L"gB_port_input";
			this->gB_port_input->Padding = System::Windows::Forms::Padding(10, 4, 10, 4);
			this->gB_port_input->Size = System::Drawing::Size(158, 170);
			this->gB_port_input->TabIndex = 8;
			this->gB_port_input->TabStop = false;
			this->gB_port_input->Text = L"Входной порт";
			// 
			// pnl_inputs
			// 
			this->pnl_inputs->AutoScroll = true;
			this->pnl_inputs->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pnl_inputs->Location = System::Drawing::Point(10, 16);
			this->pnl_inputs->Name = L"pnl_inputs";
			this->pnl_inputs->Size = System::Drawing::Size(138, 150);
			this->pnl_inputs->TabIndex = 0;
			// 
			// gB_port_output
			// 
			this->gB_port_output->Controls->Add(this->tB_port_output);
			this->gB_port_output->Location = System::Drawing::Point(10, 270);
			this->gB_port_output->Margin = System::Windows::Forms::Padding(5);
			this->gB_port_output->Name = L"gB_port_output";
			this->gB_port_output->Padding = System::Windows::Forms::Padding(10, 4, 10, 4);
			this->gB_port_output->Size = System::Drawing::Size(120, 50);
			this->gB_port_output->TabIndex = 7;
			this->gB_port_output->TabStop = false;
			this->gB_port_output->Text = L"Выходной порт";
			// 
			// tB_port_output
			// 
			this->tB_port_output->BackColor = System::Drawing::SystemColors::ControlLight;
			this->tB_port_output->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->tB_port_output->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tB_port_output->Location = System::Drawing::Point(10, 16);
			this->tB_port_output->Margin = System::Windows::Forms::Padding(5);
			this->tB_port_output->MaxLength = 4;
			this->tB_port_output->Name = L"tB_port_output";
			this->tB_port_output->ReadOnly = true;
			this->tB_port_output->Size = System::Drawing::Size(100, 19);
			this->tB_port_output->TabIndex = 0;
			this->tB_port_output->Text = L"0000";
			this->tB_port_output->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// gB_register_XY
			// 
			this->gB_register_XY->Controls->Add(this->tB_register_XY);
			this->gB_register_XY->Location = System::Drawing::Point(140, 90);
			this->gB_register_XY->Margin = System::Windows::Forms::Padding(5);
			this->gB_register_XY->Name = L"gB_register_XY";
			this->gB_register_XY->Padding = System::Windows::Forms::Padding(10, 4, 10, 4);
			this->gB_register_XY->Size = System::Drawing::Size(150, 50);
			this->gB_register_XY->TabIndex = 6;
			this->gB_register_XY->TabStop = false;
			this->gB_register_XY->Text = L"Регистр XY (RAM адрес)";
			// 
			// tB_register_XY
			// 
			this->tB_register_XY->BackColor = System::Drawing::SystemColors::ControlLight;
			this->tB_register_XY->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->tB_register_XY->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tB_register_XY->Location = System::Drawing::Point(10, 16);
			this->tB_register_XY->Margin = System::Windows::Forms::Padding(5);
			this->tB_register_XY->MaxLength = 8;
			this->tB_register_XY->Name = L"tB_register_XY";
			this->tB_register_XY->ReadOnly = true;
			this->tB_register_XY->Size = System::Drawing::Size(130, 19);
			this->tB_register_XY->TabIndex = 0;
			this->tB_register_XY->Text = L"0000 0000";
			this->tB_register_XY->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// gB_flag_Z
			// 
			this->gB_flag_Z->Controls->Add(this->tB_flag_Z);
			this->gB_flag_Z->Location = System::Drawing::Point(10, 210);
			this->gB_flag_Z->Margin = System::Windows::Forms::Padding(5);
			this->gB_flag_Z->Name = L"gB_flag_Z";
			this->gB_flag_Z->Padding = System::Windows::Forms::Padding(10, 4, 10, 4);
			this->gB_flag_Z->Size = System::Drawing::Size(120, 50);
			this->gB_flag_Z->TabIndex = 4;
			this->gB_flag_Z->TabStop = false;
			this->gB_flag_Z->Text = L"Флаг Z";
			// 
			// tB_flag_Z
			// 
			this->tB_flag_Z->BackColor = System::Drawing::SystemColors::ControlLight;
			this->tB_flag_Z->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->tB_flag_Z->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tB_flag_Z->Location = System::Drawing::Point(10, 16);
			this->tB_flag_Z->Margin = System::Windows::Forms::Padding(5);
			this->tB_flag_Z->MaxLength = 1;
			this->tB_flag_Z->Name = L"tB_flag_Z";
			this->tB_flag_Z->ReadOnly = true;
			this->tB_flag_Z->Size = System::Drawing::Size(100, 19);
			this->tB_flag_Z->TabIndex = 0;
			this->tB_flag_Z->Text = L"0";
			this->tB_flag_Z->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// gB_flag_C
			// 
			this->gB_flag_C->Controls->Add(this->tB_flag_C);
			this->gB_flag_C->Location = System::Drawing::Point(10, 150);
			this->gB_flag_C->Margin = System::Windows::Forms::Padding(5);
			this->gB_flag_C->Name = L"gB_flag_C";
			this->gB_flag_C->Padding = System::Windows::Forms::Padding(10, 4, 10, 4);
			this->gB_flag_C->Size = System::Drawing::Size(120, 50);
			this->gB_flag_C->TabIndex = 3;
			this->gB_flag_C->TabStop = false;
			this->gB_flag_C->Text = L"Флаг C";
			// 
			// tB_flag_C
			// 
			this->tB_flag_C->BackColor = System::Drawing::SystemColors::ControlLight;
			this->tB_flag_C->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->tB_flag_C->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tB_flag_C->Location = System::Drawing::Point(10, 16);
			this->tB_flag_C->Margin = System::Windows::Forms::Padding(5);
			this->tB_flag_C->MaxLength = 1;
			this->tB_flag_C->Name = L"tB_flag_C";
			this->tB_flag_C->ReadOnly = true;
			this->tB_flag_C->Size = System::Drawing::Size(100, 19);
			this->tB_flag_C->TabIndex = 0;
			this->tB_flag_C->Text = L"0";
			this->tB_flag_C->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// gB_register_PC
			// 
			this->gB_register_PC->Controls->Add(this->tB_register_PC);
			this->gB_register_PC->Location = System::Drawing::Point(140, 30);
			this->gB_register_PC->Margin = System::Windows::Forms::Padding(5);
			this->gB_register_PC->Name = L"gB_register_PC";
			this->gB_register_PC->Padding = System::Windows::Forms::Padding(10, 4, 10, 4);
			this->gB_register_PC->Size = System::Drawing::Size(150, 50);
			this->gB_register_PC->TabIndex = 5;
			this->gB_register_PC->TabStop = false;
			this->gB_register_PC->Text = L"Регистр PC (счётчик)";
			// 
			// tB_register_PC
			// 
			this->tB_register_PC->BackColor = System::Drawing::SystemColors::ControlLight;
			this->tB_register_PC->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->tB_register_PC->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tB_register_PC->Location = System::Drawing::Point(10, 16);
			this->tB_register_PC->Margin = System::Windows::Forms::Padding(5);
			this->tB_register_PC->MaxLength = 8;
			this->tB_register_PC->Name = L"tB_register_PC";
			this->tB_register_PC->ReadOnly = true;
			this->tB_register_PC->Size = System::Drawing::Size(130, 19);
			this->tB_register_PC->TabIndex = 0;
			this->tB_register_PC->Text = L"0000 0000";
			this->tB_register_PC->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// gB_register_B
			// 
			this->gB_register_B->Controls->Add(this->tB_register_B);
			this->gB_register_B->Location = System::Drawing::Point(10, 90);
			this->gB_register_B->Margin = System::Windows::Forms::Padding(5);
			this->gB_register_B->Name = L"gB_register_B";
			this->gB_register_B->Padding = System::Windows::Forms::Padding(10, 4, 10, 4);
			this->gB_register_B->Size = System::Drawing::Size(120, 50);
			this->gB_register_B->TabIndex = 2;
			this->gB_register_B->TabStop = false;
			this->gB_register_B->Text = L"Регистр B";
			// 
			// tB_register_B
			// 
			this->tB_register_B->BackColor = System::Drawing::SystemColors::ControlLight;
			this->tB_register_B->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->tB_register_B->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tB_register_B->Location = System::Drawing::Point(10, 16);
			this->tB_register_B->Margin = System::Windows::Forms::Padding(5);
			this->tB_register_B->MaxLength = 4;
			this->tB_register_B->Name = L"tB_register_B";
			this->tB_register_B->ReadOnly = true;
			this->tB_register_B->Size = System::Drawing::Size(100, 19);
			this->tB_register_B->TabIndex = 0;
			this->tB_register_B->Text = L"0000";
			this->tB_register_B->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// lb_Register
			// 
			this->lb_Register->Dock = System::Windows::Forms::DockStyle::Top;
			this->lb_Register->Font = (gcnew System::Drawing::Font(L"Times New Roman", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->lb_Register->Location = System::Drawing::Point(5, 5);
			this->lb_Register->Margin = System::Windows::Forms::Padding(5, 0, 5, 0);
			this->lb_Register->Name = L"lb_Register";
			this->lb_Register->Size = System::Drawing::Size(290, 20);
			this->lb_Register->TabIndex = 1;
			this->lb_Register->Text = L"Реестр";
			this->lb_Register->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lb_TD4m_Emulator
			// 
			this->lb_TD4m_Emulator->BackColor = System::Drawing::SystemColors::MenuHighlight;
			this->lb_TD4m_Emulator->Dock = System::Windows::Forms::DockStyle::Top;
			this->lb_TD4m_Emulator->Font = (gcnew System::Drawing::Font(L"Times New Roman", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->lb_TD4m_Emulator->Location = System::Drawing::Point(0, 24);
			this->lb_TD4m_Emulator->Name = L"lb_TD4m_Emulator";
			this->lb_TD4m_Emulator->Size = System::Drawing::Size(919, 40);
			this->lb_TD4m_Emulator->TabIndex = 9;
			this->lb_TD4m_Emulator->Text = L"Эмулятор TD4m";
			this->lb_TD4m_Emulator->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::SystemColors::ControlLight;
			this->panel1->Controls->Add(this->tB_Log);
			this->panel1->Location = System::Drawing::Point(10, 409);
			this->panel1->Margin = System::Windows::Forms::Padding(5);
			this->panel1->Name = L"panel1";
			this->panel1->Padding = System::Windows::Forms::Padding(5);
			this->panel1->Size = System::Drawing::Size(300, 200);
			this->panel1->TabIndex = 10;
			// 
			// tB_Log
			// 
			this->tB_Log->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tB_Log->Location = System::Drawing::Point(5, 5);
			this->tB_Log->Margin = System::Windows::Forms::Padding(5);
			this->tB_Log->Multiline = true;
			this->tB_Log->Name = L"tB_Log";
			this->tB_Log->ScrollBars = System::Windows::Forms::ScrollBars::Both;
			this->tB_Log->Size = System::Drawing::Size(290, 190);
			this->tB_Log->TabIndex = 0;
			// 
			// pnl_ROM
			// 
			this->pnl_ROM->BackColor = System::Drawing::SystemColors::ControlLight;
			this->pnl_ROM->Controls->Add(this->pnl_ROM_rows);
			this->pnl_ROM->Controls->Add(this->lb_ROM);
			this->pnl_ROM->Location = System::Drawing::Point(320, 69);
			this->pnl_ROM->Margin = System::Windows::Forms::Padding(5);
			this->pnl_ROM->Name = L"pnl_ROM";
			this->pnl_ROM->Padding = System::Windows::Forms::Padding(5);
			this->pnl_ROM->Size = System::Drawing::Size(290, 540);
			this->pnl_ROM->TabIndex = 11;
			// 
			// pnl_ROM_rows
			// 
			this->pnl_ROM_rows->AutoScroll = true;
			this->pnl_ROM_rows->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pnl_ROM_rows->Location = System::Drawing::Point(5, 25);
			this->pnl_ROM_rows->Margin = System::Windows::Forms::Padding(5);
			this->pnl_ROM_rows->Name = L"pnl_ROM_rows";
			this->pnl_ROM_rows->Padding = System::Windows::Forms::Padding(5);
			this->pnl_ROM_rows->Size = System::Drawing::Size(280, 510);
			this->pnl_ROM_rows->TabIndex = 3;
			// 
			// lb_ROM
			// 
			this->lb_ROM->Dock = System::Windows::Forms::DockStyle::Top;
			this->lb_ROM->Font = (gcnew System::Drawing::Font(L"Times New Roman", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->lb_ROM->Location = System::Drawing::Point(5, 5);
			this->lb_ROM->Margin = System::Windows::Forms::Padding(5, 0, 5, 0);
			this->lb_ROM->Name = L"lb_ROM";
			this->lb_ROM->Size = System::Drawing::Size(280, 20);
			this->lb_ROM->TabIndex = 2;
			this->lb_ROM->Text = L"ПЗУ";
			this->lb_ROM->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// tS_Down_1
			// 
			this->tS_Down_1->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->tS_Down_1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(8) {
				this->tSL_selectedFile,
					this->TSSep_1, this->tSL_clockGenerator, this->tSCB_clockGenerator_mode, this->tSB_clockGenerator_start, this->tSB_clockGenerator_stop,
					this->tSB_clockGenerator_reset, this->tSSep_2
			});
			this->tS_Down_1->Location = System::Drawing::Point(0, 621);
			this->tS_Down_1->Name = L"tS_Down_1";
			this->tS_Down_1->Size = System::Drawing::Size(919, 25);
			this->tS_Down_1->TabIndex = 13;
			this->tS_Down_1->Text = L"toolStrip1";
			// 
			// tSL_selectedFile
			// 
			this->tSL_selectedFile->Name = L"tSL_selectedFile";
			this->tSL_selectedFile->Size = System::Drawing::Size(97, 22);
			this->tSL_selectedFile->Text = L"Файл не выбран";
			// 
			// TSSep_1
			// 
			this->TSSep_1->Name = L"TSSep_1";
			this->TSSep_1->Size = System::Drawing::Size(6, 25);
			// 
			// tSL_clockGenerator
			// 
			this->tSL_clockGenerator->Name = L"tSL_clockGenerator";
			this->tSL_clockGenerator->Size = System::Drawing::Size(95, 22);
			this->tSL_clockGenerator->Text = L"Генератор такта";
			// 
			// tSCB_clockGenerator_mode
			// 
			this->tSCB_clockGenerator_mode->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"Вручную", L"1 Гц", L"10 Гц" });
			this->tSCB_clockGenerator_mode->Name = L"tSCB_clockGenerator_mode";
			this->tSCB_clockGenerator_mode->Size = System::Drawing::Size(121, 25);
			this->tSCB_clockGenerator_mode->Text = L"Режим работы";
			this->tSCB_clockGenerator_mode->SelectedIndexChanged += gcnew System::EventHandler(this, &MainWindow::Generator_ChangeMode);
			// 
			// tSB_clockGenerator_start
			// 
			this->tSB_clockGenerator_start->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->tSB_clockGenerator_start->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tSB_clockGenerator_start.Image")));
			this->tSB_clockGenerator_start->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tSB_clockGenerator_start->Name = L"tSB_clockGenerator_start";
			this->tSB_clockGenerator_start->Size = System::Drawing::Size(23, 22);
			this->tSB_clockGenerator_start->Text = L"toolStripButton1";
			this->tSB_clockGenerator_start->Click += gcnew System::EventHandler(this, &MainWindow::Generator_Start);
			// 
			// tSB_clockGenerator_stop
			// 
			this->tSB_clockGenerator_stop->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->tSB_clockGenerator_stop->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tSB_clockGenerator_stop.Image")));
			this->tSB_clockGenerator_stop->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tSB_clockGenerator_stop->Name = L"tSB_clockGenerator_stop";
			this->tSB_clockGenerator_stop->Size = System::Drawing::Size(23, 22);
			this->tSB_clockGenerator_stop->Text = L"toolStripButton3";
			this->tSB_clockGenerator_stop->Click += gcnew System::EventHandler(this, &MainWindow::Generator_Stop);
			// 
			// tSB_clockGenerator_reset
			// 
			this->tSB_clockGenerator_reset->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->tSB_clockGenerator_reset->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tSB_clockGenerator_reset.Image")));
			this->tSB_clockGenerator_reset->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tSB_clockGenerator_reset->Name = L"tSB_clockGenerator_reset";
			this->tSB_clockGenerator_reset->Size = System::Drawing::Size(23, 22);
			this->tSB_clockGenerator_reset->Text = L"toolStripButton2";
			this->tSB_clockGenerator_reset->Click += gcnew System::EventHandler(this, &MainWindow::Generator_Restart);
			// 
			// tSSep_2
			// 
			this->tSSep_2->Name = L"tSSep_2";
			this->tSSep_2->Size = System::Drawing::Size(6, 25);
			// 
			// mS_Up_1
			// 
			this->mS_Up_1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->tSM_file, this->tSM_RM,
					this->tSM_service, this->справкаToolStripMenuItem
			});
			this->mS_Up_1->Location = System::Drawing::Point(0, 0);
			this->mS_Up_1->Name = L"mS_Up_1";
			this->mS_Up_1->Size = System::Drawing::Size(919, 24);
			this->mS_Up_1->TabIndex = 14;
			this->mS_Up_1->Text = L"menuStrip2";
			// 
			// tSM_file
			// 
			this->tSM_file->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {
				this->tSM_file_open,
					this->tSM_Sep_1, this->tSM_file_save, this->tSM_file_saveAss, this->tSM_Sep_2, this->tSM_file_exit
			});
			this->tSM_file->Name = L"tSM_file";
			this->tSM_file->Size = System::Drawing::Size(48, 20);
			this->tSM_file->Text = L"&Файл";
			// 
			// tSM_file_open
			// 
			this->tSM_file_open->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tSM_file_open->Name = L"tSM_file_open";
			this->tSM_file_open->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::O));
			this->tSM_file_open->Size = System::Drawing::Size(181, 22);
			this->tSM_file_open->Text = L"&Открыть";
			this->tSM_file_open->Click += gcnew System::EventHandler(this, &MainWindow::Data_Load);
			// 
			// tSM_Sep_1
			// 
			this->tSM_Sep_1->Name = L"tSM_Sep_1";
			this->tSM_Sep_1->Size = System::Drawing::Size(178, 6);
			// 
			// tSM_file_save
			// 
			this->tSM_file_save->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tSM_file_save->Name = L"tSM_file_save";
			this->tSM_file_save->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::S));
			this->tSM_file_save->Size = System::Drawing::Size(181, 22);
			this->tSM_file_save->Text = L"&Сохранить";
			this->tSM_file_save->Click += gcnew System::EventHandler(this, &MainWindow::Data_Save);
			// 
			// tSM_file_saveAss
			// 
			this->tSM_file_saveAss->Name = L"tSM_file_saveAss";
			this->tSM_file_saveAss->Size = System::Drawing::Size(181, 22);
			this->tSM_file_saveAss->Text = L"Сохранить &как";
			this->tSM_file_saveAss->Click += gcnew System::EventHandler(this, &MainWindow::Data_SaveAs);
			// 
			// tSM_Sep_2
			// 
			this->tSM_Sep_2->Name = L"tSM_Sep_2";
			this->tSM_Sep_2->Size = System::Drawing::Size(178, 6);
			// 
			// tSM_file_exit
			// 
			this->tSM_file_exit->Name = L"tSM_file_exit";
			this->tSM_file_exit->Size = System::Drawing::Size(181, 22);
			this->tSM_file_exit->Text = L"Вы&ход";
			this->tSM_file_exit->Click += gcnew System::EventHandler(this, &MainWindow::Exit);
			// 
			// tSM_RM
			// 
			this->tSM_RM->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->tSM_ROM_view,
					this->tSM_ROM_clear, this->toolStripMenuItem2, this->tSM_RAM_view, this->tSM_RAM_clear
			});
			this->tSM_RM->Name = L"tSM_RM";
			this->tSM_RM->Size = System::Drawing::Size(60, 20);
			this->tSM_RM->Text = L"Память";
			// 
			// tSM_ROM_view
			// 
			this->tSM_ROM_view->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->tSM_ROM_view_text,
					this->tSM_ROM_view_binary, this->tSM_ROM_view_gex
			});
			this->tSM_ROM_view->Name = L"tSM_ROM_view";
			this->tSM_ROM_view->Size = System::Drawing::Size(180, 22);
			this->tSM_ROM_view->Text = L"Вид ПЗУ";
			// 
			// tSM_ROM_view_text
			// 
			this->tSM_ROM_view_text->Checked = true;
			this->tSM_ROM_view_text->CheckOnClick = true;
			this->tSM_ROM_view_text->CheckState = System::Windows::Forms::CheckState::Checked;
			this->tSM_ROM_view_text->Name = L"tSM_ROM_view_text";
			this->tSM_ROM_view_text->Size = System::Drawing::Size(190, 22);
			this->tSM_ROM_view_text->Text = L"Текстовый";
			this->tSM_ROM_view_text->CheckedChanged += gcnew System::EventHandler(this, &MainWindow::ROM_ChangeStyle);
			// 
			// tSM_ROM_view_binary
			// 
			this->tSM_ROM_view_binary->CheckOnClick = true;
			this->tSM_ROM_view_binary->Name = L"tSM_ROM_view_binary";
			this->tSM_ROM_view_binary->Size = System::Drawing::Size(190, 22);
			this->tSM_ROM_view_binary->Text = L"Бинарный";
			this->tSM_ROM_view_binary->CheckedChanged += gcnew System::EventHandler(this, &MainWindow::ROM_ChangeStyle);
			// 
			// tSM_ROM_view_gex
			// 
			this->tSM_ROM_view_gex->CheckOnClick = true;
			this->tSM_ROM_view_gex->Name = L"tSM_ROM_view_gex";
			this->tSM_ROM_view_gex->Size = System::Drawing::Size(190, 22);
			this->tSM_ROM_view_gex->Text = L"Шестнадцатиричный";
			this->tSM_ROM_view_gex->CheckedChanged += gcnew System::EventHandler(this, &MainWindow::ROM_ChangeStyle);
			// 
			// tSM_ROM_clear
			// 
			this->tSM_ROM_clear->Name = L"tSM_ROM_clear";
			this->tSM_ROM_clear->Size = System::Drawing::Size(180, 22);
			this->tSM_ROM_clear->Text = L"Очистить ПЗУ";
			this->tSM_ROM_clear->Click += gcnew System::EventHandler(this, &MainWindow::ROM_Clear);
			// 
			// toolStripMenuItem2
			// 
			this->toolStripMenuItem2->Name = L"toolStripMenuItem2";
			this->toolStripMenuItem2->Size = System::Drawing::Size(177, 6);
			// 
			// tSM_RAM_view
			// 
			this->tSM_RAM_view->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->tSM_RAM_view_binary,
					this->tSM_RAM_view_gex
			});
			this->tSM_RAM_view->Name = L"tSM_RAM_view";
			this->tSM_RAM_view->Size = System::Drawing::Size(180, 22);
			this->tSM_RAM_view->Text = L"Вид ОЗУ";
			// 
			// tSM_RAM_view_binary
			// 
			this->tSM_RAM_view_binary->Checked = true;
			this->tSM_RAM_view_binary->CheckOnClick = true;
			this->tSM_RAM_view_binary->CheckState = System::Windows::Forms::CheckState::Checked;
			this->tSM_RAM_view_binary->Name = L"tSM_RAM_view_binary";
			this->tSM_RAM_view_binary->Size = System::Drawing::Size(190, 22);
			this->tSM_RAM_view_binary->Text = L"Бинарный";
			this->tSM_RAM_view_binary->CheckedChanged += gcnew System::EventHandler(this, &MainWindow::RAM_ChangeStyle);
			// 
			// tSM_RAM_view_gex
			// 
			this->tSM_RAM_view_gex->CheckOnClick = true;
			this->tSM_RAM_view_gex->Name = L"tSM_RAM_view_gex";
			this->tSM_RAM_view_gex->Size = System::Drawing::Size(190, 22);
			this->tSM_RAM_view_gex->Text = L"Шестнадцатиричный";
			this->tSM_RAM_view_gex->CheckedChanged += gcnew System::EventHandler(this, &MainWindow::RAM_ChangeStyle);
			// 
			// tSM_RAM_clear
			// 
			this->tSM_RAM_clear->Name = L"tSM_RAM_clear";
			this->tSM_RAM_clear->Size = System::Drawing::Size(180, 22);
			this->tSM_RAM_clear->Text = L"Очистить ОЗУ";
			this->tSM_RAM_clear->Click += gcnew System::EventHandler(this, &MainWindow::RAM_Clear);
			// 
			// tSM_service
			// 
			this->tSM_service->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->tSM_service_reload,
					this->tSM_service_options
			});
			this->tSM_service->Name = L"tSM_service";
			this->tSM_service->Size = System::Drawing::Size(59, 20);
			this->tSM_service->Text = L"&Сервис";
			// 
			// tSM_service_reload
			// 
			this->tSM_service_reload->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->tSM_service_reload_commandTab });
			this->tSM_service_reload->Name = L"tSM_service_reload";
			this->tSM_service_reload->Size = System::Drawing::Size(154, 22);
			this->tSM_service_reload->Text = L"Перезагрузить";
			// 
			// tSM_service_reload_commandTab
			// 
			this->tSM_service_reload_commandTab->Name = L"tSM_service_reload_commandTab";
			this->tSM_service_reload_commandTab->Size = System::Drawing::Size(164, 22);
			this->tSM_service_reload_commandTab->Text = L"Таблицу команд";
			// 
			// tSM_service_options
			// 
			this->tSM_service_options->Name = L"tSM_service_options";
			this->tSM_service_options->Size = System::Drawing::Size(154, 22);
			this->tSM_service_options->Text = L"&Настройки";
			// 
			// справкаToolStripMenuItem
			// 
			this->справкаToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->tSM_reference_commandTab,
					this->tSM_Sep_3, this->tSM_reference
			});
			this->справкаToolStripMenuItem->Name = L"справкаToolStripMenuItem";
			this->справкаToolStripMenuItem->Size = System::Drawing::Size(65, 20);
			this->справкаToolStripMenuItem->Text = L"Спра&вка";
			// 
			// tSM_reference_commandTab
			// 
			this->tSM_reference_commandTab->Name = L"tSM_reference_commandTab";
			this->tSM_reference_commandTab->Size = System::Drawing::Size(164, 22);
			this->tSM_reference_commandTab->Text = L"Таблица команд";
			// 
			// tSM_Sep_3
			// 
			this->tSM_Sep_3->Name = L"tSM_Sep_3";
			this->tSM_Sep_3->Size = System::Drawing::Size(161, 6);
			// 
			// tSM_reference
			// 
			this->tSM_reference->Name = L"tSM_reference";
			this->tSM_reference->Size = System::Drawing::Size(164, 22);
			this->tSM_reference->Text = L"&О программе...";
			// 
			// pnl_RAM
			// 
			this->pnl_RAM->BackColor = System::Drawing::SystemColors::ControlLight;
			this->pnl_RAM->Controls->Add(this->pnl_RAM_rows);
			this->pnl_RAM->Controls->Add(this->lb_RAM);
			this->pnl_RAM->Location = System::Drawing::Point(620, 69);
			this->pnl_RAM->Margin = System::Windows::Forms::Padding(5);
			this->pnl_RAM->Name = L"pnl_RAM";
			this->pnl_RAM->Padding = System::Windows::Forms::Padding(5);
			this->pnl_RAM->Size = System::Drawing::Size(290, 540);
			this->pnl_RAM->TabIndex = 15;
			// 
			// pnl_RAM_rows
			// 
			this->pnl_RAM_rows->AutoScroll = true;
			this->pnl_RAM_rows->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pnl_RAM_rows->Location = System::Drawing::Point(5, 25);
			this->pnl_RAM_rows->Margin = System::Windows::Forms::Padding(5);
			this->pnl_RAM_rows->Name = L"pnl_RAM_rows";
			this->pnl_RAM_rows->Padding = System::Windows::Forms::Padding(5);
			this->pnl_RAM_rows->Size = System::Drawing::Size(280, 510);
			this->pnl_RAM_rows->TabIndex = 3;
			// 
			// lb_RAM
			// 
			this->lb_RAM->Dock = System::Windows::Forms::DockStyle::Top;
			this->lb_RAM->Font = (gcnew System::Drawing::Font(L"Times New Roman", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->lb_RAM->Location = System::Drawing::Point(5, 5);
			this->lb_RAM->Margin = System::Windows::Forms::Padding(5, 0, 5, 0);
			this->lb_RAM->Name = L"lb_RAM";
			this->lb_RAM->Size = System::Drawing::Size(280, 20);
			this->lb_RAM->TabIndex = 2;
			this->lb_RAM->Text = L"ОЗУ";
			this->lb_RAM->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// cl_clockTimer
			// 
			this->cl_clockTimer->Tick += gcnew System::EventHandler(this, &MainWindow::Clock_Tick);
			// 
			// MainWindow
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->BackColor = System::Drawing::SystemColors::ControlDark;
			this->ClientSize = System::Drawing::Size(919, 646);
			this->Controls->Add(this->pnl_RAM);
			this->Controls->Add(this->tS_Down_1);
			this->Controls->Add(this->pnl_ROM);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->lb_TD4m_Emulator);
			this->Controls->Add(this->pnl_Register);
			this->Controls->Add(this->mS_Up_1);
			this->Font = (gcnew System::Drawing::Font(L"Times New Roman", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"MainWindow";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"MainWindow";
			this->Load += gcnew System::EventHandler(this, &MainWindow::MainWindow_Load);
			this->gB_register_A->ResumeLayout(false);
			this->gB_register_A->PerformLayout();
			this->pnl_Register->ResumeLayout(false);
			this->gB_port_input->ResumeLayout(false);
			this->gB_port_output->ResumeLayout(false);
			this->gB_port_output->PerformLayout();
			this->gB_register_XY->ResumeLayout(false);
			this->gB_register_XY->PerformLayout();
			this->gB_flag_Z->ResumeLayout(false);
			this->gB_flag_Z->PerformLayout();
			this->gB_flag_C->ResumeLayout(false);
			this->gB_flag_C->PerformLayout();
			this->gB_register_PC->ResumeLayout(false);
			this->gB_register_PC->PerformLayout();
			this->gB_register_B->ResumeLayout(false);
			this->gB_register_B->PerformLayout();
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->pnl_ROM->ResumeLayout(false);
			this->tS_Down_1->ResumeLayout(false);
			this->tS_Down_1->PerformLayout();
			this->mS_Up_1->ResumeLayout(false);
			this->mS_Up_1->PerformLayout();
			this->pnl_RAM->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}

#pragma endregion
	private: System::Void MainWindow_Load(System::Object^ sender, System::EventArgs^ e) {}



		// TODO:
		// Обработка всех кнопок						- доделать, что делать с сервисом и справкой?
		// Обновление данных после обновления ввода
		// Валидатор ввода для всех режимов				- сделать
		// Таблица команд
		// Тестирование									- нужны программы
		//		Сделать возможность текстоого ввода команд
		// 
		// Генератор такта
		// Загрузка из файла							- проверить
		// Сохранение в файл							- проверить

		// TODO: Валидация ввода
		// Режим генератора такта
		// ОЗУ?
		// Поля памяти
		// 
		// 

		// TODO: Исправить ошибки
		// Ошибка изменения значения порта при работе генератора такта
		// Структура ОЗУ при шестнадцатеричном режиме
		// 
		// 
		// 
		// 
		// 

	protected:
		Emulator^ mEm;
		
		MemoryView^ mRomMemoryView;
		MemoryView^ mRamMemoryView;

		// Инициализаци
		System::Void Initialize();

	public:
		// Открыть файл
		System::Void Data_Load(System::Object^ sender, System::EventArgs^ e);

		// Сохранить в файл
		System::Void Data_Save(System::Object^ sender, System::EventArgs^ e);

		// Сохранить как
		System::Void Data_SaveAs(System::Object^ sender, System::EventArgs^ e);

		// Выход
		System::Void Exit(System::Object^ sender, System::EventArgs^ e);



		// Смена вида ПЗУ
		System::Void ROM_ChangeStyle(System::Object^ sender, System::EventArgs^ e);

		// Очистка ПЗУ
		System::Void ROM_Clear(System::Object^ sender, System::EventArgs^ e);

		// Смена вида ОЗУ
		System::Void RAM_ChangeStyle(System::Object^ sender, System::EventArgs^ e);

		// Очистка ОЗУ - а надо ли вообще?
		System::Void RAM_Clear(System::Object^ sender, System::EventArgs^ e);



		// Перезагрузка таблицы команд
		System::Void CommandTab_Reload(System::Object^ sender, System::EventArgs^ e);

		// Настройки - пока не знаю, что сюда надо
		System::Void Settings(System::Object^ sender, System::EventArgs^ e);



		// Таблица команд
		System::Void CommandTab_Show(System::Object^ sender, System::EventArgs^ e);

		// О программе
		System::Void Info(System::Object^ sender, System::EventArgs^ e);

		// Старт
		System::Void Generator_Start(System::Object^ sender, System::EventArgs^ e);

		// Стоп
		System::Void Generator_Stop(System::Object^ sender, System::EventArgs^ e);

		// Сброс
		System::Void Generator_Restart(System::Object^ sender, System::EventArgs^ e);

		System::Void Generator_ChangeMode(System::Object^ sender, System::EventArgs^ e);

		System::Void Clock_Tick(System::Object^ sender, System::EventArgs^ e);

		System::Void LogToUI(String^ line);

		System::Void Input_Bit_Changed(System::Object^ sender, System::EventArgs^ e);
	protected:
		// Проверка существования файла
		bool FileExists(String^ filePath);

		String^ RequestOpenFile();
		String^ RequestSaveFile();

		System::Void RefreshRegisters();
		System::Void RefreshInputs();
};
}
