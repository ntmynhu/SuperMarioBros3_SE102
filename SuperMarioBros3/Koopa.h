#pragma once
#include "Enemy.h"

#define KOOPA_GRAVITY 0.001f
#define KOOPA_WALKING_SPEED 0.04f
#define KOOPA_SLIDING_SPEED 0.18f
#define KOOPA_SHAKE_SPEED 0.08f
#define KOOPA_TAIL_HIT_VY 0.3f
#define KOOPA_TAIL_HIT_VX 0.1f

#define KOOPA_BLOCK_HIT_VY 0.2f
#define KOOPA_BLOCK_HIT_VX 0.05f

#define KOOPA_BBOX_WIDTH 16.0f
#define KOOPA_BBOX_WIDTH_DEFEND 16.0f
#define KOOPA_BBOX_HEIGHT 24.0f
#define KOOPA_BBOX_HEIGHT_DEFEND 14.0f

#define KOOPA_DIE_TIMEOUT 2000
#define KOOPA_DEFEND_TIMEOUT 8000
#define KOOPA_RECOVER_TIMEOUT 2000

#define KOOPA_STATE_WALKING 100
#define KOOPA_STATE_DEFEND 200
#define KOOPA_STATE_DEFEND_SLIDING 300
#define KOOPA_STATE_RECOVER 400

#define ID_ANI_KOOPA_WALKING 6000
#define ID_ANI_KOOPA_WALKING_RIGHT 6001
#define ID_ANI_KOOPA_DEFEND 6002
#define ID_ANI_KOOPA_SLIDE 6003
#define ID_ANI_KOOPA_RECOVER 6004
#define ID_ANI_KOOPA_DEFEND_UD 6005
#define ID_ANI_KOOPA_SLIDE_UD 6006
#define ID_ANI_KOOPA_RECOVER_UD 6007

class CKoopa :
	public CEnemy
{
protected:
	ULONGLONG recover_start;
	ULONGLONG defend_start;
	bool isBeingHold = false;
	bool isUpsideDown = false;

	float shakeVx;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return state!=ENEMY_STATE_DIE; };
	virtual int IsBlocking() { return 0; }
	virtual void HandleMarioRelease(float nx);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithEnemy(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithPlant(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithBlock(LPCOLLISIONEVENT e);
	virtual void ResetPos();

	virtual void OnNoCollision(DWORD dt);
	virtual void HoldingUpdate(DWORD dt);
public:
	CKoopa(float x, float y);
	virtual void SetState(int state);
	virtual bool IsDamagable() { return state != KOOPA_STATE_DEFEND && state != KOOPA_STATE_RECOVER && state != ENEMY_STATE_DIE; }
	virtual void OnCollisionByMario(LPCOLLISIONEVENT e);
	virtual void TakeJumpDamage();
	virtual void TakeTailAttackDamage(float xMario);
	virtual void TakeKoopaDamage(float xKoopa);
	virtual void TakeBlockBounceDamage(float xBlock);
};

