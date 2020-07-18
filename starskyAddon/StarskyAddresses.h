#pragma once

#define GAME_POINTS_DPTR 0x692894
#define GAME_ASM_POINTS_UPDATE 0x4FB314 //This address maybe is incorrect. It bugs collision with dynamic objects
#define GAME_ACTION_FUNC 0x501d6f //accepts 3 parameters (int, int, float)
#define GAME_START_SIREN_SOUND 0x50E321
#define GAME_GIVE_WEAPON 0x501c21
//#define GAME_SPAWN_VEHICLE //nope
//#define GAME_TO_BE_DEFINED_FUNC 0x59A500
#define GAME_TO_BE_DEFINED_FUNC 0x5FDE03
#define RESOURCE_FUNC 0x45E3E0//maybe

#define UNK_CONSTRUCTOR 0x402580

#define GAME_CREATE_WINDOW_FUNC 0x41694F

enum GameActionTypes
{
	Turbo,
	DoubleDamage,
	Siren,
	DoublePoints=5,
	GiveGun1,
	GiveGun2=8,
	GiveGunSawnoff,
	GiveGun3=14,
	Grip,
	NoEnemyDamage=17,
	TwoWheels,
	CRASH_DONOTUSE
};

enum HutchWeapons
{
	SuperRevolver = 1,
	HutchColtPython,
	Pistol9mm,
	Mac10 = 5,
	NpcRifle = 7,
	Sawnoff,
	Sawnoff2
};

/*Here I will write some notes too.

	- 0x65556c car pool start?
	- 0x6594cc oscillation camera angle
	- 0x753850 zebra3 siren light status (if == 3 then light (only) is on)
*/