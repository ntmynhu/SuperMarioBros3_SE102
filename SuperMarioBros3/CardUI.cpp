#include "CardUI.h"
#include "Game.h"

void CardUI::Render(float x, float y)
{
	CGame* game = CGame::GetInstance();

	x += 26;
	y -= 10;
	
	for (int i = 0; i < 3; i++)
	{
		CSprites* s = CSprites::GetInstance();

		x += CARD_WIDTH;

		if (card_ids[i] != -1)
		{
			switch (card_ids[i])
			{
			case 1:
				s->Get(ID_SPRITE_CARD_STAR)->DrawStatic(x, y);
				break;
			case 2:
				s->Get(ID_SPRITE_CARD_PLANT)->DrawStatic(x, y);
				break;
			case 3:
				s->Get(ID_SPRITE_CARD_MUSHROOM)->DrawStatic(x, y);
				break;
			}
		}
	}
}
