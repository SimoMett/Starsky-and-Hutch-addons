#pragma once

#include <iostream>
#include <Windows.h>

typedef void (*ActionFuncType)(int a, int type, float time);
typedef HANDLE(WINAPI* CreateFileAFuncType)(LPCSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE);
typedef BOOL(WINAPI* ReadFileFuncType)(HANDLE, LPVOID, DWORD, LPDWORD, LPOVERLAPPED);

extern ActionFuncType originalActionFunc;
extern CreateFileAFuncType originalCreateFileA;
extern ReadFileFuncType originalReadFile;

BOOL WINAPI overriddenReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped);
void overriddenActionFunc(int a, int type, float time);
HANDLE WINAPI overriddenCreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);