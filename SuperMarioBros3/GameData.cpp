#include "GameData.h"
#include "EffectManager.h"
CGameData* CGameData::__instance = NULL;

CGameData* CGameData::GetInstance()
{
	if (__instance == NULL) __instance = new CGameData();
	return __instance;
}

void CGameData::ProcessTimer(DWORD dt)
{
	if (timer_to_point_start == -1) 
	{
		currentTime -= dt;
		if (currentTime < 0) currentTime = 0;
	}
	else if (GetTickCount64() - timer_to_point_start > 2000)
	{
		currentTime -= 3000;
		if (currentTime <= 0) {
			timer_to_point_start = -1;
			currentTime = 0;
			score += outPoint;
			outPoint = 0;
		}
	}
}

void CGameData::UpdateLives(int value, float x, float y)
{
	this->marioLives += value;
	if (value == 1) ScoreEffect* scoreEffect = new ScoreEffect(value, x, y);
}

int CGameData::DecreaseLives()
{
	this->marioLives--;
	saveMarioLives = marioLives;
	int res = marioLives;
	return res;
}

void CGameData::AddScore(int value, float x, float y, LPGAMEOBJECT enemy) // Xử lí tăng điểm khi enemy die liên tiếp
{
	if (enemy != NULL) {
		if (GetTickCount64() - currentUpScoreTime < UP_SCORE_TIME)
		{
			value = upScore * 2;

			upScore *= 2;
			if (upScore == 1600) upScore = 1000;
		}
		else
		{
			upScore = 100;
			currentUpScoreTime = GetTickCount64();
		}
	}

	this->score += value;
	ScoreEffect* scoreEffect = new ScoreEffect(value, x, y);
}

void CGameData::SetSavePoint() {
	saveSceneId = sceneId;
	saveScore = score;
	saveMarioLives = marioLives;
	saveCoin = coinNumber;
	saveLevel = mario_level;
	saveCurrentTime = currentTime;
}

void CGameData::LoadSavePoint() {
	sceneId = saveSceneId;
	score = saveScore;
	marioLives = saveMarioLives;
	coinNumber = saveCoin;
	mario_level = saveLevel;
	currentTime = saveCurrentTime;
}

void CGameData::ResetData() {
	sceneId = -1;
	score = 0;
	marioLives = INIT_LIFE;
	coinNumber = 0;
	mario_level = 1;
	currentTime = 0;
	SetSavePoint();
}