// Main.h
#pragma once

#include "MainWindow.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
void main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	TD4mEmulator::MainWindow form;
	Application::Run(% form);
}