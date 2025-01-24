// Logger.h

#pragma once

using System::Byte;
using System::String;

public ref class Logger {
public:
    using LogLineHandler = System::Action<String^>;

    Logger();                                                   // Конструктор по умолчанию без логгирования

    Logger(String^ logFilePath);                                // Конструктор для логирования в файл

    void AttachToInterface(LogLineHandler^ logToUI);            // Конструктор для вывода логов в UI

    void Log(String^ message);                                  // Записать сообщение

    void LogRangeError(String^ regName, Byte maxValue);
    void LogAndThrow(String^ errorType, String^ errorMessage);

    void DetachInterface();                                     // Отсоединиться от пользовательского интерфейса
protected:
    LogLineHandler^ logToUI;   // Делегат для регистрации в UI
    String^ logFilePath;       // Путь к файлу журнала
    bool logToFile;            // Флаг регистрации файлов
};
