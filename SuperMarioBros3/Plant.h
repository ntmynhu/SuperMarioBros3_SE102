#pragma once
#include "GameObject.h"

#define PLANT_UP_TIME_OUT 2000
#define PLANT_DOWN_TIME_OUT 2000
#define PLANT_DIE_TIME_OUT 2000

#define PLANT_VY 0.02f

#define PLANT_STATE_DIE 1000
#define PLANT_STATE_UP 100
#define PLANT_STATE_MOVING 200
#define PLANT_STATE_DOWN 300

class CPlant :
    public CGameObject
{
protected:
    ULONGLONG up_start;
    ULONGLONG down_start;
	ULONGLONG die_start;

	float maxY;
	float minY;

	bool isAbleToUp;

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render() {};
	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }

public:
	CPlant(float x, float y) : CGameObject(x, y) {
		maxY = 0;
		minY = 0;
		up_start = -1;
		down_start = -1;
		die_start = -1;
		isAbleToUp = false;
		SetState(PLANT_STATE_DOWN);
	};
	virtual void SetState(int state);
	virtual void SetIsAbleToUp(bool isAbleToUp) {
		this->isAbleToUp = isAbleToUp;
	}
	virtual void TakeAttackDamage() {};
};

