#pragma once

#include "defines.h"

typedef struct FileHandle {
    void* handle;
    b8 isValid;
} FileHandle;

typedef enum FileModes {
    READ = 0x1,
    WRITE = 0x2
} FileModes;

namespace utils {
    namespace filesystem {

        #define MAX_PATH_BUFFER 512
        #define MAX_LINE_BUFFER 16000

        b8 Exists(const char* path);

        b8 Open(const char* path, FileModes mode, b8 binary, FileHandle* outHandle);

        void Close(FileHandle* handle);

        b8 ReadLine(FileHandle* handle, char** lineBuf);

        b8 WriteLine(FileHandle* handle, const char* text);

        b8 Read(FileHandle* handle, u64 size, void* outData, u64* outBytesRead);

        b8 ReadAllBytes(FileHandle* handle, u8** outData, u64* outBytesRead);

        b8 Write(FileHandle* handle, u64 size, const void* data, u64* outBytesWritten);
    }
}