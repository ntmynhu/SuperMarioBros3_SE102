#include "HUD.h"
#include "Game.h"
HUD* HUD::__instance = NULL;

HUD* HUD::GetInstance()
{
	if (__instance == NULL)
	{
		__instance = new HUD(0, 0);
		
		if (__instance->timer == NULL)
			__instance->timer = new TimerUI(0, 0);

		if (__instance->coin == NULL)
			__instance->coin = new CoinUI(0, 0);

		if (__instance->lives == NULL)
			__instance->lives = new LivesUI(0, 0);

		if (__instance->world == NULL)
			__instance->world = new WorldUI(0, 0);

		if (__instance->score == NULL)
			__instance->score = new ScoreUI(0, 0);

		if (__instance->power == NULL)
			__instance->power = new PowerUI(0, 0);

		if (__instance->cards == NULL)
			__instance->cards = new CardUI(0, 0);
	}
	return HUD::__instance;
}

void HUD::AddCard(int id)
{
	cards->AddCard(id);
}

void HUD::ClearCard()
{
	cards->ClearCard();
}

void HUD::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

}

void HUD::Render() {
	CSprites* s = CSprites::GetInstance();

	float targetX = x;
	float targetY = y - HUD_HEIGHT / 2 + 6;

	s->Get(ID_SPRITE_HUD_BACKGROUND)->DrawStatic(targetX, targetY);

	timer->Render(targetX, targetY);
	coin->Render(targetX, targetY);
	lives->Render(targetX, targetY);
	world->Render(targetX, targetY);
	score->Render(targetX, targetY);
	power->Render(targetX, targetY);
	cards->Render(targetX, targetY);
}