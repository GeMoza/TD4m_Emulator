#include "MemoryView.h"

using System::Convert;
using System::Drawing::ContentAlignment;
using System::Drawing::Color;
using namespace System::Windows::Forms;
using namespace System::Collections::Generic;

TD4mEmulator::MemoryView::MemoryView(FlowLayoutPanel^ panel, Emulator^ mEmulator, bool ram)
    : mIsRam(ram), mPanel(panel), mEmulator(mEmulator), 
    mPosLabels(gcnew List<Label^>()),
    mHexBoxes(gcnew List<TextBox^>()),
    mCheckBoxes(gcnew List<CheckBox^>())
{
}

System::Void TD4mEmulator::MemoryView::Build() {
    Byte pc = mIsRam ? mEmulator->GetRegisters()->XY : mEmulator->GetRegisters()->PC;
    Byte bits_per_word = mIsRam ? 4 : 8;

    mPosLabels->Clear();
    mHexBoxes->Clear();
    mCheckBoxes->Clear();

    // Очистка панели от прошлого содержимого
    mPanel->SuspendLayout();
    mPanel->Controls->Clear();

    Memory^ memory = mEmulator->GetMemory();
    Int16 capacity = mIsRam ? RAM_CAPACITY : ROM_CAPACITY;

    for (int i = 0; i < capacity; i++) {
        Byte value = mIsRam ? memory->ReadRAM(i) : memory->ReadROM(i);

        // Метка позиции в памяти
        Label^ lb_position = gcnew Label();
        lb_position->Width = 27;
        lb_position->TextAlign = ContentAlignment::MiddleLeft;
        lb_position->Text = i.ToString("D3");
        mPanel->Controls->Add(lb_position);

        mPosLabels->Add(lb_position);

        switch (mMode) {
        case DataDisplayMode::BINARY: {
            lb_position->Height = 36;

            // Панель двоичного представления данных
            FlowLayoutPanel^ pnl_bits = gcnew FlowLayoutPanel();
            pnl_bits->Height = 25;
            pnl_bits->Padding.All = 0;
            pnl_bits->Margin.All = 0;
            pnl_bits->FlowDirection = FlowDirection::TopDown;
            pnl_bits->Width = mIsRam ? 80 : pnl_bits->Width;

            List<CheckBox^> boxes;

            for (int bit = 0; bit < bits_per_word; bit++) {
                CheckBox^ box = gcnew CheckBox();
                box->Width = (bit == 4 && !mIsRam) ? 20 : 14;
                boxes.Add(box);
                mCheckBoxes->Add(box);
            }
            // Расставляются от старшего бита к младшему
            for (int bit = bits_per_word-1; bit >= 0; bit--) {
                CheckBox^ box = boxes[bit];
                box->Checked = (value & (1 << bit)) != 0;
                box->Name = "B" + (i * bits_per_word + bit);
                box->CheckedChanged += gcnew System::EventHandler(this, &TD4mEmulator::MemoryView::Bit_Changed);
                pnl_bits->Controls->Add(box);
            }
            mPanel->Controls->Add(pnl_bits);
            break;
        }
        case DataDisplayMode::HEX: {
            TextBox^ tb_value = gcnew TextBox();
            tb_value->Text = value.ToString("X2");
            tb_value->Width = 20;
            mPanel->Controls->Add(tb_value);
            mHexBoxes->Add(tb_value);
            break;
        }
        case DataDisplayMode::TEXT: {
            lb_position->Height = 12;
            Label^ lb_mnemonic = gcnew Label();
            lb_mnemonic->Width = 200;

            
            Byte major = value >> 4;
            Byte im    = value & 0xF;

            // Временное решение
            // TODO: требуется рефакторинг
            switch (major) {
            case 0b0000:
                if (im) lb_mnemonic->Text = "ADD A, #" + int(im).ToString(); break;
            case 0b0001:
                lb_mnemonic->Text = im ? ("ADD A, B, #" + int(im).ToString()) : "MOV A, B"; break;
            case 0b0010:
                lb_mnemonic->Text = im ? ("IN A + #" + int(im).ToString()) : "IN A"; break;
            case 0b0011:
                lb_mnemonic->Text = "MOV A, #" + int(im).ToString(); break;
            case 0b0100:
                lb_mnemonic->Text = im ? ("ADD B, A, #" + int(im).ToString()) : "MOV B, A"; break;
            case 0b0101:
                lb_mnemonic->Text = "ADD B, #" + int(im).ToString(); break;
            case 0b0110:
                lb_mnemonic->Text = im ? ("IN B + #" + int(im).ToString()) : "IN B"; break;
            case 0b0111:
                lb_mnemonic->Text = "MOV B, #" + int(im).ToString(); break;
            case 0b1000:
                switch (im) {
                case 0b0000: lb_mnemonic->Text = "ADD A, B"; break;
                case 0b0001: lb_mnemonic->Text = "NEG A"; break;
                case 0b0010: lb_mnemonic->Text = "NOT A"; break;
                case 0b0011: lb_mnemonic->Text = "OR A, B"; break;
                case 0b0100: lb_mnemonic->Text = "AND A, B"; break;
                case 0b0101: lb_mnemonic->Text = "XOR A, B"; break;
                case 0b0110: lb_mnemonic->Text = "SUB A, B"; break;
                case 0b0111: lb_mnemonic->Text = "OUT A"; break;
                case 0b1000: lb_mnemonic->Text = "LD A"; break;
                case 0b1001: lb_mnemonic->Text = "ST A"; break;
                case 0b1010: lb_mnemonic->Text = "LD B"; break;
                case 0b1011: lb_mnemonic->Text = "ST B"; break;
                case 0b1100: lb_mnemonic->Text = "MOV X, A"; break;
                case 0b1101: lb_mnemonic->Text = "MOV Y, A"; break;
                case 0b1110: lb_mnemonic->Text = "INC XY"; break;
                case 0b1111: lb_mnemonic->Text = "JMP XY"; break;
                }
                break;
            case 0b1001:
                lb_mnemonic->Text = im ? ("OUT B + #" + int(im).ToString()) : "OUT B"; break;
            case 0b1010:
                lb_mnemonic->Text = "JZ #" + int(im).ToString(); break;
            case 0b1011:
                lb_mnemonic->Text = "OUT #" + int(im).ToString(); break;
            case 0b1100:
                lb_mnemonic->Text = "MOV Y, #" + int(im).ToString(); break;
            case 0b1101:
                lb_mnemonic->Text = "MOV X, #" + int(im).ToString(); break;
            case 0b1110:
                lb_mnemonic->Text = "JNC #" + int(im).ToString(); break;
            case 0b1111:
                lb_mnemonic->Text = "JMP #" + int(im).ToString(); break;
            }
            mPanel->Controls->Add(lb_mnemonic);

            break;
        }
        default:
            break;
        }
    }
    mPanel->ResumeLayout();

    Highlight(pc);
}

