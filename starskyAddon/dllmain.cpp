#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <Windows.h>
#include <Psapi.h>
#include <fstream>

using std::cout;
using std::endl;

void CreateConsole()
{
	AllocConsole();

	DWORD dwMode;
	GetConsoleMode(GetConsoleWindow(), &dwMode);
	dwMode |= ENABLE_LINE_INPUT;
	dwMode |= ENABLE_INSERT_MODE | ENABLE_EXTENDED_FLAGS;
	//SetConsoleMode(GetConsoleWindow(), dwMode);
	
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
	freopen("CONIN$", "r", stdin);
}

void ActivatePointsCheat()
{
	short* instr = (short*)0x4FB314;

	BYTE newInstr[] = { 0x90,0x90 };

	WriteProcessMemory(GetCurrentProcess(), (void*)instr, &newInstr, 2, 0);

	float** points;
	points = (float**)0x692894;

	**points = 1000.0;
	
	cout << "ActivatePointCheat()" << endl;
}

DWORD WINAPI keysLoop(void * data)
{
	while (true)
	{
		Sleep(100);
		if (GetForegroundWindow() != GetConsoleWindow())
		{
			if (GetAsyncKeyState('B') & 0x8000)
			{
				ActivatePointsCheat();
			}
		}
	}
}

DWORD WINAPI Input(void* data)
{
	std::string input;
	while (true)
	{
		std::cin >> input;

		cout << "Command: " << input << endl;
	}
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
	{
		CreateConsole();

		HANDLE thread = CreateThread(NULL, 0, keysLoop, NULL, 0, NULL);

		printf("ADDON STARTED\n");
		
		HANDLE input = CreateThread(NULL, 0, Input, NULL, 0, NULL);
		break;
	}
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
	{

	}
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}