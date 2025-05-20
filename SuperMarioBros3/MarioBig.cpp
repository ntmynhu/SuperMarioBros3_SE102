#include "MarioBig.h"
#include "Mario.h"

void CMarioBig::Update(DWORD dt, CMario* mario, vector<LPGAMEOBJECT>* coObjects)
{
	// No additional updates needed
}

int CMarioBig::GetAniId(CMario* mario)
{
	float vx, vy, ax, ay, nx;
	mario->GetPhysics(vx, vy, ax, ay, nx);

	int aniId = -1;

	if (mario->GetChangingState() == 1)
	{
		return (nx > 0) ? ID_ANI_FROM_SMALL_TO_BIG_RIGHT : ID_ANI_FROM_SMALL_TO_BIG_LEFT;
	}
	if (mario->GetState() == MARIO_STATE_DOWN_TUNNEL || mario->GetState() == MARIO_STATE_UP_TUNNEL) return ID_ANI_MARIO_PIPE;
	if (!mario->IsOnPlatform())
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				if (!mario->IsFullPower()) aniId = mario->IsHolding() ? ID_ANI_MARIO_BIG_JUMP_HOLDING_RIGHT : ID_ANI_MARIO_JUMP_WALK_RIGHT;
				else aniId = mario->IsHolding() ? ID_ANI_MARIO_BIG_JUMP_HOLDING_RIGHT : ID_ANI_MARIO_JUMP_RUN_RIGHT;
			else
				if (!mario->IsFullPower()) aniId = mario->IsHolding() ? ID_ANI_MARIO_BIG_JUMP_HOLDING_LEFT : ID_ANI_MARIO_JUMP_WALK_LEFT;
				else aniId = mario->IsHolding() ? ID_ANI_MARIO_BIG_JUMP_HOLDING_LEFT : ID_ANI_MARIO_JUMP_RUN_LEFT;
		}
		else
		{
			if (isSitting)
			{
				if (nx > 0)
					aniId = ID_ANI_MARIO_SIT_RIGHT;
				else
					aniId = ID_ANI_MARIO_SIT_LEFT;
			}
			else {
				if (nx >= 0)
					aniId = mario->IsHolding()? ID_ANI_MARIO_BIG_JUMP_HOLDING_RIGHT : ID_ANI_MARIO_JUMP_WALK_RIGHT;
				else
					aniId = mario->IsHolding() ? ID_ANI_MARIO_BIG_JUMP_HOLDING_LEFT : ID_ANI_MARIO_JUMP_WALK_LEFT;
			}
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = mario->IsHolding() ? ID_ANI_MARIO_BIG_IDLE_HOLDING_RIGHT : ID_ANI_MARIO_IDLE_RIGHT;
				else aniId = mario->IsHolding() ? ID_ANI_MARIO_BIG_IDLE_HOLDING_LEFT : ID_ANI_MARIO_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0 && (mario->GetState() == MARIO_STATE_WALKING_LEFT || mario->GetState() == MARIO_STATE_RUNNING_LEFT) && !mario->IsHolding())
					aniId = ID_ANI_MARIO_BRACE_RIGHT;
				else if (mario->IsFullPower() && mario->GetState() == MARIO_STATE_RUNNING_RIGHT)
					aniId = mario->IsHolding() ? ID_ANI_MARIO_BIG_FULL_POWER_RUN_HOLDING_RIGHT : ID_ANI_MARIO_BIG_FULL_POWER_RUN_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X || ax == MARIO_DECEL_RUN_X)
					aniId = mario->IsHolding() ? ID_ANI_MARIO_BIG_RUNNING_HOLDING_RIGHT : ID_ANI_MARIO_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X || ax == MARIO_DECEL_WALK_X)
					aniId = mario->IsHolding() ? ID_ANI_MARIO_BIG_WALKING_HOLDING_RIGHT : ID_ANI_MARIO_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0 && (mario->GetState() == MARIO_STATE_WALKING_RIGHT || mario->GetState() == MARIO_STATE_RUNNING_RIGHT) && !mario->IsHolding())
					aniId = ID_ANI_MARIO_BRACE_LEFT;
				else if (mario->IsFullPower() && mario->GetState() == MARIO_STATE_RUNNING_LEFT)
					aniId = mario->IsHolding() ? ID_ANI_MARIO_BIG_FULL_POWER_RUN_HOLDING_LEFT : ID_ANI_MARIO_BIG_FULL_POWER_RUN_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X || ax == -MARIO_DECEL_RUN_X)
					aniId = mario->IsHolding() ? ID_ANI_MARIO_BIG_RUNNING_HOLDING_LEFT : ID_ANI_MARIO_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X || ax == -MARIO_DECEL_WALK_X)
					aniId = mario->IsHolding() ? ID_ANI_MARIO_BIG_WALKING_HOLDING_LEFT : ID_ANI_MARIO_WALKING_LEFT;
			}

	if (aniId == -1)
	{
		if (nx > 0) aniId = mario->IsHolding() ? ID_ANI_MARIO_BIG_IDLE_HOLDING_RIGHT : ID_ANI_MARIO_IDLE_RIGHT;
		else aniId = mario->IsHolding() ? ID_ANI_MARIO_BIG_IDLE_HOLDING_LEFT : ID_ANI_MARIO_IDLE_LEFT;
	}

	return aniId;
}

