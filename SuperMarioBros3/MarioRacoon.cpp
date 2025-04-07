#include "MarioRacoon.h"
#include "Mario.h"

void CMarioRacoon::Update(DWORD dt, CMario* mario, vector<LPGAMEOBJECT>* coObjects)
{
	CMarioBig::Update(dt, mario, coObjects);

	// Slow falling mechanic when holding jump button
	float vx, vy, ax, ay, nx;
	mario->GetPhysics(vx, vy, ax, ay, nx);

	if (vy > 0)
	{
		if (mario->GetState() == MARIO_STATE_JUMP)
		{
			//mario->SetVy(-MARIO_JUMP_SPEED_Y/3);
			const float SLOW_FALL_GRAVITY = MARIO_GRAVITY * 0.001f;
			const float MAX_SLOW_FALL_SPEED = 0.05f;

			float newVy = vy + SLOW_FALL_GRAVITY * dt;
			if (newVy > MAX_SLOW_FALL_SPEED)
				newVy = MAX_SLOW_FALL_SPEED;
			mario->SetVy(newVy);

			mario->SetAy(SLOW_FALL_GRAVITY);
			StartFloating();
		}
		else if (mario->GetState() == MARIO_STATE_TURBO)
		{
			const float SLOW_FALL_GRAVITY = MARIO_GRAVITY * 0.9f;
			const float MAX_SLOW_FALL_SPEED = 0.15f;

			float newVy = vy + SLOW_FALL_GRAVITY * dt;
			if (newVy > MAX_SLOW_FALL_SPEED)
				newVy = MAX_SLOW_FALL_SPEED;
			mario->SetVy(newVy);

			mario->SetAy(SLOW_FALL_GRAVITY);
		}

		if (isFloating)
		{
			//mario->SetVy(-MARIO_JUMP_SPEED_Y/3);
			const float SLOW_FALL_GRAVITY = MARIO_GRAVITY * 0.001f;
			const float MAX_SLOW_FALL_SPEED = 0.05f;

			float newVy = vy + SLOW_FALL_GRAVITY * dt;
			if (newVy > MAX_SLOW_FALL_SPEED)
				newVy = MAX_SLOW_FALL_SPEED;
			mario->SetVy(newVy);

			mario->SetAy(SLOW_FALL_GRAVITY);
		}
	}


	if (mario->IsOnPlatform()) {
		mario->SetAy(MARIO_GRAVITY);
		isFloating = false;
	}

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount64() - floatingStartTime > 200 && isFloating)
	{
		floatingStartTime = 0;
		isFloating = false;
		mario->SetAy(MARIO_GRAVITY);
	}

	DebugOutTitle(L"Vy: %d, IsFloating: %d, State %d", vy > 0, isFloating, mario->GetState());
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
	float vx, vy, ax, ay, nx;
	mario->GetPhysics(vx, vy, ax, ay, nx);

	switch (state)
	{
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting) break;
		mario->SetMaxVx(MARIO_RUNNING_SPEED);
		mario->SetAx(MARIO_ACCEL_RUN_X);
		mario->SetNx(1);
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		mario->SetMaxVx(-MARIO_RUNNING_SPEED);
		mario->SetAx(-MARIO_ACCEL_RUN_X);
		mario->SetNx(-1);
		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting) break;
		mario->SetMaxVx(MARIO_WALKING_SPEED);
		mario->SetAx(MARIO_ACCEL_WALK_X);
		mario->SetNx(1);
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting) break;
		mario->SetMaxVx(-MARIO_WALKING_SPEED);
		mario->SetAx(-MARIO_ACCEL_WALK_X);
		mario->SetNx(-1);
		break;
	case MARIO_STATE_JUMP:
		if (mario->IsOnPlatform())
		{
			if (abs(vx) == MARIO_RUNNING_SPEED)
				mario->SetVy(-MARIO_JUMP_RUN_SPEED_Y);
			else
				mario->SetVy(-MARIO_JUMP_SPEED_Y);
		}
		break;

	case MARIO_STATE_RELEASE_JUMP:
		if (vy < 0 && !isFloating)
		{
			float newVy = vy + MARIO_JUMP_SPEED_Y / 3;
			mario->SetVy(newVy);
		}
		break;

	case MARIO_STATE_SIT:
		if (mario->IsOnPlatform())
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			mario->SetVx(0); mario->SetVy(0.0f);

			float x, y;
			mario->GetPosition(x, y);
			mario->SetPosition(x, y + MARIO_SIT_HEIGHT_ADJUST);
		}
		break;

	case MARIO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;

			float x, y;
			mario->GetPosition(x, y);
			mario->SetPosition(x, y - MARIO_SIT_HEIGHT_ADJUST);
		}
		break;

	case MARIO_STATE_IDLE:
		if (nx > 0)
			mario->SetAx(-MARIO_ACCEL_WALK_X);
		else
			mario->SetAx(MARIO_ACCEL_WALK_X);
		break;
	}
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
