#include <windows.h>
#include <stdio.h>

BOOL TouchFile(const char *file);
BOOL TouchFile(HANDLE hFile);

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; ++i)
    {
        TouchFile(argv[i]);
    }

    return 0;
}

BOOL TouchFile(const char *file)
{
    HANDLE hFile = CreateFile(file, FILE_WRITE_ATTRIBUTES, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        return FALSE;
    }
    BOOL result = TouchFile(hFile);
    CloseHandle(hFile);
    return result;
}

BOOL TouchFile(HANDLE hFile)
{
    SYSTEMTIME st;
    FILETIME ft;

    GetSystemTime(&st);
    if (! SystemTimeToFileTime(&st, &ft))
    {
        return FALSE;
    }
    return SetFileTime(hFile, (const FILETIME *)NULL, (const FILETIME *)NULL, &ft);
}
