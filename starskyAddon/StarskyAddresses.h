#pragma once

#define GAME_POINTS_DPTR 0x692894
#define GAME_ASM_POINTS_UPDATE 0x4FB314 //This address maybe is incorrect. It bugs collision with dynamic objects
#define GAME_ACTION_FUNC 0x501d6f //accepts 3 parameters (int, int, float)
#define GAME_START_SIREN_SOUND 0x50E321 //maybe

enum GameActionTypes
{
	Turbo,
	DoubleDamage,
	Siren,
	DoublePoints=5,
	GivePistol,
	GiveRevolver=8,
	GiveGunSawnoff,
	GiveGun3=14,
	Grip,
	NoEnemyDamage=17,
	TwoWheels,
	CRASH_DONOTUSE
};

/*Here I will write some notes too.

*/