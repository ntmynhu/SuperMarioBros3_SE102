#include "EffectManager.h"
#include "debug.h"
#include "Game.h"

EffectManager* EffectManager::__instance = NULL;

void EffectManager::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
}

void EffectManager::Render()
{
	for (CUIElement* effect : effects)
	{
		effect->Render();
	}
}

EffectManager* EffectManager::GetInstance()
{
	if (__instance == NULL)
	{
		__instance = new EffectManager(0, 0);
	}

	return EffectManager::__instance;
}

void ScoreEffect::Render()
{
	if (GetTickCount64() - startTime > SCORE_EFFECT_TIME)
	{
		Delete();
		return;
	}

	CSprites* s = CSprites::GetInstance();


	float camX, camY;
	CGame::GetInstance()->GetCamPos(camX, camY);

	float targetX = x - camX;
	float targetY = y - camY - increasement;

	if (GetTickCount64() - startTime < SCORE_EFFECT_TIME / 2)
		increasement += 0.75f;
	else
		increasement += 0.35f;

	DebugOut(L"x: %f\n", GetTickCount64() - currentTime);

	s->Get(id_sprite)->DrawStatic(targetX, targetY);
}
