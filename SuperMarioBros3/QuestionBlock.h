#pragma once
#include "Block.h"
#include "Mario.h"

#define ID_ANI_QUESTION_BLOCK 81101

#define ID_ITEM_COIN 0
#define ID_ITEM_SUPER_MUSHROOM 1
#define ID_ITEM_SUPER_LEAF 2
#define ID_ITEM_SUPER_MUSHROOM_AND_LEAF 3
#define ID_ITEM_BLUE_BUTTON 4
#define ID_ITEM_ONE_UP_MUSHROOM 5

#define BLOCK_BOUNCING_SPEED 0.2f
#define BLOCK_BOUNCING_HEIGHT 20

class CQuestionBlock : public CBlock
{
protected:
	bool isEmpty;
	int itemId;
	int itemId2 = -1; // For the case of store multiple items
	CGameObject* item = NULL;
	CGameObject* item2 = NULL;
	bool isBouncing = false;



	int bouncing_start = -1;
public:
	CQuestionBlock(float x, float y, int itemId, CGameObject* item, 
		int itemId2 = -1, CGameObject* item2 = NULL, 
		int active_ani_id = ID_ANI_QUESTION_BLOCK) : CBlock(x, y, active_ani_id)
	{
		this->item = item;
		isEmpty = false;	
		this->itemId = itemId;
		this->itemId2 = itemId2;
		this->item2 = item2;
	}

	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	bool IsBouncing() { return isBouncing; }
	bool IsEmpty() { return isEmpty; }
	void StartBouncing() { isBouncing = true; vy = -1; bouncing_start = 0; }
	virtual void SpawnItem();

	virtual void TriggerAction(LPCOLLISIONEVENT e = NULL) { if (!isEmpty && !isBouncing) StartBouncing(); }
};

