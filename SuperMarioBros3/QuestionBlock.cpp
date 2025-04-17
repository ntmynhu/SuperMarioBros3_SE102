#include "QuestionBlock.h"
#include "Coin.h"
#include "SuperMushroom.h"
#include "debug.h"

void CQuestionBlock::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (!isEmpty)
	{
		aniId = ID_ANI_QUESTION_BLOCK;
	}
	else
	{
		aniId = ID_ANI_BLOCK_EMPTY;
	}

	animations->Get(aniId)->Render(x, y);
}

void CQuestionBlock::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isBouncing)
	{
		y += vy * BLOCK_BOUNCING_SPEED * dt;

		if (y <= originalY - BLOCK_BOUNCING_HEIGHT)
		{
			vy = 1;
		}

		if (vy == 1 && y >= originalY)
		{
			vy = 0;
			isBouncing = false;
			y = originalY;
		}
	}
}

void CQuestionBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	CBlock::GetBoundingBox(l, t, r, b);
}

void CQuestionBlock::SpawnItem()
{
	if (item == NULL) return;

	switch (itemId)
	{
		case ID_ITEM_COIN:
		{
			CCoin* coin = dynamic_cast<CCoin*>(item);
			if (coin)
			{
				coin->StartBouncing();
				isEmpty = true;
				isBouncing = true;
				vy = -1;
			}
			break;
		}

		case ID_ITEM_SUPER_MUSHROOM:
		{
			CSuperMushroom* mushroom = dynamic_cast<CSuperMushroom*>(item);
			if (mushroom)
			{
				mushroom->AppearFromQuestionBlock(x, y);
				isEmpty = true;
				isBouncing = true;
				vy = -1;
			}
			break;
		}	
	}
}
