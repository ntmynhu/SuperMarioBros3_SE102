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
	currentTime -= dt;
	if (currentTime < 0) currentTime = 0;
}

void CGameData::UpdateLives(int value, float x, float y)
{
	this->marioLives += value;
	if (value == 1) ScoreEffect* scoreEffect = new ScoreEffect(value, x, y);
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