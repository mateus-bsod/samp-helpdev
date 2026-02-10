#pragma once
#ifndef WINDOW_H
#define WINDOW_H

#include <windows.h>
#include <tlhelp32.h>
#include <string>
#include <vector>
#include <filesystem>

bool isRunning(const std::string& exeName);
	bool start_process(const std::string & exePath, const std::string & args, const std::string & workDir);

#endif