#pragma once
#include "Enemy.h"

#define KOOPA_GRAVITY 0.002f
#define KOOPA_WALKING_SPEED 0.05f
#define KOOPA_SLIDING_SPEED 0.2f
#define KOOPA_SHAKE_SPEED 0.05f

#define KOOPA_BBOX_WIDTH 16.0f
#define KOOPA_BBOX_WIDTH_DEFEND 16.0f
#define KOOPA_BBOX_HEIGHT 25.0f
#define KOOPA_BBOX_HEIGHT_DEFEND 16.0f

#define KOOPA_DEFEND_TIMEOUT 3000
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

class CKoopa :
    public CEnemy
{
protected:
	ULONGLONG recover_start;
	float left_lim = 0.0f;
	float right_lim = 0.0f;
	bool isUpsideDown = false;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithGround(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithEnemy(LPCOLLISIONEVENT e);

public:
	CKoopa(float x, float y);
	virtual void SetState(int state);
	virtual bool IsDamagable() { return state != KOOPA_STATE_DEFEND && state != KOOPA_STATE_RECOVER; }
	virtual void OnCollisionByMario(LPCOLLISIONEVENT e);
	virtual void TakeJumpDamage();
};

