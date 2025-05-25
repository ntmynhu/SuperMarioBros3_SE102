#include "ScoreUI.h"
#include "Game.h"
#include "GameData.h"

void ScoreUI::Render(float x, float y)
{
	CGameData* game = CGameData::GetInstance();
	int score = game->GetScore();

	int millionsPlace = score / 1000000;
	int hundredThousandsPlace = (score % 1000000) / 100000;
	int tenThousandsPlace = (score % 100000) / 10000;
	int thousandsPlace = (score % 10000) / 1000;
	int hundredsPlace = (score % 1000) / 100;
	int tensPlace = (score % 100) / 10;
	int unitsPlace = score % 10;

	CSprites* s = CSprites::GetInstance();

	x -= 18;
	y -= 6;

	s->Get(ID_SPRITE_NUMBER_0 + millionsPlace)->DrawStatic(x - NUMBER_WIDTH * 6, y);
	s->Get(ID_SPRITE_NUMBER_0 + hundredThousandsPlace)->DrawStatic(x - NUMBER_WIDTH * 5, y);
	s->Get(ID_SPRITE_NUMBER_0 + tenThousandsPlace)->DrawStatic(x - NUMBER_WIDTH * 4, y);
	s->Get(ID_SPRITE_NUMBER_0 + thousandsPlace)->DrawStatic(x - NUMBER_WIDTH * 3, y);
	s->Get(ID_SPRITE_NUMBER_0 + hundredsPlace)->DrawStatic(x - NUMBER_WIDTH * 2, y);
	s->Get(ID_SPRITE_NUMBER_0 + tensPlace)->DrawStatic(x - NUMBER_WIDTH, y);
	s->Get(ID_SPRITE_NUMBER_0 + unitsPlace)->DrawStatic(x, y);
}
