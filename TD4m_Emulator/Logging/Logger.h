// Logger.h

#pragma once

using namespace System;

public ref class Logger {
public:
    Logger();                                           // ����������� �� ��������� ��� ������������

    Logger(String^ logFilePath);                        // ����������� ��� ����������� � ����

    void AttachToInterface(Action<String^>^ logToUI);   // ����������� ��� ������ ����� � UI

    void Log(String^ message);                          // �������� ���������

    void LogRangeError(String^ regName, Byte maxValue);
    void LogAndThrow(String^ errorType, String^ errorMessage);

    void DetachInterface();                             // ������������� �� ����������������� ����������

protected:
    Action<String^>^ logToUI;   // ������� ��� ����������� � UI
    String^ logFilePath;        // ���� � ����� �������
    bool logToFile;             // ���� ����������� ������
};
