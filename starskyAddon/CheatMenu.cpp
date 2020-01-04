#include "CheatMenu.h"

CheatMenu * CheatMenu::instance = nullptr;

CheatMenu::CheatMenu()
{

}

void CheatMenu::Show()
{
	if (instance == nullptr)
	{
		instance = new CheatMenu();
	}
	//show..
}

void CheatMenu::Hide()
{
	if (instance == nullptr)
	{
		//instance = new CheatMenu();
	}
	//show..
}