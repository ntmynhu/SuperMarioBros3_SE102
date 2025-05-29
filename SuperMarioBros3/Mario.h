#pragma once
#include "GameObject.h"
#include "Enemy.h"
#include "Tail.h"
#include "Animation.h"
#include "Animations.h"

#include "MarioSmall.h"
#include "MarioBig.h"
#include "MarioRacoon.h"

#include "debug.h"

#define MARIO_WALKING_SPEED		0.1f
#define MARIO_RUNNING_SPEED		0.15f
#define MARIO_FULL_POWER_SPEED_X	0.2f

#define MARIO_DECEL_WALK_X	-0.00015f
#define MARIO_DECEL_RUN_X	-0.00015f

#define MARIO_ACCEL_WALK_X	0.0004f
#define MARIO_ACCEL_RUN_X	0.0006f

#define MARIO_JUMP_SPEED_Y		0.375f
#define MARIO_JUMP_RUN_SPEED_Y	0.40f
#define MARIO_FULL_POWER_SPEED_Y	0.45f

#define MARIO_TUNNEL_SPEED_Y	0.05f

#define MARIO_GRAVITY			0.00095f

#define MARIO_JUMP_DEFLECT_SPEED  MARIO_JUMP_SPEED_Y / 1.5f

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

#define MARIO_STATE_CHANGING_UP 1000
#define MARIO_STATE_CHANGING_DOWN 1001

#define MARIO_STATE_DOWN_TUNNEL 1002
#define MARIO_STATE_UP_TUNNEL 1003

#pragma region ANIMATION_ID

#define ID_ANI_MARIO_DIE 999

#pragma endregion

#define GROUND_Y 160.0f

#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define	MARIO_LEVEL_RACOON	3

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)

#define MARIO_UNTOUCHABLE_TIME 2000
#define MARIO_DIE_TIME 2000

#define MARIO_CHARGING_POWER_TIME 900
#define MARIO_FULL_POWER_TIME 5000

#define MARIO_KICKING_TIME 200

class CMario : public CGameObject
{
	CMarioForm* currentForm = nullptr;

	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 

	int level;
	int untouchable;
	ULONGLONG untouchable_start;
	ULONGLONG die_start;

	BOOLEAN isOnPlatform;
	bool isReadyToHold;
	CEnemy* holdingObj;
	CGameObject* stickingObj;

	CTail* tail;
	int coin;

	int currentBaseScore = 100;

	ULONGLONG stateChange_start;
	int isChangingState; // -1 as down, 1 as up

	float chargingPowerTime = 0.0f;
	bool isChargingPower = false;

	float fullPowerTime = MARIO_FULL_POWER_TIME;
	bool isFullPower = false;
	bool isStickToPlatform = false;
	bool isInputLock = false;
	bool isEnding = false;
	bool isKicking = false;
	ULONGLONG kick_start = -1;

	bool isHoldingJump = false;

	void OnCollisionWithEnemy(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithPlant(LPCOLLISIONEVENT e);
	void OnCollisionWithThrowable(LPCOLLISIONEVENT e);
	void OnCollisionWithBlock(LPCOLLISIONEVENT e);
	void OnCollisionWithMovingPlatform(LPCOLLISIONEVENT e);
	void OnCollisionWithTunnel(LPCOLLISIONEVENT e);
	void OnCollisionWithMushroomAndLeaf(LPCOLLISIONEVENT e);
	void OnCollisionWithBlueButton(LPCOLLISIONEVENT e);
	void OnCollisionWithOneUpMushroom(LPCOLLISIONEVENT e);
	void OnCollisionWithPlatformKill(LPCOLLISIONEVENT e);
	void OnCollisionWithEndingCard(LPCOLLISIONEVENT e);

public:
	CMario(float x, float y) : CGameObject(x, y)
	{
		currentForm = new CMarioSmall();
		tail = new CTail(x, y);
		level = MARIO_LEVEL_SMALL;

		maxVx = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY;

		untouchable = 0;
		untouchable_start = -1;

		die_start = -1;

		isChangingState = 0;
		stateChange_start = -1;

		isOnPlatform = false;
		coin = 0;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void HoldingUpdate(DWORD dt);
	void Render();
	void SetState(int state);
	void ChangeForm(int newLevel, int isChanging = 0);
	
	void Deactivate() {}

	int IsCollidable()
	{
		return (state != MARIO_STATE_DIE);
	}

	bool IsReadyToHold() { return isReadyToHold; }
	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable == 0); }
	bool IsHolding() { return holdingObj != NULL; }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void SetLevel(int l);
	void SetIsStickToPlatform(CGameObject* stickObj) {
		this->stickingObj = stickObj;
		if (stickObj) isStickToPlatform = true;
		else isStickToPlatform = false;
	}
	void SetHoldingObject(CEnemy* obj) { this->holdingObj = obj; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }
	void StartChangingStateDown() { isChangingState = -1; stateChange_start = GetTickCount64(); }
	void StartChangingStateUp() { isChangingState = 1; stateChange_start = GetTickCount64(); }

	int GetChangingState() { return isChangingState; }
	float GetChargingPowerTime() { return chargingPowerTime; }
	float GetFullPowerTime() { return fullPowerTime; }

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	bool IsStickToPlatform() { return isStickToPlatform; }
	bool IsOnPlatform() { return isOnPlatform; }
	void GetPhysics(float& vx, float& vy, float& ax, float& ay, float& nx) { vx = this->vx; vy = this->vy; ax = this->ax; ay = this->ay; nx = this->nx; }
	void GetPosition(float& x, float& y) { x = this->x; y = this->y; }
	bool IsUntouchable() { return untouchable == 1; }

	int GetLevel() { return currentForm->GetLevel(); }
	CMarioForm* GetCurrentForm() { return currentForm; }
	void GetHoldOffset(float &ox, float &oy) { 
		float res_ox, res_oy;
		currentForm->GetHoldOffset(res_ox, res_oy);
		ox = res_ox;
		oy = res_oy;
	}

	CTail* GetTail() { return tail; }
	void TakeDamage() { currentForm->OnTakeDamage(this); }
	void SetMaxVx(float maxVx) { this->maxVx = maxVx; }
	void SetOnPlatform(bool isOnPlatform) { this->isOnPlatform = isOnPlatform; }
	void SetAx(float ax) { this->ax = ax; }
	void SetAy(float ay) { this->ay = ay; }
	void SetVx(float vx) { this->vx = vx; }
	void SetVy(float vy) { this->vy = vy; }
	void SetNx(int nx) { this->nx = nx; }
	int GetNx() { return nx; }
	void SetPosition(float x, float y) { this->x = x; this->y = y; }

	void SetHoldingJump(bool value) { isHoldingJump = value; }

	void InputLock() { isInputLock = true; };
	void InputUnlock() { isInputLock = false; };

	bool IsChargingPower() { return isChargingPower; }
	bool IsFullPower() { return isFullPower; }
	bool IsFlying() { 
		return currentForm->IsFlying();
	}
	void SetChargingPower(bool value)
	{
		isChargingPower = value;
	}

	bool IsFullSpeed();
	void TriggerKick() { isKicking = true; kick_start = GetTickCount64(); }
	bool IsKicking() { return isKicking; }
};