#include "filesystem.h"

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "utils/logger/logger.h"


#define MAX_LINE_BUFFER 16000

namespace utils::filesystem {

    b8 Exists(const char* path) {
        struct stat buffer;
        return stat(path, &buffer) == 0;
    }

    b8 Open(const char* path, FileModes mode, b8 binary, FileHandle* outHandle) {
        outHandle->isValid = false;
        outHandle->handle = 0;
        const char* modeStr;

        if ((mode & FileModes::READ) != 0 && (mode & FileModes::WRITE) != 0) {
            modeStr = binary ? "w+b" : "w+";
        } else if ((mode & FileModes::READ) != 0 && (mode & FileModes::WRITE) == 0) {
            modeStr = binary ? "rb" : "r";
        } else if ((mode & FileModes::READ) == 0 && (mode & FileModes::WRITE) != 0) {
            modeStr = binary ? "wb" : "w";
        } else {
            K_LOG_ERROR("Invalid mode passed while trying to open file: '%s'", path);
            return false;
        }
        FILE* file = fopen(path, modeStr);
        if (!file) {
            K_LOG_ERROR("Error opening file: '%s'", path);
            return false;
        }

        outHandle->handle = file;
        outHandle->isValid = true;

        return true;
    }

    void Close(FileHandle* handle) {
        if (handle->handle) {
            fclose((FILE*)handle->handle);
            handle->handle = 0;
            handle->isValid = false;
        }
    }

    b8 ReadLine(FileHandle* handle, char** lineBuf) {
        if (handle->handle) {
            char buffer[MAX_LINE_BUFFER];
            if (fgets(buffer, MAX_LINE_BUFFER, (FILE*)handle->handle) != 0) {
                u64 length = strlen(buffer);
                *lineBuf = (char*)malloc((sizeof(char) * length) + 1);
                strcpy(*lineBuf, buffer);
                return true;
            }
        }
        return false;
    }

    b8 WriteLine(FileHandle* handle, const char* text) {
        if (handle->handle) {
            i32 result = fputs(text, (FILE*)handle->handle);
            if (result != EOF) {
                result = fputc('\n', (FILE*)handle->handle);
            }

            fflush((FILE*)handle->handle);
            return result != EOF;
        }

        return false;
    }

    b8 Read(FileHandle* handle, u64 size, void* outData, u64* outBytesRead) {
        if (handle->handle && outData) {
            *outBytesRead = fread(outData, 1, size, (FILE*)handle->handle);
            if (*outBytesRead != size) {
                return false;
            }
            return true;
        }
        return false;
    }

    b8 ReadAllBytes(FileHandle* handle, u8** outData, u64* outBytesRead) {
        if (handle->handle) {
            fseek((FILE*)handle->handle, 0, SEEK_END);
            u64 size = ftell((FILE*)handle->handle);
            rewind((FILE*)handle->handle);

            *outData = (u8*)malloc(sizeof(u8) * size);
            *outBytesRead = fread(*outData, 1, size, (FILE*)handle->handle);
            if (*outBytesRead != size) {
                free(*outData);
                return false;
            }
            return true;
        }
        return false;
    }

    b8 Write(FileHandle* handle, u64 size, const void* data, u64* outBytesWritten) {
        if (handle->handle) {
            *outBytesWritten = fwrite(data, 1, size, (FILE*)handle->handle);
            if (*outBytesWritten != size) {
                return false;
            }
            fflush((FILE*)handle->handle);
            return true;
        }
        return false;
    }
}