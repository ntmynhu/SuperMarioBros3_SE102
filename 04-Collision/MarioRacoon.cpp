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
	float vx, vy, ax, ay, nx;
	mario->GetPhysics(vx, vy, ax, ay, nx);

	int aniId = -1;
	if (!mario->IsOnPlatform())
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_RACOON_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACOON_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_RACOON_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACOON_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_RACOON_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACOON_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_RACOON_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_RACOON_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0 && (mario->GetState() == MARIO_STATE_WALKING_LEFT || mario->GetState() == MARIO_STATE_RUNNING_LEFT))
					aniId = ID_ANI_MARIO_RACOON_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RACOON_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_RACOON_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0 && (mario->GetState() == MARIO_STATE_WALKING_RIGHT || mario->GetState() == MARIO_STATE_RUNNING_RIGHT))
					aniId = ID_ANI_MARIO_RACOON_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RACOON_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_RACOON_WALKING_LEFT;
			}

	if (aniId == -1)
	{
		if (nx > 0) aniId = ID_ANI_MARIO_RACOON_IDLE_RIGHT;
		else aniId = ID_ANI_MARIO_RACOON_IDLE_LEFT;
	}

	return aniId;
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
