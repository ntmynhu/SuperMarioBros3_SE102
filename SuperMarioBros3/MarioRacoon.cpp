#include "MarioRacoon.h"
#include "Mario.h"

void CMarioRacoon::Update(DWORD dt, CMario* mario, vector<LPGAMEOBJECT>* coObjects)
{
	CMarioBig::Update(dt, mario, coObjects);

	// Slow falling mechanic when holding jump button
	float vx, vy, ax, ay, nx;
	float m_x, m_y;
	mario->GetPosition(m_x, m_y);
	mario->GetPhysics(vx, vy, ax, ay, nx);

	// Handle flying
	if (!mario->IsOnPlatform() && isFlying)
	{
		if (mario->GetState() == MARIO_STATE_JUMP)
		{
			// Handle flying
			mario->SetVy(-MARIO_FLYING_SPEED);
			mario->SetAy(MARIO_GRAVITY);
		}
		else if (mario->GetState() == MARIO_STATE_TURBO_A)
		{
			// Handle flying
			mario->SetVy(-MARIO_FLYING_SPEED / 2);
			mario->SetAy(MARIO_GRAVITY);
		}
	}
	else if (vy > 0) // Handle Tail Floating
	{
		if (mario->GetState() == MARIO_STATE_JUMP)
		{
			// Slow fall mechanic
			const float SLOW_FALL_GRAVITY = MARIO_GRAVITY * 0.001f;
			const float MAX_SLOW_FALL_SPEED = 0.05f;

			float newVy = vy + SLOW_FALL_GRAVITY * dt;
			if (newVy > MAX_SLOW_FALL_SPEED)
				newVy = MAX_SLOW_FALL_SPEED;
			mario->SetVy(newVy);

			mario->SetAy(SLOW_FALL_GRAVITY);
			StartFloating();
		}
		else if (mario->GetState() == MARIO_STATE_TURBO_A)
		{
			const float SLOW_FALL_GRAVITY = MARIO_GRAVITY * 0.9f;
			const float MAX_SLOW_FALL_SPEED = 0.05f;

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

	if ((mario->GetState() == MARIO_STATE_B || mario->GetState() == MARIO_STATE_TURBO_B) && !isTailAttacking)
	{
		StartTailAttacking(nx);
	}

	if (GetTickCount64() - floatingStartTime > 200 && isFloating)
	{
		floatingStartTime = 0;
		isFloating = false;
		mario->SetAy(MARIO_GRAVITY);
	}

	if (GetTickCount64() - tailAttackingStartTime > TAIL_FLOATING_DURATION/2 && isTailAttacking)
	{
		isTailAttacking = -nx;
		if (GetTickCount64() - tailAttackingStartTime > TAIL_FLOATING_DURATION) {
			tailAttackingStartTime = 0;
			isTailAttacking = 0;
		}
	}

	if (GetTickCount64() - flyStartTime > FLY_DURATION)
	{
		isFlying = false;
		mario->SetAy(MARIO_GRAVITY);
	}
	else
	{
		if (!mario->IsOnPlatform()) mario->SetVx(MARIO_FLYING_SPEED_X * nx);
	}

	if (isTailAttacking != 0) {
		mario->GetTail()->SetPosition(m_x + isTailAttacking * 8, m_y + 4);
		mario->GetTail()->Update(dt, coObjects);
	}

	//DebugOutTitle(L"Vy: %d, IsFloating: %d, State %d", vy > 0, isFloating, mario->GetState());
}

int CMarioRacoon::GetAniId(CMario* mario)
{
	float vx, vy, ax, ay, nx;
	mario->GetPhysics(vx, vy, ax, ay, nx);

	int aniId = -1;

	if (mario->GetChangingState() == 1)
	{
		return ID_ANI_FROM_BIG_TO_RACOON;
	}

	if (mario->GetState() == MARIO_STATE_DOWN_TUNNEL || mario->GetState() == MARIO_STATE_UP_TUNNEL) return ID_ANI_MARIO_RACOON_PIPE;

	if (!mario->IsOnPlatform())
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (vy < 0)
			{
				if (nx >= 0)
					aniId = (mario->IsFullPower() || isFlying) ? ID_ANI_RACOON_FLY_TAIL_DOWN_RIGHT : ID_ANI_MARIO_RACOON_JUMP_RUN_RIGHT;
				else
					aniId = (mario->IsFullPower() || isFlying) ? ID_ANI_RACOON_FLY_TAIL_DOWN_LEFT : ID_ANI_MARIO_RACOON_JUMP_RUN_LEFT;
			}
			else
			{
				if (nx >= 0)
					aniId = isFlying? ID_ANI_RACOON_FLY_TAIL_UP_RIGHT : ID_ANI_MARIO_RACOON_FALL_RIGHT;
				else
					aniId = isFlying ? ID_ANI_RACOON_FLY_TAIL_UP_LEFT : ID_ANI_MARIO_RACOON_FALL_LEFT;
			}
		}
		else
		{
			if (isSitting && !isFlying)
			{
				if (nx > 0)
					aniId = ID_ANI_MARIO_SIT_RIGHT;
				else
					aniId = ID_ANI_MARIO_SIT_LEFT;
			}
			else if (vy < 0)
			{
				if (nx >= 0)
					aniId = isFlying ? ID_ANI_RACOON_FLY_RIGHT : ID_ANI_MARIO_RACOON_JUMP_WALK_RIGHT;
				else
					aniId = isFlying ? ID_ANI_RACOON_FLY_LEFT : ID_ANI_MARIO_RACOON_JUMP_WALK_LEFT;

			}
			else
			{
				if (nx >= 0)
					aniId = isFlying ? ID_ANI_RACOON_FLY_TAIL_UP_RIGHT : ID_ANI_MARIO_RACOON_FALL_RIGHT;
				else
					aniId = isFlying ? ID_ANI_RACOON_FLY_TAIL_UP_LEFT : ID_ANI_MARIO_RACOON_FALL_LEFT;
			}
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
				else if (mario->IsFullPower() && mario->GetState() == MARIO_STATE_RUNNING_RIGHT)
					aniId = ID_ANI_MARIO_RACOON_FULL_POWER_RUN_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X || ax == MARIO_DECEL_RUN_X)
					aniId = ID_ANI_MARIO_RACOON_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X || ax == MARIO_DECEL_WALK_X)
					aniId = ID_ANI_MARIO_RACOON_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0 && (mario->GetState() == MARIO_STATE_WALKING_RIGHT || mario->GetState() == MARIO_STATE_RUNNING_RIGHT))
					aniId = ID_ANI_MARIO_RACOON_BRACE_LEFT;
				else if (mario->IsFullPower() && mario->GetState() == MARIO_STATE_RUNNING_LEFT)
					aniId = ID_ANI_MARIO_RACOON_FULL_POWER_RUN_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X || ax == -MARIO_DECEL_RUN_X)
					aniId = ID_ANI_MARIO_RACOON_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X || ax == -MARIO_DECEL_WALK_X)
					aniId = ID_ANI_MARIO_RACOON_WALKING_LEFT;
			}

	if (isTailAttacking)
	{
		aniId = (nx > 0) ? ID_ANI_MARIO_RACOON_TAIL_ATTACK_RIGHT : ID_ANI_MARIO_RACOON_TAIL_ATTACK_LEFT;
	}

	if (isFloating)
	{
		if (nx > 0) aniId = ID_ANI_MARIO_RACOON_FLOATING_RIGHT;
		else aniId = ID_ANI_MARIO_RACOON_FLOATING_LEFT;
	}
	else if (mario->GetState() == MARIO_STATE_TURBO_A && !mario->IsOnPlatform())
	{
		if (!isFlying) 
			aniId = (nx > 0) ? ID_ANI_MARIO_RACOON_FLOATING_TURBO_RIGHT : ID_ANI_MARIO_RACOON_FLOATING_TURBO_LEFT;
		else
			aniId = (nx > 0) ? ID_ANI_RACOON_FLY_TURBO_RIGHT : ID_ANI_RACOON_FLY_TURBO_LEFT;
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
		if (isSitting) OnSitRelease(state, mario);
		if (!mario->IsFullPower())
		{
			mario->SetMaxVx(MARIO_RUNNING_SPEED);
		}
		else
		{
			mario->SetMaxVx(MARIO_FULL_POWER_SPEED_X);
		}
		mario->SetAx(MARIO_ACCEL_RUN_X);
		mario->SetNx(1);
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) OnSitRelease(state, mario);
		if (!mario->IsFullPower())
		{
			mario->SetMaxVx(-MARIO_RUNNING_SPEED);
		}
		else
		{
			mario->SetMaxVx(-MARIO_FULL_POWER_SPEED_X);
		}
		mario->SetAx(-MARIO_ACCEL_RUN_X);
		mario->SetNx(-1);
		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting) OnSitRelease(state, mario);
		mario->SetMaxVx(MARIO_WALKING_SPEED);
		mario->SetAx(MARIO_ACCEL_WALK_X);
		mario->SetNx(1);
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting) OnSitRelease(state, mario);
		mario->SetMaxVx(-MARIO_WALKING_SPEED);
		mario->SetAx(-MARIO_ACCEL_WALK_X);
		mario->SetNx(-1);
		break;
	case MARIO_STATE_JUMP:
		if (mario->IsOnPlatform())
		{
			if (abs(vx) == MARIO_RUNNING_SPEED)
				mario->SetVy(-MARIO_JUMP_RUN_SPEED_Y);
			else if (abs(vx) == MARIO_FULL_POWER_SPEED_X)
			{
				mario->SetVy(-MARIO_JUMP_RUN_SPEED_Y);
				StartFlying();
			}
			else
				mario->SetVy(-MARIO_JUMP_SPEED_Y);
		}
		break;

	case MARIO_STATE_B:

		break;

	case MARIO_STATE_TURBO_A:
		if (mario->IsOnPlatform())
		{
			mario->SetVy(-MARIO_JUMP_SPEED_Y/1.5);

			if (abs(vx) == MARIO_FULL_POWER_SPEED_X)
			{
				mario->SetVy(-MARIO_JUMP_RUN_SPEED_Y);
				StartFlying();
			}
		}
		break;

	case MARIO_STATE_TURBO_B:
		
		break;

	case MARIO_STATE_RELEASE_JUMP:
		if (vy < 0 && !isFloating && !isFlying)
		{
			float newVy = vy + MARIO_JUMP_SPEED_Y / 3;
			mario->SetVy(newVy);
		}
		break;

	case MARIO_STATE_SIT:
		if (abs(ax) == MARIO_ACCEL_RUN_X) break;

		if (!isSitting && mario->IsOnPlatform())
		{
			isSitting = true;
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
			mario->SetAx(MARIO_DECEL_WALK_X);
		else
			mario->SetAx(-MARIO_DECEL_WALK_X);
		break;
	}
}

void CMarioRacoon::GetBoundingBox(float& left, float& top, float& right, float& bottom, CMario* mario)
{
	float x, y;
	mario->GetPosition(x, y);

	float vx, vy, ax, ay, nx;
	mario->GetPhysics(vx, vy, ax, ay, nx);

	if (isSitting)
	{
		left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2 + nx * 4;
		top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
		right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
		bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
	}
	else
	{
		left = x - MARIO_BIG_BBOX_WIDTH / 2 + nx * 4;
		top = y - MARIO_BIG_BBOX_HEIGHT / 2;
		right = left + MARIO_BIG_BBOX_WIDTH;
		bottom = top + MARIO_BIG_BBOX_HEIGHT;
	}	
}

int CMarioRacoon::GetLevel() const
{
	return MARIO_LEVEL_RACOON;
}

void CMarioRacoon::OnTakeDamage(CMario* mario)
{
	if (isSitting) OnSitRelease(MARIO_STATE_IDLE ,mario);
	mario->SetAy(MARIO_GRAVITY);
	mario->ChangeForm(MARIO_LEVEL_BIG, -1);
	mario->StartUntouchable();
}
