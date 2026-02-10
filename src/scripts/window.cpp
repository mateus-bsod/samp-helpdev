#include "./window.h"

bool start_process(const std::string& exePath, const std::string& args, const std::string& workDir)
{
    SHELLEXECUTEINFOA sei{};
    sei.cbSize = sizeof(sei);
    sei.fMask = SEE_MASK_NOCLOSEPROCESS;
    sei.lpVerb = "open";
    sei.lpFile = exePath.c_str();
    sei.lpParameters = args.c_str();
    sei.lpDirectory = workDir.c_str();
    sei.nShow = SW_SHOWNORMAL;

    if (!ShellExecuteExA(&sei))
        return false;

    CloseHandle(sei.hProcess);
    return true;
}

bool isRunning(const std::string& exeName) {
    std::wstring wExeName;
    if (!exeName.empty()) {
        int n = MultiByteToWideChar(CP_UTF8, 0, exeName.c_str(), (int)exeName.size(), NULL, 0);
        wExeName.resize(n);
        MultiByteToWideChar(CP_UTF8, 0, exeName.c_str(), (int)exeName.size(), &wExeName[0], n);
    }
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnap == INVALID_HANDLE_VALUE) return false;
    PROCESSENTRY32 pe; pe.dwSize = sizeof(pe);
    if (Process32First(hSnap, &pe)) {
        do {
            if (_wcsicmp(pe.szExeFile, wExeName.c_str()) == 0) { CloseHandle(hSnap); return true; }
        } while (Process32Next(hSnap, &pe));
    }
    CloseHandle(hSnap);
    return false;
}

