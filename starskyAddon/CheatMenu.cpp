#include "CheatMenu.h"

using std::cout;
using std::endl;

CheatMenu * CheatMenu::instance = nullptr;

CheatMenu::CheatMenu(): isShown(false)
{

}

void CheatMenu::Show()
{
	if (instance == nullptr)
	{
		instance = new CheatMenu();
	}
	//show..
	cout << "show" << endl;
	instance->isShown = true;
}

void CheatMenu::Hide()
{
	if (instance == nullptr)
	{
		//TODO
	}
	cout << "hide" << endl;
	instance->isShown = false;
}

bool CheatMenu::IsShown()
{
	if (instance == nullptr)
		instance = new CheatMenu();

	return instance->isShown;
}