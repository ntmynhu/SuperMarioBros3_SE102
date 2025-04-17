#pragma once
#include "Block.h"

#define ID_ANI_QUESTION_BLOCK 81101

#define ID_ITEM_COIN 0
#define ID_ITEM_SUPER_MUSHROOM 1

#define BLOCK_BOUNCING_SPEED 0.35f
#define BLOCK_BOUNCING_HEIGHT 20

class CQuestionBlock : public CBlock
{
	bool isEmpty;
	int itemId;
	CGameObject* item = NULL;
	bool isBouncing = false;
	float originalY;
public:
	CQuestionBlock(float x, float y, int itemId, CGameObject* item) : CBlock(x, y)
	{
		item->Deactivate();
		this->item = item;
		isEmpty = false;	
		this->itemId = itemId;
		originalY = y;
	}

	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	bool IsEmpty() { return isEmpty; }
	void SpawnItem();
};

