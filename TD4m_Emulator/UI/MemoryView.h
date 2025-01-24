#pragma once

#include "../Core/Emulator.h"

namespace TD4mEmulator {
	using System::Byte;
	using System::Int16;
	using System::Windows::Forms::Label;
	using System::Windows::Forms::TextBox;
	using System::Windows::Forms::CheckBox;
	using System::Windows::Forms::FlowLayoutPanel;

	// Класс управляющий панелью памяти (ПЗУ или ОЗУ)
	ref class MemoryView
	{
	public:
		enum class DataDisplayMode {
			BINARY, HEX, TEXT
		};

		MemoryView(FlowLayoutPanel^ panel, Emulator^ mEmulator, bool ram);

		// построить или перестроить панель
		System::Void Build();

		// подсветка указанной позиции в памяти
		System::Void Highlight(Int16 index);

		// изменение режима отображения
		System::Void SetMode(DataDisplayMode mode);
	
		// обновление значения в UI-элементах
		System::Void Update(Byte position);

	private:
		bool mIsRam;
		DataDisplayMode mMode = DataDisplayMode::BINARY;
		Int16 mHighlighted = 0;
		System::Collections::Generic::List<Label^>^ mPosLabels;
		System::Collections::Generic::List<TextBox^>^ mHexBoxes;
		System::Collections::Generic::List<CheckBox^>^ mCheckBoxes;
		FlowLayoutPanel^ mPanel;
		Emulator^ mEmulator;

		// изменение отдельного бита памяти через чекбокс
		System::Void Bit_Changed(System::Object^ sender, System::EventArgs^ e);
	};
}