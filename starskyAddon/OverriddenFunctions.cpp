#include "OverriddenFunctions.h"

using std::cout;
using std::string;
using std::endl;

ActionFuncType originalActionFunc;
CreateFileAFuncType originalCreateFileA;
ReadFileFuncType originalReadFile;
overriddenToBeDefinedFuncType originalToBeDefined;

BOOL WINAPI overriddenReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped)//TODO cannot read file name
{
	char stringa[40];
	memset(stringa, 0, 40);

	GetFileInformationByHandleEx(hFile, FileNameInfo, (LPVOID)stringa, 40);

	cout << "Read " << (int)nNumberOfBytesToRead << " bytes from: " << string(stringa) << endl;

	return originalReadFile(hFile, lpBuffer, nNumberOfBytesToRead, lpNumberOfBytesRead, lpOverlapped);
}

/*
	Actyally this function is not for turbo only. It is multi-purpose.
	It can activate several actions, like turbo, siren..
*/
void overriddenActionFunc(int a, int type, float time)
{
	printf("Action(%d %d %f)\n", a, type, time);
	originalActionFunc(a, type, time);
}

HANDLE WINAPI overriddenCreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile)
{
	cout << "Opening file: " << lpFileName << endl;
	return originalCreateFileA(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}

int overriddenToBeDefined(char* a1)
{
	cout << "ToBeDefined Function:" << endl;
	cout << "\t" << string(a1) <<endl;
	return originalToBeDefined(a1);
}