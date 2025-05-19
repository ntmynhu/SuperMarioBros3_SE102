#include "LivesUI.h"
#include "Game.h"

void LivesUI::Render(float x, float y)
{
	CGame* game = CGame::GetInstance();
	int lives = game->GetLives();

	int tensPlace = lives / 10;
	int unitsPlace = lives % 10;

	CSprites* s = CSprites::GetInstance();

	x -= 84;
	y -= 6;

	if (tensPlace > 0) s->Get(ID_SPRITE_TIMER_0 + tensPlace)->DrawStatic(x - NUMBER_WIDTH, y);
	s->Get(ID_SPRITE_TIMER_0 + unitsPlace)->DrawStatic(x, y);
}
