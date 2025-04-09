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
	virtual void OnCollisionByMario(LPCOLLISIONEVENT e) {};
	virtual void TakeJumpDamage() {};
	virtual void TakeAttackDamage() {};
	virtual void TakeTailAttackDamage() {};
	virtual void TakeKoopaDamage() {};
	virtual bool IsDamagable() { return true; };
};

