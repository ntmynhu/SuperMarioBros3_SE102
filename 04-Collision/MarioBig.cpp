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
	if (!mario->IsOnPlatform())
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
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
				if (nx > 0) aniId = ID_ANI_MARIO_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0 && (mario->GetState() == MARIO_STATE_WALKING_LEFT || mario->GetState() == MARIO_STATE_RUNNING_LEFT))
					aniId = ID_ANI_MARIO_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0 && (mario->GetState() == MARIO_STATE_WALKING_RIGHT || mario->GetState() == MARIO_STATE_RUNNING_RIGHT))
					aniId = ID_ANI_MARIO_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_LEFT;
			}

	if (aniId == -1)
	{
		if (nx > 0) aniId = ID_ANI_MARIO_IDLE_RIGHT;
		else aniId = ID_ANI_MARIO_IDLE_LEFT;
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
		if (vy < 0)
		{
			float newVy = vy + MARIO_JUMP_SPEED_Y / 2;
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
	mario->ChangeForm(MARIO_LEVEL_SMALL);
	mario->StartUntouchable();
}
