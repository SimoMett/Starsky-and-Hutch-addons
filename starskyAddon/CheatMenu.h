#pragma once
#include <iostream>

class CheatMenu
{
public:
	static void Show();
	static void Hide();
	static bool IsShown();

private:
	CheatMenu();

	bool isShown;

	static CheatMenu* instance;
};

