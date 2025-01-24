// Logger.h

#pragma once

using System::Byte;
using System::String;

public ref class Logger {
public:
    using LogLineHandler = System::Action<String^>;

    Logger();                                                   // ����������� �� ��������� ��� ������������

    Logger(String^ logFilePath);                                // ����������� ��� ����������� � ����

    void AttachToInterface(LogLineHandler^ logToUI);            // ����������� ��� ������ ����� � UI

    void Log(String^ message);                                  // �������� ���������

    void LogRangeError(String^ regName, Byte maxValue);
    void LogAndThrow(String^ errorType, String^ errorMessage);

    void DetachInterface();                                     // ������������� �� ����������������� ����������
protected:
    LogLineHandler^ logToUI;   // ������� ��� ����������� � UI
    String^ logFilePath;       // ���� � ����� �������
    bool logToFile;            // ���� ����������� ������
};
