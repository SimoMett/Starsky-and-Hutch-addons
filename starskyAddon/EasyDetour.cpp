#include "EasyDetour.h"

std::map<void*, EasyDetour*> EasyDetour::patches;

void* EasyDetour::ApplyEasyDetour(PBYTE _targetFunc, PBYTE _detourFunc)
{
	void* _originalFunc = nullptr;
	EasyDetour* detour = new EasyDetour(_targetFunc, _detourFunc, _originalFunc);

	std::pair<void*, EasyDetour*> _pair(_originalFunc, detour);
	patches.insert(_pair);

	return _originalFunc;
}

EasyDetour::EasyDetour(PBYTE _targetFunc, PBYTE _detourFunc, void*&_originalFunc) : targetFunc(_targetFunc), detourFunc(_detourFunc)
{
	originalFunc = (void*)DetourFunction(targetFunc, detourFunc);
	_originalFunc = originalFunc;
}