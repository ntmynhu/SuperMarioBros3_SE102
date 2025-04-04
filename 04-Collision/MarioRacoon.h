#pragma once
#include "MarioBig.h"

#define ID_ANI_MARIO_RACOON_IDLE_RIGHT 2000
#define ID_ANI_MARIO_RACOON_IDLE_LEFT 2001

#define ID_ANI_MARIO_RACOON_WALKING_RIGHT 2100
#define ID_ANI_MARIO_RACOON_WALKING_LEFT 2101

#define ID_ANI_MARIO_RACOON_RUNNING_RIGHT 2200
#define ID_ANI_MARIO_RACOON_RUNNING_LEFT 2201

#define ID_ANI_MARIO_RACOON_JUMP_WALK_RIGHT 2300
#define ID_ANI_MARIO_RACOON_JUMP_WALK_LEFT 2301

#define ID_ANI_MARIO_RACOON_JUMP_RUN_RIGHT 2400
#define ID_ANI_MARIO_RACOON_JUMP_RUN_LEFT 2401

#define ID_ANI_MARIO_RACOON_SIT_RIGHT 2500
#define ID_ANI_MARIO_RACOON_SIT_LEFT 2501

#define ID_ANI_MARIO_RACOON_BRACE_RIGHT 2600
#define ID_ANI_MARIO_RACOON_BRACE_LEFT 2601


class CMarioRacoon : public CMarioBig
{
private:
	bool isFlying = false;
	bool isTailAttacking = false;
	DWORD flyStartTime = 0;
	const float FLY_DURATION = 3000;
public:
    void Update(DWORD dt, CMario* mario, vector<LPGAMEOBJECT>* coObjects);
    int GetAniId(CMario* mario);
    void SetState(int state, CMario* mario);
    void GetBoundingBox(float& left, float& top, float& right, float& bottom, CMario* mario);
    int GetLevel() const;
    void OnTakeDamage(CMario* mario);

    void StartFlying() { isFlying = true; flyStartTime = GetTickCount(); }
    void StopFlying() { isFlying = false; }
    void TailAttack() { isTailAttacking = true; }
    bool IsFlying() const { return isFlying; }
    bool IsTailAttacking() const { return isTailAttacking; }
};

