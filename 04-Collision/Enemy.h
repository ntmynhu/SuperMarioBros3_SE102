#pragma once
#include "GameObject.h"
class CEnemy :
    public CGameObject
{
protected:
	float ax;
	float ay;
	bool isOnPlatform;
	ULONGLONG die_start;

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
public:
	CEnemy(float x, float y);
};

