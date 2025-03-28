#pragma once
#include "GameObject.h"
#include "Mario.h"

class MarioForm
{
public:
	virtual void Update(DWORD dt, CMario* mario, vector<LPGAMEOBJECT> *coObjects) = 0;
	virtual void Render(float x, float y) = 0;
	virtual void SetState(int state, CMario* mario) = 0;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	virtual void GetLevel() const = 0;
	virtual void OnTakeDamage(CMario* mario) = 0;	
};

