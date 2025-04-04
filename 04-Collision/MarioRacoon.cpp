#include "MarioRacoon.h"
#include "Mario.h"

void CMarioRacoon::Update(DWORD dt, CMario* mario, vector<LPGAMEOBJECT>* coObjects)
{
	CMarioBig::Update(dt, mario, coObjects);

    // Slow falling mechanic when holding jump button
	float vx, vy, ax, ay, nx;
	mario->GetPhysics(vx, vy, ax, ay, nx);
    if (vy > 0 && mario->GetState() == MARIO_STATE_TURBO)
    {
        const float SLOW_FALL_GRAVITY = MARIO_GRAVITY * 0.9f;
        const float MAX_SLOW_FALL_SPEED = 0.15f;             

        float newVy = vy + SLOW_FALL_GRAVITY * dt;
        if (newVy > MAX_SLOW_FALL_SPEED)
            newVy = MAX_SLOW_FALL_SPEED;
        mario->SetVy(newVy);

        mario->SetAy(SLOW_FALL_GRAVITY);
    }
    else if (vy > 0 && !isFlying)
    {
        mario->SetAy(MARIO_GRAVITY);
    }
}

int CMarioRacoon::GetAniId(CMario* mario)
{
	return CMarioBig::GetAniId(mario);
}

void CMarioRacoon::SetState(int state, CMario* mario)
{
	CMarioBig::SetState(state, mario);
}

void CMarioRacoon::GetBoundingBox(float& left, float& top, float& right, float& bottom, CMario* mario)
{
	CMarioBig::GetBoundingBox(left, top, right, bottom, mario);
}

int CMarioRacoon::GetLevel() const
{
	return MARIO_LEVEL_RACOON;
}

void CMarioRacoon::OnTakeDamage(CMario* mario)
{
	mario->ChangeForm(MARIO_LEVEL_BIG);
	mario->StartUntouchable();
}
