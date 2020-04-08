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
#include "Logger.h"
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

float actionTimer = 60;
int actionType = GameActionTypes::Siren;

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
				originalActionFunc(*strangeNumber,actionType,actionTimer);
			}
			if (GetAsyncKeyState('G') & 0x8000)
			{
				overriddenGiveWeapon(HutchWeapons::NpcRifle, 2);
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
			actionTimer = std::stof(params);
			cout << "Set action time to "<<actionTimer << endl;
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

			Logger::Debug("ADDON STARTED\n");

			HANDLE input = CreateThread(NULL, 0, Input, NULL, 0, NULL);

			HANDLE thread = CreateThread(NULL, 0, keysLoop, NULL, 0, NULL);

			DetourTransactionBegin();
			DetourUpdateThread(GetCurrentThread());

			DetourAttach(& (PVOID&) originalCreateFileA, (PVOID)overriddenCreateFileA);
			//DetourAttach(&(PVOID &)originalReadFile, (PBYTE)overriddenReadFile);

			DetourAttach(&(PVOID &)originalActionFunc, (PVOID)overriddenActionFunc);

			DetourAttach(&(PVOID &)originalToBeDefined, (PBYTE)overriddenToBeDefined);

			//CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)DirectInputHook, NULL, NULL, NULL);
			//DirectInputHook();

			DetourAttach(&(PVOID&)originalResource, (PVOID)overriddenResource);

			DetourAttach(&(PVOID&)originalToggleSirenSnd, (PVOID)hookedToggleSirenSnd);

			DetourAttach(&(PVOID&)sub50E0D1, (PVOID)hookedSub_50E0D1);
			DetourAttach(&(PVOID&)sub50E4DA, (PVOID)hookedSub_50E4DA);
			DetourAttach(&(PVOID&)sub45CF74, (PVOID)hookedSub_45CF74);
			//DetourAttach(&(PVOID&)sub45AA9B, (PVOID)hookedSub_45AA9B);
			DetourAttach(&(PVOID&)sub45A3BC, (PVOID)hookedSub_45A3BC);
			DetourAttach(&(PVOID&)originalGiveWeapon, (PVOID)overriddenGiveWeapon);

			initDI8Hook2();

			DetourTransactionCommit();
			break;
		}
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		{

		}
		case DLL_PROCESS_DETACH:
		{
			Logger::Close();
			break;
		} 
    }
    return TRUE;
}
