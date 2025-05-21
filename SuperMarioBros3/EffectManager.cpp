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
	CSprites* s = CSprites::GetInstance();

	float camX, camY;
	CGame::GetInstance()->GetCamPos(camX, camY);

	float targetX = x - camX;
	float targetY = y - camY;

	DebugOut(L"x: %f, y: %f\n", x, y);

	s->Get(ID_SPRITE_SCORE_EFFECT_100)->DrawStatic(targetX, targetY);
}
