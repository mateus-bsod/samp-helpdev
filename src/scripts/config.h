#ifndef CONFIG_H
#define CONFIG_H


#include <iostream>
#include <string>
#include <fstream>

#include <windows.h>
#include <shellapi.h>

#include "../json.hpp"

using json = nlohmann::json;

struct Programas {
    std::string textdraw;
    std::string map;
    std::string server;
};

json loadConfig(const std::string& arquivo);
Programas loadServer(const json& config);


#endif