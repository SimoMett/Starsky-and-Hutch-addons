#pragma once

#include <iostream>
#include <Windows.h>

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"dinput8.lib")

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

//method2
typedef BOOL(WINAPI* TranslateMessage_t)(const MSG*);
TranslateMessage_t originalTranslateMessage;

BOOL WINAPI hookedTranslateMessage(const MSG * msg)
{	
	if (msg->message == 0xff)
		printf("di8 %d: %d\n", msg->time, msg->message);
	return originalTranslateMessage(msg);
}

void initDI8Hook2()
{
	originalTranslateMessage = TranslateMessage;
	cout << "di8: " << DetourAttach(&(PVOID&)originalTranslateMessage, hookedTranslateMessage) << endl;
}

//method3
typedef HRESULT(WINAPI* IDirectInputDevice_GetDeviceData)(IDirectInputDevice8*, DWORD, LPDIDEVICEOBJECTDATA, LPDWORD, DWORD);

IDirectInputDevice_GetDeviceData originalGetDeviceState = nullptr;

void* HookVTableFunction(void* pVTable, void* fnHookFunc, int nOffset);
HRESULT overriddenGetDeviceData(IDirectInputDevice8* pThis, DWORD a, LPDIDEVICEOBJECTDATA b, LPDWORD c, DWORD d);

void initDI8Hook()
{
	HINSTANCE hInst = (HINSTANCE)GetModuleHandle(NULL);
	IDirectInput8* pDirectInput = nullptr;

	if (DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8W, (LPVOID*)&pDirectInput, NULL) != DI_OK)
	{
		cout << "E" << endl;
		return;
	}

	LPDIRECTINPUTDEVICE8 lpdiKeydoard;
	if (pDirectInput->CreateDevice(GUID_SysKeyboard, &lpdiKeydoard, NULL) != DI_OK)
	{
		pDirectInput->Release();
		cout << "E2" << endl;
		return;
	}
	cout << "OK" << endl;


	originalGetDeviceState = (IDirectInputDevice_GetDeviceData)HookVTableFunction(lpdiKeydoard, overriddenGetDeviceData, 10);
}

// By Timb3r
// Source: https://gamephreakers.com/2018/08/introduction-to-vtable-hooking/
void* HookVTableFunction(void* pVTable, void* fnHookFunc, int nOffset)
{
	intptr_t ptrVtable = *((intptr_t*)pVTable); // Pointer to our chosen vtable
	intptr_t ptrFunction = ptrVtable + sizeof(intptr_t) * nOffset; // The offset to the function (remember it's a zero indexed array with a size of four bytes)
	intptr_t ptrOriginal = *((intptr_t*)ptrFunction); // Save original address

	// Edit the memory protection so we can modify it
	MEMORY_BASIC_INFORMATION mbi;
	VirtualQuery((LPCVOID)ptrFunction, &mbi, sizeof(mbi));
	VirtualProtect(mbi.BaseAddress, mbi.RegionSize, PAGE_EXECUTE_READWRITE, &mbi.Protect);

	// Overwrite the old function with our new one
	*((intptr_t*)ptrFunction) = (intptr_t)fnHookFunc;

	// Restore the protection
	VirtualProtect(mbi.BaseAddress, mbi.RegionSize, mbi.Protect, &mbi.Protect);

	// Return the original function address incase we want to call it
	return (void*)ptrOriginal;
}

HRESULT overriddenGetDeviceData(IDirectInputDevice8* pThis, DWORD a, LPDIDEVICEOBJECTDATA b, LPDWORD c, DWORD d)
{
	cout << "getdevicedata" << endl;
	HRESULT res = originalGetDeviceState(pThis,a,b,c,d);
	if (res == DI_OK)
	{
		cout << ">tap" << endl;
	}
	return res;
}