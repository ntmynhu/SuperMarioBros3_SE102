#pragma once
#include "GameObject.h"



#define ENEMY_DIE_UPSIDE_DOWN_VY 0.2f
#define ENEMY_DIE_UPSIDE_DOWN_VX 0.2f

#define ENEMY_STATE_DIE 1000

class CMario;
class CEnemy :
	public CGameObject
{
protected:
	float ax;
	float ay;
	bool isOnPlatform;
	ULONGLONG die_start;
	CMario* mario;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual int CheckXDirection();
	virtual void SetMario();
	virtual void ResetPos();
public:
	CEnemy(float x, float y);
	virtual void OnCollisionByMario(LPCOLLISIONEVENT e) {};
	virtual void TakeJumpDamage() {};
	virtual void TakeAttackDamage() {};
	virtual void TakeTailAttackDamage(float xMario) {};
	virtual void TakeKoopaDamage() {};
	virtual void HandleMarioRelease(float nx) {};
	virtual void TakeKoopaDamage(float xKoopa) {};
	virtual bool IsDamagable() { return true; };
};

