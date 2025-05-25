#pragma once
#include "Enemy.h"
#include "Boomerang.h"
#include <random>

#define BOOMERANG_BRO_VX 0.028f
#define BOOMERANG_BRO_VY 0.25f

#define BOOMERANG_BRO_GRAVITY 0.001f

#define BOOMERANG_BRO_STATE_WALKING 700
#define BOOMERANG_BRO_STATE_PREPARE_THROWING 701

#define BOOMERANG_BRO_JUMP_TIMEOUT 4000
#define BOOMERANG_BRO_THROW_TIMEOUT 5000
#define BOOMERANG_BRO_PREPARE_TIMEOUT 500
#define BOOMERANG_BRO_DIE_TIMEOUT 4000

#define BOOMERANG_BRO_RANGE 32

#define BOOMERANG_BRO_BBOX_WIDTH 16
#define BOOMERANG_BRO_BBOX_HEIGHT 20

#define BOOMERANG_BRO_PREPARE_BBOX_WIDTH 24
#define BOOMERANG_BRO_PREPARE_BBOX_HEIGHT 26

#define BOOMERANG_BRO_BOOMERANG_DELAY 1000
#define BOOMERANG_BRO_TURN_DELAY 150

#define BOOMERANG_BRO_2_BOOMERANG_RANGE 96
#define BOOMERANG_BRO_ATTACK_RANGE 112

#define ID_ANI_BOOMERANG_BRO_WALK_LEFT 8001
#define ID_ANI_BOOMERANG_BRO_WALK_RIGHT 8002
#define ID_ANI_BOOMERANG_BRO_PREPARE_LEFT 8003
#define ID_ANI_BOOMERANG_BRO_PREPARE_RIGHT 8004
#define ID_ANI_BOOMERANG_BRO_DIE_LEFT 8005
#define ID_ANI_BOOMERANG_BRO_DIE_RIGHT 8006

class CBoomerangBros :
    public CEnemy
{
protected:
	random_device rd;
	mt19937 gen{ rd() };

	ULONGLONG jump_start = -1;
	ULONGLONG throw_start = -1;
	ULONGLONG prepare_start = -1;
	ULONGLONG switch_start = -1;
	ULONGLONG throw_timeout;

	CBoomerang* boomerang1;
	CBoomerang* boomerang2;

	float min_x, max_x;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return state != ENEMY_STATE_DIE; };
	virtual int IsBlocking() { return 0; }

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithBoomerang(LPCOLLISIONEVENT e);

	virtual void FaceMario();
	virtual void MakeJump();
	virtual int Throwable();
	virtual void MakeThrow1();
	virtual void MakeThrow2();

public:
	CBoomerangBros(float x, float y) :CEnemy(x, y) {
		this->ay = BOOMERANG_BRO_GRAVITY;
		
		uniform_real_distribution<> dis(-1, 1);

		double random_value = dis(gen);

		min_x = random_value < 0 ? init_x : init_x - BOOMERANG_BRO_RANGE; //randomly choose
		max_x = min_x + BOOMERANG_BRO_RANGE;
		throw_timeout = BOOMERANG_BRO_THROW_TIMEOUT;
		SetState(BOOMERANG_BRO_STATE_WALKING);
	}
	virtual void ResetPos() {
		CEnemy::ResetPos();
		uniform_real_distribution<> dis(-1, 1);

		double random_value = dis(gen);

		min_x = random_value < 0 ? init_x : init_x - BOOMERANG_BRO_RANGE; //randomly choose
		max_x = min_x + BOOMERANG_BRO_RANGE;
		SetState(BOOMERANG_BRO_STATE_WALKING);
	}

	virtual void SetBoomerangs(CBoomerang* boomerang1, CBoomerang* boomerang2) {
		this->boomerang1 = boomerang1;
		this->boomerang2 = boomerang2;
		boomerang1->Deactivate();
		boomerang2->Deactivate();
	}

	virtual bool PreventDefaultScoring() { return true; }
	virtual void SetState(int state);
	virtual bool IsDamagable() { return state != ENEMY_STATE_DIE; }
	virtual void OnCollisionByMario(LPCOLLISIONEVENT e);
	virtual void TakeJumpDamage();
	virtual void TakeTailAttackDamage(float xMario);
	virtual void TakeKoopaDamage(float xKoopa);
};

