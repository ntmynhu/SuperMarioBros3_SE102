#pragma once
#include "QuestionBlock.h"
#include "BrokenBrick_Particle.h"

#define ID_ANI_GOLDEN_BRICK 81102

#define BRICK_STAT_NORMAL 0
#define BRICK_STAT_NO_COLLIDE_Y 1

class CGoldenBrick : public CQuestionBlock
{
protected:
	BrokenBrick_Particle* particle;
	int brick_stat = 0;
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

public:
	CGoldenBrick(float x, float y, int itemId, 
		CGameObject* item, BrokenBrick_Particle* particle, int brick_stat = 0) : CQuestionBlock(x, y, itemId, item)
	{
		this->particle = particle;
		this->brick_stat = brick_stat;
	}

	void ResetPos() {
		if (item == NULL || item->IsDeleted() && !isEmpty)
		{
			if (particle != NULL)
				this->particle->Delete();
			this->Delete();
			return;
		}
		CGameObject::ResetPos();
	}
	virtual void Render();
	virtual void TriggerAction(LPCOLLISIONEVENT e = NULL);
	virtual void TurnToCoin();
	virtual void SpawnItem();
};

