#include "Paragoomba.h"
#include "Mario.h"
#include "debug.h"
void CParagoomba::TakeJumpDamage() {
	if (state == PARA_GOOMBA_STATE_HASWING) {
		SetState(GOOMBA_STATE_WALKING);
		return;
	}
	CGoomba::TakeJumpDamage();
}

void CParagoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == PARA_GOOMBA_STATE_HASWING) {
		left = x - PARA_GOOMBA_BBOX_WIDTH / 2;
		top = y - PARA_GOOMBA_BBOX_HEIGHT / 2;
		right = left + PARA_GOOMBA_BBOX_WIDTH;
		bottom = top + PARA_GOOMBA_BBOX_HEIGHT;
		return;
	}
	
	CGoomba::GetBoundingBox(left, top, right, bottom);
}

void CParagoomba::Render()
{
	int aniId = ID_ANI_PARA_GOOMBA_WING;
	switch (state) {
	case (ENEMY_STATE_DIE):
		if (isUpsideDown) aniId = ID_ANI_PARA_GOOMBA_DIE_UPSIDE_DOWN;
		else aniId = ID_ANI_PARA_GOOMBA_DIE;
		break;
	case (GOOMBA_STATE_WALKING):
		aniId = ID_ANI_PARA_GOOMBA_WALKING;
		break;
	case (PARA_GOOMBA_STATE_HASWING):
		if (jumpCount == 4)
			aniId = ID_ANI_PARA_GOOMBA_FLY;
		else if (jumpCount != 0)
			aniId = ID_ANI_PARA_GOOMBA_HOP;
		break;
	}
	
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}


void CParagoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (HasWing()) {
		if (GetTickCount64() - walk_start >= PARA_GOOMBA_WALK_TIMEOUT && !isFlying)
		{
			isFlying = true;
			jumpCount = 0;
		}
		if (isFlying && isOnPlatform) {
			if (jumpCount < PARA_GOOMBA_SMALL_JUMP_LIMIT)
			{
				vy = -PARA_GOOMBA_SMALL_JUMP_SPEED_Y;
				jumpCount++;
			}
			else
			{
				vy = -PARA_GOOMBA_FLY_SPEED_Y;
				ay = GOOMBA_GRAVITY * 0.5;
				jumpCount = 4;
				isFlying = false; //After one fly, no longer fly
				walk_start = GetTickCount64(); //Start walking
			}

		}
		else if (!isFlying && isOnPlatform) {
			jumpCount = 0;
			ay = GOOMBA_GRAVITY;
		}


	}

	CGoomba::Update(dt, coObjects);
}