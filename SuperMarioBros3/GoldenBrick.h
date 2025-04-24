#pragma once
#include "QuestionBlock.h"

#define ID_ANI_GOLDEN_BRICK 81102

class CGoldenBrick : public CQuestionBlock
{
public:
	CGoldenBrick(float x, float y, int itemId, CGameObject* item) : CQuestionBlock(x, y, itemId, item) {}
	virtual void Render();
	virtual void TriggerAction();
};

