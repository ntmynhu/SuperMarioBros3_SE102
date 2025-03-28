#pragma once
#include "MarioBig.h"

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

