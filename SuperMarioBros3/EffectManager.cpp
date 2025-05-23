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
		if (effect != nullptr)
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
	if (GetTickCount64() - startTime > SCORE_EFFECT_TIME || id_sprite == -1)
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

	s->Get(id_sprite)->DrawStatic(targetX, targetY);
}

void TailEffect::Render()
{
	if (GetTickCount64() - startTime > VISUAL_EFFECT_TIME)
	{
		Delete();
		return;
	}

	float offset = VISUAL_EFFECT_TIME / 5;

	int index = (GetTickCount64() - startTime) / offset;
	
	int id_sprite = -1;

	DebugOut(L"index: %d\n", index);
	switch (index)
	{
	case 0:
		id_sprite = ID_SPRITE_TAIL_EFFECT_PINK_LEFT;
		break;
	case 1:
		id_sprite = ID_SPRITE_TAIL_EFFECT_WHITE_RIGHT;
		break;
	case 2:
		id_sprite = ID_SPRITE_TAIL_EFFECT_PINK_RIGHT;
		break;
	case 3:
		id_sprite = ID_SPRITE_TAIL_EFFECT_WHITE_LEFT;
		break;
	case 4:
		id_sprite = ID_SPRITE_TAIL_EFFECT_PINK_LEFT;
		break;
	default:
		id_sprite = ID_SPRITE_TAIL_EFFECT_PINK_LEFT;
		break;
	}

	CSprites* s = CSprites::GetInstance();

	float camX, camY;
	CGame::GetInstance()->GetCamPos(camX, camY);

	float targetX = x - camX;
	float targetY = y - camY;

	DebugOut(L"targetX: %f, targetY: %f\n", targetX, targetY);

	s->Get(id_sprite)->DrawStatic(targetX, targetY);
}
