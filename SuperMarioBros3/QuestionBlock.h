#pragma once
#include "Block.h"

#define ID_ANI_QUESTION_BLOCK 81101

#define ID_ITEM_COIN 0

class CQuestionBlock : public CBlock
{
	bool isEmpty;
	CGameObject* item = NULL;
public:
	CQuestionBlock(float x, float y, CGameObject* item) : CBlock(x, y)
	{
		isEmpty = false;	
	}

	virtual void Render();
	virtual void Update(DWORD dt) {}
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

