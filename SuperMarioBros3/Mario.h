#pragma once
#include "GameObject.h"
#include "Enemy.h"

#include "Animation.h"
#include "Animations.h"

#include "MarioSmall.h"
#include "MarioBig.h"
#include "MarioRacoon.h"

#include "debug.h"

#define MARIO_WALKING_SPEED		0.1f
#define MARIO_RUNNING_SPEED		0.2f

#define MARIO_DECEL_WALK_X	-0.0004f

#define MARIO_ACCEL_WALK_X	0.0004f
#define MARIO_ACCEL_RUN_X	0.0006f

#define MARIO_JUMP_SPEED_Y		0.6f
#define MARIO_JUMP_RUN_SPEED_Y	0.65f

#define MARIO_GRAVITY			0.002f

#define MARIO_JUMP_DEFLECT_SPEED  0.4f

#define MARIO_STATE_DIE				-10
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200

#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301

#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	500

#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601

#define MARIO_STATE_B			700
#define MARIO_STATE_B_RELEASE	701
#define MARIO_STATE_TURBO_A		800
#define MARIO_STATE_TURBO_B		900

#pragma region ANIMATION_ID

#define ID_ANI_MARIO_DIE 999

#pragma endregion

#define GROUND_Y 160.0f

#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define	MARIO_LEVEL_RACOON	3


#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)


#define MARIO_UNTOUCHABLE_TIME 2000
#define MARIO_STATE_CHANGE_TIME 2000

class CMario : public CGameObject
{
	CMarioForm* currentForm = nullptr;

	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 

	int level;
	int untouchable;
	ULONGLONG untouchable_start;
	BOOLEAN isOnPlatform;
	bool isReadyToHold;
	CEnemy* holdingObj;
	int coin;

	ULONGLONG stateChange_start;
	bool isChangingState;

	void OnCollisionWithEnemy(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithPlant(LPCOLLISIONEVENT e);
	void OnCollisionWithFireBall(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBlock(LPCOLLISIONEVENT e);

public:
	CMario(float x, float y) : CGameObject(x, y)
	{
		currentForm = new CMarioRacoon();
		level = MARIO_LEVEL_RACOON;

		maxVx = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY;

		untouchable = 0;
		untouchable_start = -1;

		isChangingState = false;
		stateChange_start = -1;

		isOnPlatform = false;
		coin = 0;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void HoldingUpdate(DWORD dt);
	void Render();
	void SetState(int state);
	void ChangeForm(int newLevel);

	int IsCollidable()
	{
		return (state != MARIO_STATE_DIE);
	}

	bool IsReadyToHold() { return isReadyToHold; }
	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable == 0); }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void SetLevel(int l);
	void SetHoldingObject(CEnemy* obj) { this->holdingObj = obj; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }
	void StartChangingState() { isChangingState = true; stateChange_start = GetTickCount64(); }

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	bool IsOnPlatform() { return isOnPlatform; }
	void GetPhysics(float& vx, float& vy, float& ax, float& ay, float& nx) { vx = this->vx; vy = this->vy; ax = this->ax; ay = this->ay; nx = this->nx; }
	void GetPosition(float& x, float& y) { x = this->x; y = this->y; }
	int GetLevel() { return currentForm->GetLevel(); }
	CMarioForm* GetCurrentForm() { return currentForm; }
	void GetHoldOffset(float &ox, float &oy) { 
		float res_ox, res_oy;
		currentForm->GetHoldOffset(res_ox, res_oy);
		ox = res_ox;
		oy = res_oy;
	}

	void TakeDamage() { currentForm->OnTakeDamage(this); }
	void SetMaxVx(float maxVx) { this->maxVx = maxVx; }
	void SetOnPlatform(bool isOnPlatform) { this->isOnPlatform = isOnPlatform; }
	void SetAx(float ax) { this->ax = ax; }
	void SetAy(float ay) { this->ay = ay; }
	void SetVx(float vx) { this->vx = vx; }
	void SetVy(float vy) { this->vy = vy; }
	void SetNx(int nx) { this->nx = nx; }
	void SetPosition(float x, float y) { this->x = x; this->y = y; }
};