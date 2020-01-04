#pragma once

class CheatMenu
{
public:
	static void Show();
	static void Hide();
private:
	CheatMenu();

	static CheatMenu* instance;
};

