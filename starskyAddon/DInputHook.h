#pragma once

#include <iostream>
#include <Windows.h>

using std::cout;
using std::endl;

typedef int (WINAPI *DInputCreate)(int a, int b, int c, int d, int e);
DInputCreate originalDInputCreate;

int __stdcall hookedDInputCreate(int hInst, int version, int c, int d, int e);

void DirectInputHook()
{
	HMODULE hDInputModule=nullptr;
	do
	{
		hDInputModule=GetModuleHandle(TEXT("dinput8.dll"));
	}
	while (!hDInputModule);

	cout << "dinput8.dll found: "<<hDInputModule << endl;
	originalDInputCreate = (DInputCreate)GetProcAddress(hDInputModule, "DirectInput8Create");

	DetourAttach(&(PVOID &)originalDInputCreate,(PVOID) hookedDInputCreate);
}

int __stdcall hookedDInputCreate(int hInst, int version, int c, int d, int e)
{
	printf("hookedDInputCreate( %d, 0x%x, %d, %d, %d )\n", hInst, version, c, d, e);
	return originalDInputCreate(hInst, version, c, d, e);
}