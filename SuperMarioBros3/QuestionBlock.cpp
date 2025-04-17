#include "QuestionBlock.h"
#include "Coin.h"
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

void CQuestionBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	CBlock::GetBoundingBox(l, t, r, b);
}

void CQuestionBlock::SpawnItem()
{
	if (item == NULL) return;

	DebugOut(L"[INFO] Spawn item in question block %d\n", itemId);
	switch (itemId)
	{
	case ID_ITEM_COIN:
		DebugOut(L"[INFO] Spawn coin\n");
		CCoin* coin = dynamic_cast<CCoin*>(item);
		if (coin)
		{
			DebugOut(L"[INFO] Start Bouncing");
			coin->StartBouncing();
			isEmpty = true;
		}
		break;
	}
}
