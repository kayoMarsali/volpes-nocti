#include "kstring.h"
#include <string.h>
#include <stdarg.h>

namespace utils::Strings {

    u64 Length(const char* str) {
        return strlen(str);
    }
    char* Duplicate(const char* str) {
        u64 length = Length(str);
        char* copy = (char*)malloc(length + 1);
        if (!copy) {
            return nullptr;
        }
        memcpy(copy, str, length + 1);
        return copy;
    }

    // Case-sensitive string comparison. True if the same, otherwise false.
    b8 Equals(const char* str0, const char* str1) {
        return strcmp(str0, str1) == 0;
    }

    i32 Format(char* dest, const char* format, ...) {
        if (dest) {
            va_list arg_ptr;
            va_start(arg_ptr, format);
            i32 written = FormatV(dest, format, arg_ptr);
            va_end(arg_ptr);
            return written;
        }
        return -1;
    }

    i32 FormatV(char* dest, const char* format, void* va_listp) {
        if (dest) {
            // Big, but can fit on the stack.
            char buffer[15360];
            memset(buffer, 0, sizeof(buffer));
            i32 written = vsnprintf(buffer, 15360, format, (va_list)((u64)va_listp));
            if (written > 0) {
                buffer[written] = 0;
            }
        memcpy(dest, buffer, written + 1LLU);

            return written;
        }
        return -1;
    }

    b8 Concat(char* dest, const char* src, i32 max_len) {
        i32 len = Length(dest) + Length(src);
        if(len > max_len) {
            return false;
        }

        strcat_s(dest, 500, src);

        return true;
    }
}