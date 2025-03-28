#include "MarioSmall.h"

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
		mario->SetMaxVx(MARIO_RUNNING_SPEED);
		mario->SetAx(MARIO_ACCEL_RUN_X);
		mario->SetNx(1);
		break;
	case MARIO_STATE_RUNNING_LEFT:
		mario->SetMaxVx(-MARIO_RUNNING_SPEED);
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
			else
				mario->SetVy(-MARIO_JUMP_SPEED_Y);
		}
		break;

	case MARIO_STATE_RELEASE_JUMP:
		if (vy < 0)
		{
			float newVy = vy + MARIO_JUMP_SPEED_Y / 2;
			mario->SetVy(newVy);
		}
		break;

	case MARIO_STATE_IDLE:
		mario->SetVx(0);
		mario->SetAx(0);
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

//
// Get animation ID for small Mario
//
int CMarioSmall::GetAniId(CMario* mario)
{
	int aniId = -1;
	float vx, vy, ax, ay, nx;
	mario->GetPhysics(vx, vy, ax, ay, nx);

	if (!mario->IsOnPlatform())
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
		}
	}
	else
		if (mario->IsSitting())
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}
