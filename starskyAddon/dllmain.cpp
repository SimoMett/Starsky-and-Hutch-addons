#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <Windows.h>
#include <Psapi.h>
#include <fstream>

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include "detours/detours.h"
#include "StarskyAddresses.h"
#include "OverriddenFunctions.h"
#include "DInputHook.h"
#include "CheatMenu.h"

using std::cout;
using std::endl;
using std::string;

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
	short* instr = (short*)GAME_ASM_POINTS_UPDATE;//This address maybe is incorrect. It bugs collision with dynamic objects

	BYTE newInstr[] = { 0x90,0x90 };

	WriteProcessMemory(GetCurrentProcess(), (void*)instr, &newInstr, 2, 0);

	float** points=(float**)GAME_POINTS_DPTR;

	**points = 1000.0;
	
	cout << "ActivatePointCheat()" << endl;
}

float actionFactor = 4.5;
int actionType = GameActionTypes::Turbo;

DWORD WINAPI keysLoop(void * data)
{
	while (true)
	{
		Sleep(100);
		if (GetForegroundWindow() != GetConsoleWindow())
		{
			/*if (GetAsyncKeyState('B') & 0x8000) //disabled for now
			{
				ActivatePointsCheat();
			}*/

			if (GetAsyncKeyState('M') & 0x8000)
			{
				if (!CheatMenu::IsShown())
					CheatMenu::Show();
				else
					CheatMenu::Hide();
			}

			if (GetAsyncKeyState('T') & 0x8000)
			{
				int* strangeNumber = (int*)0x692450;
				originalActionFunc(*strangeNumber,actionType,actionFactor);
			}
		}
	}
}

DWORD WINAPI Input(void* data)
{
	while (true)
	{
		std::string input;
		std::getline(std::cin, input);

		std::string cmd (input.substr(0, input.find_first_of(" ")));
		std::string params(input.substr(input.find_first_of(" ")+1));

		if (cmd == "setactiontime")
		{
			actionFactor = std::stof(params);
			cout << "Set action time to "<<actionFactor << endl;
		}
		if (cmd == "setactiontype")
		{
			actionType = std::stoi(params);
			cout << "Set action type to " << actionType << endl;
		}
	}
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
	{
		CreateConsole();

		printf("ADDON STARTED\n");

		HANDLE input = CreateThread(NULL, 0, Input, NULL, 0, NULL);

		HANDLE thread = CreateThread(NULL, 0, keysLoop, NULL, 0, NULL);

		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());

		DetourAttach(& (PVOID&) originalCreateFileA, (PVOID)overriddenCreateFileA);
		//DetourAttach(&(PVOID &)originalReadFile, (PBYTE)overriddenReadFile);

		DetourAttach(&(PVOID &)originalActionFunc, (PVOID)overriddenActionFunc);

		DetourAttach(&(PVOID &)originalToBeDefined, (PBYTE)overriddenToBeDefined);

		//CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)DirectInputHook, NULL, NULL, NULL);
		DirectInputHook();

		DetourTransactionCommit();		
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
