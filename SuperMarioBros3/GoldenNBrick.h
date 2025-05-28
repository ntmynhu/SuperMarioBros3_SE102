#pragma once
#include "QuestionBlock.h"
#include "Coin.h"
#define ID_ANI_GOLDEN_BRICK 81102

#define SPAWN_TIMEOUT 1500
class CGoldenNBrick : public CQuestionBlock
{
protected:
	ULONGLONG spawn_start = -1;
	vector<CCoin*> coins;
	int spawn_point = 0;
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void CleanList();
public:
	CGoldenNBrick(float x, float y, vector<CCoin*> coins, int active_ani_id = ID_ANI_GOLDEN_BRICK) : CQuestionBlock(x, y, -1, NULL, -1, NULL, active_ani_id)
	{
		this->coins = coins;
	}

	int IsBlocking() { return 1; }
	int IsCollidable() { return 1; }

	virtual void Render();
	virtual void TriggerAction(LPCOLLISIONEVENT e = NULL);
	virtual void SpawnItem();
};

