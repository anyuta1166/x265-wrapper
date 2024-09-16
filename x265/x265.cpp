// x265.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <process.h>
#include <windows.h>
#include <string>

int wmain(int argc, wchar_t* argv[])
{
    int count;
    const wchar_t** args;

    int ac = argc + 2;
    args = new const wchar_t*[ac];

    for (count = 0; count < argc; count++) {
        args[count] = argv[count];
    }

    args[ac - 3] = L"--input";
    args[ac - 2] = L"-";
    args[ac - 1] = NULL;

    wchar_t szFileName[MAX_PATH];
    GetModuleFileNameW(NULL, szFileName, MAX_PATH);

    std::wstring filePath(szFileName);
    std::wstring dirName = filePath.substr(0, filePath.find_last_of(L"\\"));
    std::wstring newName = dirName.append(L"\\x265_.exe");

    args[0] = newName.c_str();

    for (count = 0; count < ac; count++) {
        if (args[count] != NULL) {
            std::wstring originalString = args[count];
            if (originalString.find(' ') != std::wstring::npos) {
                std::wstring* convertedString = new std::wstring;
                (*convertedString) = L"\"" + originalString + L"\"";
                args[count] = (*convertedString).c_str();
            }
        }
    }

    _wexecvp(newName.c_str(), args);

    return 0;
}