System::Void TD4mEmulator::MemoryView::Highlight(Int16 index) {
	mPosLabels[mHighlighted]->ForeColor = Color::Black;
	mPosLabels[index]->ForeColor = Color::Red;
	mHighlighted = index;
}

System::Void TD4mEmulator::MemoryView::SetMode(DataDisplayMode mode) {
    if (mode == mMode) {
        return;
    }
    mMode = mode;
    Build();
}

System::Void TD4mEmulator::MemoryView::Update(Byte position) {
    Memory^ memory = mEmulator->GetMemory();
    Byte value = mIsRam ? memory->ReadRAM(position) : memory->ReadROM(position);

    if (mMode == DataDisplayMode::BINARY) {
        Byte bits_per_word = mIsRam ? 4 : 8;
        
        for (Byte bit = 0; bit < bits_per_word; bit++) {
            mCheckBoxes[position * bits_per_word + bit]->Checked = (value & (1 << bit)) != 0;
        }
    }
    else {
        mHexBoxes[position]->Text = value.ToString("X2");
    }
}


System::Void TD4mEmulator::MemoryView::Bit_Changed(System::Object^ sender, System::EventArgs^ e) {
    Memory^ memory = mEmulator->GetMemory();

    Byte bits_per_word = mIsRam ? 4 : 8;

    CheckBox^ box = (CheckBox^)sender;
    Int16 bit_index = Convert::ToInt16(box->Name->Substring(1));
    Byte position = bit_index / bits_per_word;
    bit_index &= mIsRam ? 3 : 7;
    Byte bit = 1 << bit_index;
    Byte value = mIsRam ? memory->ReadRAM(position) : memory->ReadROM(position);
    if (box->Checked) {
        value |= bit;
    }
    else {
        value &= ~bit;
    }
    if (mIsRam) {
        memory->WriteRAM(position, value);
    }
    else {
        memory->WriteROM(position, value);
    }
}