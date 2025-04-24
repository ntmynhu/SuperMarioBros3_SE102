#include "GoldenBrick.h"

void CGoldenBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (!isEmpty && !isBouncing)
	{
		aniId = ID_ANI_GOLDEN_BRICK;
	}
	else
	{
		aniId = ID_ANI_BLOCK_EMPTY;
	}

	animations->Get(aniId)->Render(x, y);
}

void CGoldenBrick::TriggerAction()
{
}
