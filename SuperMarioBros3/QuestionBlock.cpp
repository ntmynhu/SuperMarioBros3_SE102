#include "QuestionBlock.h"

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
