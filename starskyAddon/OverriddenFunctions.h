#pragma once

#include <iostream>
#include <Windows.h>
#include "StarskyAddresses.h"

typedef void (*ActionFuncType)(int a, int type, float time);
typedef HANDLE (WINAPI* CreateFileAFuncType)(LPCSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE);
typedef BOOL (WINAPI* ReadFileFuncType)(HANDLE, LPVOID, DWORD, LPDWORD, LPOVERLAPPED);
typedef HANDLE (__stdcall* ResourceFuncType)(const char* lpFileName, int a, int addr1, int addr2, int addr3);
typedef int (__fastcall* ToggleSirenSndFuncType)(int _this);
typedef int (__fastcall* sub_50E0D1)(void * _this);
typedef int (__fastcall* sub_50E4DA)(int _this, float a);
typedef signed int(__fastcall* sub_45CF74)(DWORD * _this,int a2, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite);
typedef int(__fastcall* sub_45AA9B)(DWORD* _this);
typedef int(__fastcall* sub_45A3BC)(DWORD* _this, int edx0, char* a2, int a3, int a4);
typedef void(__cdecl* GiveWeaponFuncType)(int weapon, short ammo);

typedef void(__thiscall* UnkCtor)(int param);

typedef int(__fastcall* sub_43DDE8)(DWORD*, int, char*, int, int);

#define TO_BE_TESTED_SIGNATURE int a1
#define TO_BE_TESTED_RETURN_TYPE char *
typedef TO_BE_TESTED_RETURN_TYPE (*overriddenToBeDefinedFuncType)(TO_BE_TESTED_SIGNATURE);

extern ActionFuncType originalActionFunc;
extern CreateFileAFuncType originalCreateFileA;
extern ReadFileFuncType originalReadFile;
extern overriddenToBeDefinedFuncType originalToBeDefined;
extern ResourceFuncType originalResource;
extern ToggleSirenSndFuncType originalToggleSirenSnd;
extern sub_50E0D1 sub50E0D1;
extern sub_50E4DA sub50E4DA;
extern sub_45CF74 sub45CF74;
extern sub_45AA9B sub45AA9B;
extern sub_45A3BC sub45A3BC;
extern GiveWeaponFuncType originalGiveWeapon;
extern UnkCtor originalUnkCtor;
extern sub_43DDE8 sub43DDE8;


BOOL WINAPI overriddenReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped);
void overriddenActionFunc(int a, int type, float time);
HANDLE WINAPI overriddenCreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);
TO_BE_TESTED_RETURN_TYPE overriddenToBeDefined(TO_BE_TESTED_SIGNATURE);
HANDLE __stdcall overriddenResource(const char* lpFileName, int a, int addr1, int addr2, int addr3);
int __fastcall hookedToggleSirenSnd(int _this);
int __fastcall hookedSub_50E0D1(void* _this);
int __fastcall hookedSub_50E4DA(int _this, float a);
signed int __fastcall hookedSub_45CF74(DWORD* _this, int a2, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite);
int __fastcall hookedSub_45AA9B(DWORD* _this);
int __fastcall hookedSub_45A3BC(DWORD* _this, int edx0, char* a2, int a3, int a4);
void __cdecl overriddenGiveWeapon(int weapon, short ammo);
int __fastcall hookedSub_43DDE8(DWORD * _this, int edx0,char* btwFileName, int a3, int a4);

#undef TO_BE_TESTED_SIGNATURE