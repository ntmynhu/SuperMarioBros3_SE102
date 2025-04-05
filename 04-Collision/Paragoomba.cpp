#include "Paragoomba.h"
#include "Mario.h"
#include "debug.h"
void CParagoomba::TakeDamage() {
	if (state == PARA_GOOMBA_STATE_HASWING) {
		SetState(GOOMBA_STATE_WALKING);
		return;
	}
	CGoomba::TakeDamage();
}

void CParagoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (HasWing()) {
		if (GetTickCount64() - walk_start >= PARA_GOOMBA_WALK_TIMEOUT && !isFlying)
		{
			isFlying = true;
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
				jumpCount = 0;
				isFlying = false; //After one fly, no longer fly
				walk_start = GetTickCount64(); //Start walking
			}

		}

		
	}
	
	CGoomba::Update(dt, coObjects);
}