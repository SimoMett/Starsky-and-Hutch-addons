#pragma once

#include <Windows.h>
#include <string>
#include <map>
#include "detours/detours.h"

template <class FuncType>
class EasyDetour
{
public:
	static EasyDetour * ApplyEasyDetour(PBYTE _targetFunc, PBYTE _detourFunc, const std::string & funcName)
	{
		EasyDetour * detour=new EasyDetour(_targetFunc, _detourFunc);

		std::pair<std::string, EasyDetour*> _pair (funcName, detour);

		patches.insert(_pair);
		return detour;
	}

	static const PBYTE GetOriginalFuncAddr(std::string key)
	{
		return patches[key]->originalFunc;
	}
	
private:

	EasyDetour(PBYTE _targetFunc, PBYTE _detourFunc) : targetFunc(_targetFunc), detourFunc(_detourFunc)
	{
		originalFunc = (FuncType)DetourFunction(targetFunc, detourFunc);
	}

	static std::map<std::string, EasyDetour*> patches;
	
	PBYTE targetFunc;
	PBYTE detourFunc;
	
	FuncType originalFunc;
};

template <class FuncType>
std::map<std::string , EasyDetour<FuncType>*> EasyDetour<FuncType>::patches;
