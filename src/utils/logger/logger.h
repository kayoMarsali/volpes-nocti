#pragma once
#include "defines.h"

namespace utils {


    typedef enum LogLevel {
        LL_FATAL = 0,
        LL_ERROR = 1,
        LL_WARN  = 2,
        LL_INFO  = 3,
        LL_DEBUG = 4,
        LL_TRACE = 5
    } LogLevel;
    namespace Logger {
        b8 Initialize();
        void Shutdown();

        
        void LogOutput(LogLevel level, const char* message...);
    };
}

#define LOG_WARN_ENABLED  1
#define LOG_INFO_ENABLED  1
#if defined(_DEBUG)
	#define LOG_DEBUG_ENABLED 1
	#define LOG_TRACE_ENABLED 1
#elif defined(_NDEBUG)
	#define LOG_DEBUG_ENABLED 0
	#define LOG_TRACE_ENABLED 0
#else
	#define LOG_DEBUG_ENABLED 0
	#define LOG_TRACE_ENABLED 1
#endif


#define LOG_MESSAGE_BUFFER 4096

#define K_LOG_FATAL(message, ...) utils::Logger::LogOutput(utils::LogLevel::LL_FATAL, message, ##__VA_ARGS__)

#define K_LOG_ERROR(message, ...) utils::Logger::LogOutput(utils::LogLevel::LL_ERROR, message, ##__VA_ARGS__)

#if LOG_WARN_ENABLED == 1
#define K_LOG_WARN(message, ...)  utils::Logger::LogOutput(utils::LogLevel::LL_WARN,  message, ##__VA_ARGS__)
#else
#define K_LOG_WARN(message, ...)
#endif

#if LOG_INFO_ENABLED == 1
#define K_LOG_INFO(message, ...)  utils::Logger::LogOutput(utils::LogLevel::LL_INFO,  message, ##__VA_ARGS__)
#else
#define K_LOG_INFO(message, ...)
#endif

#if LOG_DEBUG_ENABLED == 1
#define K_LOG_DEBUG(message, ...)  utils::Logger::LogOutput(utils::LogLevel::LL_DEBUG,  message, ##__VA_ARGS__)
#else
#define K_LOG_DEBUG(message, ...)
#endif

#if LOG_TRACE_ENABLED == 1
#define K_LOG_TRACE(message, ...)  utils::Logger::LogOutput(utils::LogLevel::LL_TRACE,  message, ##__VA_ARGS__)
#else
#define K_LOG_TRACE(message, ...)
#endif