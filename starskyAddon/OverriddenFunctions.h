#pragma once

#include <iostream>
#include <Windows.h>

typedef void (*ActionFuncType)(int a, int type, float time);
typedef HANDLE(WINAPI* CreateFileAFuncType)(LPCSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE);
typedef BOOL(WINAPI* ReadFileFuncType)(HANDLE, LPVOID, DWORD, LPDWORD, LPOVERLAPPED);

#define TO_BE_TESTED_SIGNATURE char* a1
typedef int (*overriddenToBeDefinedFuncType)(TO_BE_TESTED_SIGNATURE);

extern ActionFuncType originalActionFunc;
extern CreateFileAFuncType originalCreateFileA;
extern ReadFileFuncType originalReadFile;
extern overriddenToBeDefinedFuncType originalToBeDefined;

BOOL WINAPI overriddenReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped);
void overriddenActionFunc(int a, int type, float time);
HANDLE WINAPI overriddenCreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);
int overriddenToBeDefined(TO_BE_TESTED_SIGNATURE);

#undef TO_BE_TESTED_SIGNATURE