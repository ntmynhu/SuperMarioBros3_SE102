#include "EffectManager.h"
#include "debug.h"
#include "Game.h"
#include "HUD.h"
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

	s->Get(id_sprite)->DrawStatic(targetX, targetY);
}

void TextEffect::Render()
{
	CSprites* s = CSprites::GetInstance();

	float camX, camY;
	CGame::GetInstance()->GetCamPos(camX, camY);

	float targetX = x - camX;
	float targetY = y - camY;

	for (int i = 0; i < text.length(); i++)
	{
		int index = text[i] - 'a'; // Convert char to int

		if (index >= 0) s->Get(ID_SPRITE_LETTER_A + index)->DrawStatic(targetX + i * LETTER_WIDTH, targetY);
		else
		{
			if (index == -64)
			{
				s->Get(ID_SPRITE_EXCLAMATION)->DrawStatic(targetX + i * LETTER_WIDTH, targetY);
			}
		}
	}
}

void FadeEffect::Render()
{
	if (fadeState == 0)
	{

		if (GetTickCount64() - startTime > FADE_EFFECT_TIME) {
			Delete();
			return;

		}
	}

	CSprites* s = CSprites::GetInstance();
	float dt = GetTickCount64() - startTime;
	switch (fadeState) {
	case FADE_IN_STATE:
		a += fadeSpeed * dt;
		if (a >= 1.0f) {
			a = 1.0f;
			fadeState = 0;
		}
		break;

	case FADE_OUT_STATE:
		a -= fadeSpeed * dt;
		if (a <= 0.0f) {
			a = 0.0f;
			//fadeState = 0;
		}
		break;
	}
	if (fadeState != 0)
		startTime = GetTickCount64();
	s->Get(ID_SPRITE_BLACK_FILL)->DrawStaticFill(0, 30, a);

}

void Image::Render()
{
	CSprites* s = CSprites::GetInstance();

	if (id_sprite == -1) return;

	float camX, camY;
	CGame::GetInstance()->GetCamPos(camX, camY);

	float targetX = x - camX;
	float targetY = y - camY;

	s->Get(id_sprite)->DrawStatic(targetX, targetY);
}
