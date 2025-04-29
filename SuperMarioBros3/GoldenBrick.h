#pragma once
#include "QuestionBlock.h"
#include "BrokenBrick_Particle.h"

#define ID_ANI_GOLDEN_BRICK 81102

class CGoldenBrick : public CQuestionBlock
{
	BrokenBrick_Particle* particle;
public:
	CGoldenBrick(float x, float y, int itemId, CGameObject* item, BrokenBrick_Particle* particle) : CQuestionBlock(x, y, itemId, item)
	{
		this->particle = particle;
	}

	virtual void Render();
	virtual void TriggerAction();
};

