#pragma once
#include "defines.h"

namespace utils::Strings {
u64 Length(const char* str);

char* Duplicate(const char* str);

b8 Equals(const char* str0, const char* str1);

// Performs string formatting to dest given format string and parameters.
i32 Format(char* dest, const char* format, ...);

//
/**
* Performs variadic string formatting to dest given format string and va_list.
* @param dest The destination for the formatted string.
* @param format The string to be formatted.
* @param va_list The variadic argument list.
* @returns The size of the data written.
*/
i32 FormatV(char* dest, const char* format, void* va_list);

b8 Concat(char* dest, const char* src, i32 max_len);
}