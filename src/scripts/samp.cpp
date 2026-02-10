
#include "./samp.h"

SAMP samp;

bool start_samp_server(const std::string& full_path)
{
    if (full_path.empty())
        return false;

    std::filesystem::path exePath(full_path);

    if (!std::filesystem::exists(exePath))
        return false;

    std::string workDir = exePath.parent_path().string();

    STARTUPINFOA si{};
    PROCESS_INFORMATION pi{};
    si.cb = sizeof(si);

    std::string cmd = "\"" + exePath.string() + "\"";
    std::vector<char> cmdBuffer(cmd.begin(), cmd.end());
    cmdBuffer.push_back('\0');

    BOOL ok = CreateProcessA(nullptr, cmdBuffer.data(), nullptr, nullptr, FALSE, CREATE_NEW_CONSOLE, nullptr, workDir.c_str(), &si, &pi);
    if (!ok)
        return false;

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return true;
}


SAMP loadSAMP()
{

    HKEY hKey;
    if (RegOpenKeyExA(HKEY_CURRENT_USER, "Software\\SAMP", 0, KEY_READ, &hKey) != ERROR_SUCCESS)
        return {};

    char gtaPath[MAX_PATH]{};
    char playerName[MAX_PATH]{};
    DWORD size = sizeof(gtaPath);
    DWORD type = REG_SZ;

    if (RegQueryValueExA(hKey, "gta_sa_exe", nullptr, &type, reinterpret_cast<LPBYTE>(gtaPath), &size) != ERROR_SUCCESS)
    {
        RegCloseKey(hKey);
        return {};
    }

    size = sizeof(playerName);
    if (RegQueryValueExA(hKey, "PlayerName", nullptr, &type, reinterpret_cast<LPBYTE>(playerName), &size) != ERROR_SUCCESS)
    {
        RegCloseKey(hKey);
        return {};
    }

    std::filesystem::path gtaDirPath = gtaPath;
    samp.GTA_DIR = gtaDirPath.parent_path().string() + "\\";

    samp.PlayerName = std::string(playerName);
    std::replace(samp.PlayerName.begin(), samp.PlayerName.end(), '_', ' ');

    RegCloseKey(hKey);
    return samp;
}