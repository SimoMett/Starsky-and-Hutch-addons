#pragma once

#include <iostream>
#include <Windows.h>

#include "EasyDetour.h"

using std::cout;
using std::endl;

//Types definitions

typedef void (*ActionFuncType)(int a, int type, float time);

typedef HANDLE(WINAPI* CreateFileAFuncType)(LPCSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE);

typedef BOOL(WINAPI* ReadFileFuncType)(HANDLE, LPVOID, DWORD, LPDWORD, LPOVERLAPPED);

typedef HANDLE(WINAPI* sub_45E3E0)(LPCSTR, int, int, int, int);

typedef int(*sub_45EBF2)(int, signed int*);

//Override prototypes
HANDLE WINAPI overriddenCreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);