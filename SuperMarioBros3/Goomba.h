#pragma once
#include "Enemy.h"

#define GOOMBA_GRAVITY 0.002f
#define GOOMBA_WALKING_SPEED 0.05f


#define GOOMBA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 14
#define GOOMBA_BBOX_HEIGHT_DIE 7

#define GOOMBA_DIE_TIMEOUT 200
#define GOOMBA_DIE_UD_TIMEOUT 2000

#define GOOMBA_STATE_WALKING 100


#define ID_ANI_GOOMBA_WALKING 5000
#define ID_ANI_GOOMBA_DIE 5001
#define ID_ANI_GOOMBA_DIE_UPSIDE_DOWN 5002

class CGoomba : public CEnemy
{
protected:
	bool isUpsideDown = false;
	
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return state != ENEMY_STATE_DIE; };
	virtual int IsBlocking() { return 0; }

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	

public:
	CGoomba(float x, float y);
	virtual void SetState(int state);
	virtual bool IsDamagable() { return state != ENEMY_STATE_DIE; }
	virtual void OnCollisionByMario(LPCOLLISIONEVENT e);
	virtual void TakeJumpDamage();
	virtual void TakeKoopaDamage(float xKoopa);
};