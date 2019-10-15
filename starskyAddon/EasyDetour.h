#pragma once

#include <Windows.h>
#include <string>
#include <map>
#include "detours/detours.h"

//This class needs some reworks

class EasyDetour
{
public:
	static void * ApplyEasyDetour(PBYTE _targetFunc, PBYTE _detourFunc)
	{
		void* _originalFunc = nullptr;
		EasyDetour * detour=new EasyDetour(_targetFunc, _detourFunc, _originalFunc);

		std::pair<void *, EasyDetour*> _pair (_originalFunc, detour);

		patches.insert(_pair);
		return _originalFunc;
	}
	
private:

	EasyDetour(PBYTE _targetFunc, PBYTE _detourFunc, void* & _originalFunc) : targetFunc(_targetFunc), detourFunc(_detourFunc)
	{
		originalFunc = (void*)DetourFunction(targetFunc, detourFunc);
		_originalFunc = originalFunc;
	}
	
	PBYTE targetFunc;
	PBYTE detourFunc;
	
	void* originalFunc;

	static std::map<void*, EasyDetour*> patches;
};