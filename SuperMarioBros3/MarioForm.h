#pragma once
#include "GameObject.h"

class CMario;

#define MARIO_DOWN_CHANGE_TIME 2000

class CMarioForm
{
public:
	virtual void Update(DWORD dt, CMario* mario, vector<LPGAMEOBJECT>* coObjects) = 0;
	virtual int GetAniId(CMario* mario) = 0;
	virtual void SetState(int state, CMario* mario) = 0;
	virtual int GetDownStateChangeTime() {
		return MARIO_DOWN_CHANGE_TIME;
	}
	virtual int GetUpStateChangeTime() = 0;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom, CMario* mario) = 0;
	virtual int GetLevel() const = 0;
	virtual void GetHoldOffset(float& ox, float& oy) = 0;
	virtual void OnTakeDamage(CMario* mario) = 0;
};

