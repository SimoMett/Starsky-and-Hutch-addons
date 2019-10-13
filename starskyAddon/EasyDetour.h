#pragma once

#include <Windows.h>
#include <string>
#include <map>
#include "detours/detours.h"

//This class needs some reworks

template <class FuncType>
class EasyDetour
{
public:
	static FuncType ApplyEasyDetour(PBYTE _targetFunc, PBYTE _detourFunc, const std::string & funcName)
	{
		FuncType _originalFunc = nullptr;
		EasyDetour * detour=new EasyDetour(_targetFunc, _detourFunc, _originalFunc);

		std::pair<std::string, EasyDetour*> _pair (funcName, detour);

		patches.insert(_pair);
		return _originalFunc;
	}
	
private:

	EasyDetour(PBYTE _targetFunc, PBYTE _detourFunc, FuncType & _originalFunc) : targetFunc(_targetFunc), detourFunc(_detourFunc)
	{
		originalFunc = (FuncType)DetourFunction(targetFunc, detourFunc);
		_originalFunc = originalFunc;
	}

	static std::map<std::string, EasyDetour*> patches;
	
	PBYTE targetFunc;
	PBYTE detourFunc;
	
	FuncType originalFunc;
};

template <class FuncType>
std::map<std::string , EasyDetour<FuncType>*> EasyDetour<FuncType>::patches;
