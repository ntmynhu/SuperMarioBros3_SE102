#include "GameData.h"

CGameData* CGameData::__instance = NULL;

CGameData* CGameData::GetInstance()
{
	if (__instance == NULL) __instance = new CGameData();
	return __instance;
}