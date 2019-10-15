#pragma once

#include <Windows.h>

//Types definitions

typedef void (*ActionFuncType)(int a, int type, float time);

typedef HANDLE(WINAPI* CreateFileAFuncType)(LPCSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE);

typedef BOOL(WINAPI* ReadFileFuncType)(HANDLE, LPVOID, DWORD, LPDWORD, LPOVERLAPPED);

typedef HANDLE(WINAPI* sub_45E3E0)(LPCSTR, int, int, int, int);

typedef int(*sub_45EBF2)(int, signed int*);