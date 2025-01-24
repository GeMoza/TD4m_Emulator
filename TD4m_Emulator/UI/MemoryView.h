#pragma once

#include "../Core/Emulator.h"

namespace TD4mEmulator {
	using System::Byte;
	using System::Int16;
	using System::Windows::Forms::Label;
	using System::Windows::Forms::TextBox;
	using System::Windows::Forms::CheckBox;
	using System::Windows::Forms::FlowLayoutPanel;

	// ����� ����������� ������� ������ (��� ��� ���)
	ref class MemoryView
	{
	public:
		enum class DataDisplayMode {
			BINARY, HEX, TEXT
		};

		MemoryView(FlowLayoutPanel^ panel, Emulator^ mEmulator, bool ram);

		// ��������� ��� ����������� ������
		System::Void Build();

		// ��������� ��������� ������� � ������
		System::Void Highlight(Int16 index);

		// ��������� ������ �����������
		System::Void SetMode(DataDisplayMode mode);
	
		// ���������� �������� � UI-���������
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

		// ��������� ���������� ���� ������ ����� �������
		System::Void Bit_Changed(System::Object^ sender, System::EventArgs^ e);
	};
}