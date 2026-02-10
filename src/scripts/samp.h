#pragma once
#ifndef SAMP_H
#define SAMP_H

#include <windows.h>
#include <string>
#include <vector>
#include <algorithm>
#include <filesystem>

#pragma once
struct SAMP {
    std::string PlayerName;
    std::string GTA_DIR;
};
extern SAMP samp;

bool start_samp_server(const std::string& full_path);
SAMP loadSAMP();

#endif