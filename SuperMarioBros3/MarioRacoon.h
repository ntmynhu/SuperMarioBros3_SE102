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

#define ID_ANI_MARIO_RACOON_FALL_RIGHT 2350
#define ID_ANI_MARIO_RACOON_FALL_LEFT 2351

#define ID_ANI_MARIO_RACOON_SIT_RIGHT 2500
#define ID_ANI_MARIO_RACOON_SIT_LEFT 2501

#define ID_ANI_MARIO_RACOON_BRACE_RIGHT 2600
#define ID_ANI_MARIO_RACOON_BRACE_LEFT 2601

#define ID_ANI_MARIO_RACOON_TAIL_ATTACK_RIGHT 2700
#define ID_ANI_MARIO_RACOON_TAIL_ATTACK_LEFT 2701

#define ID_ANI_MARIO_RACOON_FLOATING_RIGHT 2800
#define ID_ANI_MARIO_RACOON_FLOATING_LEFT 2801

#define ID_ANI_MARIO_RACOON_FLOATING_TURBO_RIGHT 2810
#define ID_ANI_MARIO_RACOON_FLOATING_TURBO_LEFT 2811

#define ID_ANI_MARIO_RACOON_FULL_POWER_RUN_RIGHT 2910
#define ID_ANI_MARIO_RACOON_FULL_POWER_RUN_LEFT 2911

#define ID_ANI_FROM_BIG_TO_RACOON 1902

#define ID_ANI_RACOON_FLY_TAIL_UP_RIGHT 2970
#define ID_ANI_RACOON_FLY_TAIL_DOWN_RIGHT 2971
#define ID_ANI_RACOON_FLY_RIGHT 2972
#define ID_ANI_RACOON_FLY_TURBO_RIGHT 2973

#define ID_ANI_RACOON_FLY_TAIL_UP_LEFT 2930
#define ID_ANI_RACOON_FLY_TAIL_DOWN_LEFT 2931
#define ID_ANI_RACOON_FLY_LEFT 2932
#define ID_ANI_RACOON_FLY_TURBO_LEFT 2933

#define MARIO_FLYING_SPEED 0.25f
#define MARIO_FLYING_SPEED_X 0.1f

#define FLY_DURATION 5000
#define TAIL_FLOATING_DURATION 300

#define MARIO_BIG_TO_RACOON_DURATION 300

class CMarioRacoon : public CMarioBig
{
private:
    bool isFlying = false;
    DWORD flyStartTime = 0;

    ULONGLONG floatingStartTime = -1;
    bool isFloating = false;

	ULONGLONG tailAttackingStartTime = -1;
    int isTailAttacking = 0;

   

public:
    void Update(DWORD dt, CMario* mario, vector<LPGAMEOBJECT>* coObjects);
    int GetAniId(CMario* mario);
    void SetState(int state, CMario* mario);
    void GetBoundingBox(float& left, float& top, float& right, float& bottom, CMario* mario);
    int GetLevel() const;
    void OnTakeDamage(CMario* mario);

    int GetUpStateChangeTime() { return MARIO_BIG_TO_RACOON_DURATION; }

    void StartFlying() { isFlying = true; flyStartTime = GetTickCount64(); }
    void StopFlying() { isFlying = false; }
    void TailAttack() { isTailAttacking = true; }
    bool IsFlying() const { return isFlying; }
    int IsTailAttacking() const { return isTailAttacking; }

    void StartFloating() { isFloating = true; floatingStartTime = GetTickCount64(); }
    void StartTailAttacking(int nx) { isTailAttacking = nx; tailAttackingStartTime = GetTickCount64(); }
};

