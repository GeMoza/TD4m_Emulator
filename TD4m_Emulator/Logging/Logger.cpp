// Logger.cpp

#include "Logger.h"
#include <fstream>
#include <msclr/marshal_cppstd.h>

Logger::Logger() : logToUI(nullptr), logFilePath(nullptr), logToFile(false) {}

Logger::Logger(String^ logFilePath) : logToUI(nullptr), logFilePath(logFilePath), logToFile(true) {}

void Logger::AttachToInterface(Action<String^>^ logToUI) { this->logToUI = logToUI; }


void Logger::DetachInterface() { logToUI = nullptr; }


// Преобразование System::String^ в std::string
std::string ConvertToString(System::String^ managedString) {
    using namespace System::Runtime::InteropServices;
    const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(managedString)).ToPointer();
    std::string nativeString = chars;
    Marshal::FreeHGlobal(System::IntPtr((void*)chars));
    return nativeString;
}

void Logger::Log(String^ message) {
    if (logToUI != nullptr) {
        logToUI(message);
    }

    if (logToFile && logFilePath != nullptr) {
        std::ofstream logFile(ConvertToString(logFilePath), std::ios::app);
        if (logFile.is_open()) {
            logFile << ConvertToString(message) << std::endl;
            logFile.close();
        }
    }
}


void Logger::LogRangeError(String^ regName, Byte maxValue) {
    String^ message = "Error: Value for " + regName + " must be between 0 and " + (maxValue - 1) + ".";
    Log(message);
    throw gcnew ArgumentOutOfRangeException(regName, message);
}


void Logger::LogAndThrow(String^ errorType, String^ errorMessage) {
    String^ message = "Error: " + errorMessage;
    Log(message);
    if (errorType == "Operands") {
        throw gcnew ArgumentNullException(errorType, message);
    }
    else if (errorType == "RangeError") {
        throw gcnew ArgumentOutOfRangeException(errorType, message);
    }
    else {
        throw gcnew Exception(message);
    }
}
