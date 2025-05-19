#include "CoinUI.h"
#include "Game.h"

void CoinUI::Render(float x, float y)
{
	CGame* game = CGame::GetInstance();
	int coinNumber = game->GetCoin();

	int tensPlace = coinNumber / 10;
	int unitsPlace = coinNumber % 10;

	CGame* g = CGame::GetInstance();
	CSprites* s = CSprites::GetInstance();

	x += 20;
	y -= 14;

	if (tensPlace > 0) s->Get(ID_SPRITE_TIMER_0 + tensPlace)->DrawStatic(x - NUMBER_WIDTH, y);
	s->Get(ID_SPRITE_TIMER_0 + unitsPlace)->DrawStatic(x, y);
}
