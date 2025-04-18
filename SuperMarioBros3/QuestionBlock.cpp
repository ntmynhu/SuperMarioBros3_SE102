#include "QuestionBlock.h"
#include "Coin.h"
#include "SuperMushroom.h"
#include "SuperLeaf.h"
#include "debug.h"

void CQuestionBlock::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (!isEmpty && !isBouncing)
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
	if (!isEmpty && item) item->Deactivate();

	if (isBouncing)
	{
		// If the item is coin, spawn it immediately
		if (itemId == ID_ITEM_COIN && !isEmpty)
		{
			SpawnItem();
		}

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

			SpawnItem();
		}
	}
}

void CQuestionBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	CBlock::GetBoundingBox(l, t, r, b);
}

void CQuestionBlock::SpawnItem()
{
	if (!item || item->IsDeleted()) {
		item = NULL;
		return;
	}

	switch (itemId)
	{
		case ID_ITEM_COIN:
		{
			CCoin* coin = dynamic_cast<CCoin*>(item);
			if (coin)
			{
				coin->StartBouncing(y);
			}
			break;
		}

		case ID_ITEM_SUPER_MUSHROOM:
		{
			CSuperMushroom* mushroom = dynamic_cast<CSuperMushroom*>(item);
			if (mushroom)
			{
				float marioX, marioY;
				mario->GetPosition(marioX, marioY);
				mushroom->AppearFromQuestionBlock(marioX, y);
			}
			break;
		}	

		case ID_ITEM_SUPER_LEAF:
		{
			CSuperLeaf* leaf = dynamic_cast<CSuperLeaf*>(item);
			if (leaf)
			{
				leaf->AppearFromQuestionBlock(x, y);
			}
			break;
		}
	}

	isEmpty = true;
}
