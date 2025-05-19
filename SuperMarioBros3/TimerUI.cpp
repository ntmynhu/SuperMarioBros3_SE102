#include "TimerUI.h"
#include "Game.h"
#include "debug.h"

void TimerUI::Render(float x, float y)
{
	CGame* game = CGame::GetInstance();
	int totalTime = (int)(game->GetGameCurrentTime() / 1000);

	int hundredsPlace = totalTime / 100;
	int tensPlace = (totalTime % 100) / 10;
	int unitsPlace = (totalTime % 100) % 10;

	CSprites* s = CSprites::GetInstance();

	x += 14;
	y -= 6;

	s->Get(ID_SPRITE_NUMBER_0 + hundredsPlace)->DrawStatic(x - NUMBER_WIDTH, y);
	s->Get(ID_SPRITE_NUMBER_0 + tensPlace)->DrawStatic(x, y);
	s->Get(ID_SPRITE_NUMBER_0 + unitsPlace)->DrawStatic(x + NUMBER_WIDTH, y);
}