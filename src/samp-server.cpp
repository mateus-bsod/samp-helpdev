#include <iostream>
#include <string>

#include "./scripts/port.h"
#include "./scripts/config.h"
#include "./scripts/samp.h"
#include "./scripts/window.h"

#include <algorithm>
#include <windows.h>
#include <psapi.h>

// Main
int main(int argc, char* argv[]) {

    system("cls");

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return 0;

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) return 0;

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);

    // 

    loadSAMP();
    if (samp.GTA_DIR.empty() || !std::filesystem::is_directory(samp.GTA_DIR))
    {
        std::cout << "[-] Invalid GTA SA Dir -> " << samp.GTA_DIR << "\n";
        system("pause");
        exit(0);
    }

    if (!std::filesystem::exists((samp.GTA_DIR + "samp.exe")) && !std::filesystem::is_regular_file((samp.GTA_DIR + "samp.exe")))
    {
        std::cout << "[-] Invalid SA:MP exe -> " << (samp.GTA_DIR + "samp.exe") << "\n";
        system("pause");
        exit(0);
    }


    // Settings
    json config = loadConfig("./config.json");
    if (config.empty())
    {
        std::cout << "[-] Invalid config.json" << "\n";
        system("pause");
        exit(0);
    }

    // Variaveis
    int port = 7777, run_server = -1;
    bool verify = true, run = false, portinuse = false;
    std::string password = "";

    std::cout << "\x1b[0m[+] Hi \x1b[1;96m" << samp.PlayerName << "\x1b[0m" << std::endl;

    Programas programas = loadServer(config);

    // Args
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        std::transform(arg.begin(), arg.end(), arg.begin(), [](unsigned char c) { return std::tolower(c); });

        // Server Args
        if (run_server == -1)
        {
            if (arg == "-td") run_server = 1;
            else if (arg == "-sv") run_server = 2;
            else if (arg == "-map") run_server = 3;
        }

        // Outros Args
        if (arg == "-h" || arg == "--help" || arg == "-help")
        {
            std::cout << "\nUsage:\n";
            std::cout << "  -td           : Run textdraw mode (Configure it in the JSON file.)\n";
            std::cout << "  -sv           : Run server mode (Configure it in the JSON file.)\n";
            std::cout << "  -map          : Run map-editor mode (Configure it in the JSON file.)\n";
            std::cout << "  -v            : Ignore port verification being used.\n";
            std::cout << "  -r            : Open GTA along with the server.\n";
            std::cout << "  --pass <num>  : Set server password\n";
            std::cout << "  --port <num>  : Set server port\n";
            std::cout << "  -h, --help    : Show this help message\n";
            system("pause");
            exit(0);
        }

        if (arg == "-v") verify = false;
        if (arg == "-r") run = true;

        if (arg == "--pass" && i + 1 < argc) {
            password = std::stoi(argv[++i]);
        }

        if (arg == "--port" && i + 1 < argc) {
            int p = std::stoi(argv[++i]);
            if (p >= 1 && p <= 65535) {
                port = p;
            }
            else
            {
                std::cout << "[-] Invalid PORT: " << p << "\n";
                system("pause");
                exit(0);
            }
        }
    }

    if (isPortInUse(port) || isRunning(programas.server) || isRunning(programas.textdraw) || isRunning(programas.map))
    {
        std::cout << "[-] There's already a SAMP server running!" << std::endl;
        system("pause");
        exit(0);
    }

    // Lol
    if (verify)
    {
        if (isPortInUse(port))
        {
            std::cout << "\x1b[0m[+] Server \x1b[1;92mrunning\x1b[0m on \x1b[1m : "  << port << "\x1b[0m " << std::endl;
            portinuse = true;
        }
        else std::cout << "\x1b[0m[-] The server is \x1b[1;31mnot \x1b[0mrunning\x1b[1m : " << port << "\x1b[0m " << std::endl;
    }
    else std::cout << "\x1b[0m[/] Server running on \x1b[1m" << port << "\x1b[0m " << std::endl;

    if (run_server == 1) start_samp_server(programas.textdraw);
    else if (run_server == 2) start_samp_server(programas.server);
    else if (run_server == 3) start_samp_server(programas.map);

    if (run)
    {
        if (run_server == -1/* && verify && !portinuse)*/)
        {
            std::cout << "[-] No ports started\n";
            system("pause");
            exit(0);
        }

        if (!isRunning(samp.GTA_DIR))
        {
            std::string args = "127.0.0.1 " + password;
            start_process((samp.GTA_DIR + "samp.exe"), args, samp.GTA_DIR);
        }
        else
            std::cout << "[+] GTA SA is already open, maximize the screen!\n";
    }
    return 0;
}

