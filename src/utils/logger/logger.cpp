#include "logger.h"
#include "utils/strings/kstring.h"
#include "utils/filesystem/filesystem.h"
#include <stdio.h>
#include <stdarg.h>
#include <memory.h>
#include <windows.h>

namespace utils {
    namespace Logger {

        #define LOG_FILE_BUFFER 280
        #define LOG_BUFFER_MAX 1024
        char *LogBuffer = nullptr;

        static const char *logFilePath = "./console.log";
        static FileHandle logFileHandle = {};

        void AppendToLogFile(const char* message);
        void ConsoleWrite(const char* message, u8 color);
        void ConsoleWriteError(const char* message, u8 color);

        b8 Initialize() {
            LogBuffer = (char *)malloc(sizeof(char)*LOG_BUFFER_MAX);
            memset(LogBuffer, 0, sizeof(char)*LOG_BUFFER_MAX);
            if(!utils::filesystem::Open(logFilePath, FileModes::WRITE, false, &logFileHandle)) {

                ConsoleWriteError("ERROR: Unable to open console.log for writing.", utils::LogLevel::LL_ERROR);
                return false;
            }

            return true;
        }

        void Shutdown() {
            if(utils::Strings::Length(LogBuffer) > 1) {
                AppendToLogFile(LogBuffer);
                memset(LogBuffer, 0, sizeof(char) * LOG_BUFFER_MAX);
            }
            utils::filesystem::Close(&logFileHandle);
            free(LogBuffer);
            LogBuffer = nullptr;
        }


        void AppendToLogFile(const char* message) {

            if (logFileHandle.isValid) {
                u64 length = utils::Strings::Length(message);
                u64 written = 0;
                if (!utils::filesystem::Write(&logFileHandle, length, message, &written)) {
                    ConsoleWriteError("ERROR writing to console.log", utils::LogLevel::LL_ERROR);
                }
            }
        }


        void LogOutput(LogLevel level, const char* message...) {
            const char* LevelStrings[6] = { "[FATAL]: ","[ERROR]: ", "[WARN]:  ", "[INFO]:  ", "[DEBUG]: ", "[TRACE]: " };
            b8 isError = level < 2;

            char OutMessage[LOG_MESSAGE_BUFFER];
            memset(OutMessage, 0, sizeof(OutMessage));


            va_list args;
            va_start(args, message);
            utils::Strings::FormatV(OutMessage, message, args);
            va_end(args);

            utils::Strings::Format(OutMessage, "%s%s\n", LevelStrings[level], OutMessage);


            if (isError) {
                ConsoleWriteError(OutMessage, level);
            } else {
                ConsoleWrite(OutMessage, level);
            }
            utils::Strings::Concat(LogBuffer, OutMessage, LOG_BUFFER_MAX);

            if(utils::Strings::Length(LogBuffer) > LOG_FILE_BUFFER) {
                AppendToLogFile(LogBuffer);
                memset(LogBuffer, 0, sizeof(char) * LOG_BUFFER_MAX);
            }
        }



        void ReportAssertionFailure(const char* expression, const char* message, const char* file, i32 line) {
            LogOutput(utils::LogLevel::LL_FATAL, "Assertion Failure: %s, message: '%s', in file: %s line: %d", expression, message, file, line);
        }


        void ConsoleWrite(const char* message, u8 color) {
            HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
            static u8 levels[6] = { 64, 4, 6, 2, 1, 8 };
            SetConsoleTextAttribute(consoleHandle, levels[color]);

            OutputDebugStringA(message);
            u64 length = strlen(message);
            LPDWORD numberWritten = 0;
            WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), message, (DWORD)length, numberWritten, 0);

            SetConsoleTextAttribute(consoleHandle, (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY));
        }
        void ConsoleWriteError(const char* message, u8 color) {
            HANDLE consoleHandle = GetStdHandle(STD_ERROR_HANDLE);
            static u8 levels[6] = { 64, 4, 6, 2, 1, 8 };
            SetConsoleTextAttribute(consoleHandle, levels[color]);

            OutputDebugStringA(message);
            u64 length = strlen(message);
            LPDWORD numberWritten = 0;
            WriteConsoleA(GetStdHandle(STD_ERROR_HANDLE), message, (DWORD)length, numberWritten, 0);

            SetConsoleTextAttribute(consoleHandle, (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY));
        }
    }
}