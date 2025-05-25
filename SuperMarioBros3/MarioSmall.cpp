#include "MarioSmall.h"
#include "Mario.h"

void CMarioSmall::Update(DWORD dt, CMario* mario, vector<LPGAMEOBJECT>* coObjects)
{
	// No additional updates needed
}

void CMarioSmall::SetState(int state, CMario* mario)
{
	float vx, vy, ax, ay, nx;
	mario->GetPhysics(vx, vy, ax, ay, nx);

	switch (state)
	{
	case MARIO_STATE_RUNNING_RIGHT:
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
		mario->SetMaxVx(MARIO_WALKING_SPEED);
		mario->SetAx(MARIO_ACCEL_WALK_X);
		mario->SetNx(1);
		break;
	case MARIO_STATE_WALKING_LEFT:
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

	case MARIO_STATE_IDLE:
		if (vx == 0) return;
		if (nx > 0)
			mario->SetAx(MARIO_DECEL_WALK_X);
		else
			mario->SetAx(-MARIO_DECEL_WALK_X);
		break;
	}
}

void CMarioSmall::GetBoundingBox(float& left, float& top, float& right, float& bottom, CMario* mario)
{
	float x, y;
	mario->GetPosition(x, y);

	left = x - MARIO_SMALL_BBOX_WIDTH / 2;
	top = y - MARIO_SMALL_BBOX_HEIGHT / 2;
	right = left + MARIO_SMALL_BBOX_WIDTH;
	bottom = top + MARIO_SMALL_BBOX_HEIGHT;
}

int CMarioSmall::GetLevel() const
{
	return MARIO_LEVEL_SMALL;
}

void CMarioSmall::OnTakeDamage(CMario* mario)
{
	mario->SetState(MARIO_STATE_DIE);
}

int CMarioSmall::GetKickAniId(CMario* mario)
{
	return (mario->GetNx() > 0) ? ID_ANI_MARIO_SMALL_KICK_RIGHT : ID_ANI_MARIO_SMALL_KICK_LEFT;
}

//
// Get animation ID for small Mario
//
int CMarioSmall::GetAniId(CMario* mario)
{
	int aniId = -1;
	float vx, vy, ax, ay, nx;
	mario->GetPhysics(vx, vy, ax, ay, nx);

	if (mario->GetState() == MARIO_STATE_DOWN_TUNNEL || mario->GetState() == MARIO_STATE_UP_TUNNEL) return ID_ANI_MARIO_SMALL_PIPE;

	if (!mario->IsOnPlatform())
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				if (!mario->IsFullPower()) aniId = mario->IsHolding() ? ID_ANI_MARIO_SMALL_JUMP_HOLDING_RIGHT : ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
				else aniId = mario->IsHolding() ? ID_ANI_MARIO_SMALL_FULL_POWER_JUMP_HOLDING_RIGHT : ID_ANI_MARIO_SMALL_FULL_POWER_JUMP_RIGHT;
			else
				if (!mario->IsFullPower()) aniId = mario->IsHolding()? ID_ANI_MARIO_SMALL_JUMP_HOLDING_LEFT : ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
				else aniId = mario->IsHolding() ? ID_ANI_MARIO_SMALL_FULL_POWER_JUMP_HOLDING_LEFT : ID_ANI_MARIO_SMALL_FULL_POWER_JUMP_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = mario->IsHolding() ? ID_ANI_MARIO_SMALL_JUMP_HOLDING_RIGHT : ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
			else
				aniId = mario->IsHolding() ? ID_ANI_MARIO_SMALL_JUMP_HOLDING_LEFT : ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
		}
	}
	else
		if (vx == 0)
		{
			if (nx >= 0) aniId = mario->IsHolding() ? ID_ANI_MARIO_SMALL_IDLE_HOLDING_RIGHT : ID_ANI_MARIO_SMALL_IDLE_RIGHT;
			else aniId = mario->IsHolding() ? ID_ANI_MARIO_SMALL_IDLE_HOLDING_LEFT : ID_ANI_MARIO_SMALL_IDLE_LEFT;
		}
		else if (vx > 0)
		{
			if (ax < 0 && (mario->GetState() == MARIO_STATE_WALKING_LEFT || mario->GetState() == MARIO_STATE_RUNNING_LEFT) && !mario->IsHolding())
				aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
			else if (mario->IsFullPower() && mario->GetState() == MARIO_STATE_RUNNING_RIGHT)
				aniId = mario->IsHolding() ? ID_ANI_MARIO_SMALL_FULL_POWER_RUN_HOLDING_RIGHT : ID_ANI_SMALL_FULL_POWER_RUN_RIGHT;
			else if (ax == MARIO_ACCEL_RUN_X || ax == MARIO_DECEL_RUN_X)
				aniId = mario->IsHolding() ? ID_ANI_MARIO_SMALL_FULL_POWER_RUN_HOLDING_RIGHT : ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
			else if (ax == MARIO_ACCEL_WALK_X || ax == MARIO_DECEL_WALK_X)
				aniId = mario->IsHolding() ? ID_ANI_MARIO_SMALL_WALKING_HOLDING_RIGHT : ID_ANI_MARIO_SMALL_WALKING_RIGHT;
		}
		else // vx < 0
		{
			if (ax > 0 && (mario->GetState() == MARIO_STATE_WALKING_RIGHT || mario->GetState() == MARIO_STATE_RUNNING_RIGHT) && !mario->IsHolding())
				aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
			else if (mario->IsFullPower() && mario->GetState() == MARIO_STATE_RUNNING_LEFT)
				aniId = mario->IsHolding() ? ID_ANI_MARIO_SMALL_FULL_POWER_JUMP_HOLDING_LEFT : ID_ANI_SMALL_FULL_POWER_RUN_LEFT;
			else if (ax == -MARIO_ACCEL_RUN_X || ax == -MARIO_DECEL_RUN_X)
				aniId = mario->IsHolding() ? ID_ANI_MARIO_SMALL_RUNNING_HOLDING_LEFT : ID_ANI_MARIO_SMALL_RUNNING_LEFT;
			else if (ax == -MARIO_ACCEL_WALK_X || ax == -MARIO_DECEL_WALK_X)
				aniId = mario->IsHolding() ? ID_ANI_MARIO_SMALL_WALKING_HOLDING_LEFT : ID_ANI_MARIO_SMALL_WALKING_LEFT;
		}

	if (aniId == -1)
	{
		if (nx >= 0) aniId = mario->IsHolding()? ID_ANI_MARIO_SMALL_IDLE_HOLDING_RIGHT : ID_ANI_MARIO_SMALL_IDLE_RIGHT;
		else aniId = mario->IsHolding()? ID_ANI_MARIO_SMALL_IDLE_HOLDING_LEFT : ID_ANI_MARIO_SMALL_IDLE_LEFT;
	}

	return aniId;
}
