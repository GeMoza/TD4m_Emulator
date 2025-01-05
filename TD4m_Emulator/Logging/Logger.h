// Logger.h

#pragma once

using namespace System;

public ref class Logger {
public:
    Logger();                                           // Конструктор по умолчанию без логгирования

    Logger(String^ logFilePath);                        // Конструктор для логирования в файл

    void AttachToInterface(Action<String^>^ logToUI);   // Конструктор для вывода логов в UI

    void Log(String^ message);                          // Записать сообщение

    void LogRangeError(String^ regName, Byte maxValue);
    void LogAndThrow(String^ errorType, String^ errorMessage);

    void DetachInterface();                             // Отсоединитесь от пользовательского интерфейса

protected:
    Action<String^>^ logToUI;   // Делегат для регистрации в UI
    String^ logFilePath;        // Путь к файлу журнала
    bool logToFile;             // Флаг регистрации файлов
};
