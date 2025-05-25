#pragma once
#include <Windows.h>
#include "Mario.h"

using namespace std;

#define	GAME_TIME	300000
#define UP_SCORE_TIME 1000

class CGameData
{
	static CGameData* __instance;
	int mario_level = MARIO_LEVEL_SMALL;
	int upScore = 100;

	float currentTime = GAME_TIME;

	ULONGLONG currentUpScoreTime = 0;
	ULONGLONG timer_to_point_start = -1;

	int outPoint = 0;
	int coinNumber = 0;
	int marioLives = 4;
	int score = 0;
	int sceneId = 0;

	int saveSceneId;
	int saveScore, saveMarioLives, saveCoin, saveLevel;
	float saveCurrentTime;

public:
	static CGameData* GetInstance();
	void GetLevel(int &level) {
		level = mario_level;
	}
	void SetLevel(int level) {
		mario_level = level;
	}

	void SetSceneId(int sceneId) { this->sceneId = sceneId; }
	int GetSceneId() { return sceneId; }

	void SetTimer(float timer) { this->currentTime = timer; }
	void ProcessTimer(DWORD dt);
	void TimerToPoint() { 
		if (timer_to_point_start == -1) {
			timer_to_point_start = GetTickCount64();
			outPoint = 50 * (int) (currentTime / 1000);
		}
	}
	float GetGameCurrentTime() { return currentTime; }

	void AddCoin(int value) { coinNumber += value; }
	int GetCoin() { return coinNumber; }

	void UpdateLives(int value, float x, float y);
	int GetLives() { return this->marioLives; }

	void AddScore(int value, float x, float y, LPGAMEOBJECT enemy = NULL);
	void AddNoEffectScore(int value) { score += value; }
	int GetScore() { return this->score; }

	void SetSavePoint();
	void LoadSavePoint();
};

typedef CGameData* LPGAMEDATA;