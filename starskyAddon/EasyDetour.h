#pragma once

#include <Windows.h>
#include <string>
#include <map>
#include "detours/detours.h"

//This class needs some reworks

class EasyDetour
{
public:
	static void* ApplyEasyDetour(PBYTE _targetFunc, PBYTE _detourFunc);

	static void * GetOriginalFuncAddr(void * par)
	{
		return patches[par]->originalFunc;
	}
	
private:

	EasyDetour(PBYTE _targetFunc, PBYTE _detourFunc, void*& _originalFunc);
	
	PBYTE targetFunc;
	PBYTE detourFunc;
	
	void* originalFunc;

	static std::map<void*, EasyDetour*> patches;
};