void CMarioBig::SetState(int state, CMario* mario)
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
		OnSitRelease(state, mario);
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
				mario->SetVy(-MARIO_FULL_POWER_SPEED_Y);
			else
				mario->SetVy(-MARIO_JUMP_SPEED_Y);
		}
		break;
	case MARIO_STATE_B:
		break;

	case MARIO_STATE_TURBO_A:
		if (mario->IsOnPlatform())
		{
			mario->SetVy(-MARIO_JUMP_SPEED_Y / 1.25);
		}
		break;

	case MARIO_STATE_TURBO_B:

		break;

	case MARIO_STATE_RELEASE_JUMP:
		if (vy < 0)
		{
			float newVy = vy + MARIO_JUMP_SPEED_Y / 2;
			mario->SetVy(newVy);
		}
		break;

	case MARIO_STATE_SIT:
		if (abs(ax) == MARIO_ACCEL_RUN_X) break;
		if (mario->IsHolding()) break;

		if (!isSitting && mario->IsOnPlatform())
		{
			isSitting = true;
			float x, y;
			mario->GetPosition(x, y);
			mario->SetPosition(x, y + MARIO_SIT_HEIGHT_ADJUST);
		}
		break;

	case MARIO_STATE_SIT_RELEASE:
		OnSitRelease(state, mario);
		break;

	case MARIO_STATE_IDLE:
		if (nx > 0)
			mario->SetAx(MARIO_DECEL_WALK_X);
		else
			mario->SetAx(-MARIO_DECEL_WALK_X);
		break;
	}
}

void CMarioBig::GetBoundingBox(float& left, float& top, float& right, float& bottom, CMario* mario)
{
	float x, y;
	mario->GetPosition(x, y);

	if (isSitting)
	{
		left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
		top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
		right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
		bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
	}
	else
	{
		left = x - MARIO_BIG_BBOX_WIDTH / 2;
		top = y - MARIO_BIG_BBOX_HEIGHT / 2;
		right = left + MARIO_BIG_BBOX_WIDTH;
		bottom = top + MARIO_BIG_BBOX_HEIGHT;
	}
}

int CMarioBig::GetLevel() const
{
	return MARIO_LEVEL_BIG;
}

void CMarioBig::OnTakeDamage(CMario* mario)
{
	if (isSitting)
		OnSitRelease(MARIO_STATE_IDLE, mario);

	mario->ChangeForm(MARIO_LEVEL_SMALL, -1);
	mario->StartUntouchable();
}

void CMarioBig::OnSitRelease(int state, CMario* mario)
{
	if (isSitting)
	{
		isSitting = false;
		state = MARIO_STATE_IDLE;

		float x, y;
		mario->GetPosition(x, y);
		mario->SetPosition(x, y - MARIO_SIT_HEIGHT_ADJUST);
	}
}