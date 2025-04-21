#pragma once
#include <Windows.h>
#include "Mario.h"

using namespace std;
class CGameData
{
	static CGameData* __instance;
	int mario_level = MARIO_LEVEL_SMALL;

public:
	static CGameData* GetInstance();
	void GetLevel(int &level) {
		level = mario_level;
	}
	void SetLevel(int level) {
		mario_level = level;
	}
};

typedef CGameData* LPGAMEDATA;