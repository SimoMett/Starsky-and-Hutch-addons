#pragma once

#define _CRT_SECURE_NO_WARNINGS
//Simple logger made by me LOL, DonSimonetti

#include <cstdio>
#include <cstdarg>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>

#define LOG_FILENAME "StarskyPC_addon.log"
#define LOG_TAG "[ADDON]"

using namespace std;

namespace Logger
{
	static ofstream* logFile;

	void Debug(const char* str, ...);
	void Error(const char* str, ...);
	void Print(stringstream& stream);
	void Flush();
	void Close();
}