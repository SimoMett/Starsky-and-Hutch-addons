#include <csignal>
#include "OverriddenFunctions.h"
#include "main.h"


using std::cout;
using std::string;
using std::endl;

ActionFuncType originalActionFunc = (ActionFuncType)GAME_ACTION_FUNC;
CreateFileAFuncType originalCreateFileA = CreateFileA;
ReadFileFuncType originalReadFile = ReadFile;
overriddenToBeDefinedFuncType originalToBeDefined = (overriddenToBeDefinedFuncType)GAME_TO_BE_DEFINED_FUNC;
ResourceFuncType originalResource = (ResourceFuncType)RESOURCE_FUNC;
ToggleSirenSndFuncType originalToggleSirenSnd = (ToggleSirenSndFuncType)GAME_START_SIREN_SOUND;
sub_50E0D1 sub50E0D1 = (sub_50E0D1)0x50E0D1;
sub_50E4DA sub50E4DA = (sub_50E4DA)0x50E4DA;
sub_45CF74 sub45CF74 = (sub_45CF74)0x45CF74;
sub_45AA9B sub45AA9B = (sub_45AA9B)0x45AA9B;
sub_45A3BC sub45A3BC = (sub_45A3BC)0x45A3BC;
GiveWeaponFuncType originalGiveWeapon = (GiveWeaponFuncType)GAME_GIVE_WEAPON;
CreateGameWindowFuncType originalCreateGameWindow = (CreateGameWindowFuncType)GAME_CREATE_WINDOW_FUNC;
Direct3DCreate8FuncType originalDirect3DCreate8 = (Direct3DCreate8FuncType)DIRECT3DCREATE8_FUNC;

UnkCtor originalUnkCtor = (UnkCtor)UNK_CONSTRUCTOR;


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

void __cdecl overriddenGiveWeapon(int weapon, short ammoRounds)
{
	cout << "GiveWeapon(" << weapon << "," << ammoRounds << ")" << endl;
	originalGiveWeapon(weapon, ammoRounds);
}

HANDLE WINAPI overriddenCreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile)
{
	cout << "Opening file: " << lpFileName << endl;
	/*if (std::string(lpFileName) == "cdData\\Common.btw")
	{
		//system("pause");
	}*/
	return originalCreateFileA(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}

TO_BE_TESTED_RETURN_TYPE overriddenToBeDefined(int a1)
{
	cout << "ToBeDefined Function:" << endl;

	char* result = originalToBeDefined(a1);

	cout << "\t" << string(result) << endl;

	return result;
}

HANDLE __stdcall overriddenResource(const char* lpFileName, int a, int addr3, int addr4, int addr5)
{
	if(addr3 && addr4)
		cout <<"resource: "<< std::hex<<*(int*)(addr3)<< " "<<std::hex<<*(int*)(addr4) << endl;

	return originalResource(lpFileName, a, addr3, addr4, addr5);
}

/*
	This function is pretty simple.
	from assembly:
	
	*(_DWORD *)(this + 8) = 3; // Set zebra3 light on (light only)
	return sub_50E340(this, 1); //(accordingly) trigger siren sound

*/
int __fastcall hookedToggleSirenSnd(int _this)
{
	//cout << "hookedToggleSirenSnd: ptr = " << std::hex << _this << endl;

	//return 0;
	return originalToggleSirenSnd(_this);
}

//called once at start. Maybe to set everything to 0 at beginning
int __fastcall hookedSub_50E0D1(void* _this)
{
	//cout << "this: " << std::hex << _this << endl;
	return sub50E0D1(_this);
}

/*
	sirenDelta: siren speed (movement between frames)

	called every frame (in game)
*/
int __fastcall hookedSub_50E4DA(int _this, float sirenDelta)
{
	//sirenDelta *= 0.5;
	//cout << "this: " << std::hex << _this << " sirenDelta: " << sirenDelta << endl;
	return sub50E4DA(_this, sirenDelta);
}

//unknown atm
signed int __fastcall hookedSub_45CF74(DWORD* _this, int a2, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite)
{
	std::string buffer((char*)lpBuffer);
	cout << "lpBuffer: " << buffer << endl;
	return sub45CF74(_this, a2, lpBuffer, nNumberOfBytesToWrite);
}

//unknown atm
int __fastcall hookedSub_45AA9B(DWORD* _this)
{
	cout << "sub_45AA9B: " << std::hex << _this << endl;
	return sub45AA9B(_this);
}

/*
	This function is related to resource loading
*/
int __fastcall hookedSub_45A3BC(DWORD* _this, int edx0, char* a2, int a3, int a4)
{
	string str(a2);
	cout << "hookedSub_45A3BC(" <<std::hex<< _this<<", "<<edx0 << ", " << str << ", " << a3 << ", " << a4 << ")" << endl;
	return sub45A3BC(_this, edx0, a2, a3, a4);
}

static bool init = false;

HWND __cdecl overriddenCreateGameWindow(HINSTANCE hInstance)
{
	gameWindowHwnd=originalCreateGameWindow(hInstance);
	printf("CreateGameWindow(%d) => %d\n", hInstance, gameWindowHwnd);

	return gameWindowHwnd;
}

/*
	'device' (below) is also stored at:	0x0076357C
										0x7AF235D8
*/
int __stdcall overriddenDirect3DCreate8(int SDKVersion)
{
	int device=originalDirect3DCreate8(SDKVersion);
	printf("Direct3DCreate8(%d) => %d\n",SDKVersion, device);

	if (!init)
	{
		ImGui::CreateContext();
		static ImGuiIO& io = ImGui::GetIO();
		ImGui::StyleColorsDark();

		ImGui_ImplWin32_Init(gameWindowHwnd);
		ImGui_ImplDX8_Init((IDirect3DDevice8*)device);
		init = true;
	}

	return device;
}
