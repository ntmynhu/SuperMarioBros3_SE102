#include "RedParakoopa.h"
void CRedParakoopa::TakeJumpDamage() {
	if (state == PARA_KOOPA_STATE_HASWING) {
		SetState(KOOPA_STATE_WALKING);
		return;
	}
	CRedKoopa::TakeJumpDamage();
}

void CRedParakoopa::ResetPos() {
	if (state != ENEMY_STATE_DIE) {
		CRedKoopa::ResetPos();
		SetState(PARA_KOOPA_STATE_HASWING);
		ay = 0;
		vy = -RED_PARA_KOOPA_FLY_SPEED_Y;
		vx = 0;
	}
}


void CRedParakoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (HasWing()) {
		if (vy == 0)
		{
			if (isOnPlatform) vy = -RED_PARA_KOOPA_FLY_SPEED_Y;
			else vy = RED_PARA_KOOPA_FLY_SPEED_Y;
		}

		if (y <= top_bound)
		{
			if (switch_start == -1)
			{
				vy = -RED_PARA_KOOPA_FLY_SMALL_SPEED_Y;
				switch_start = GetTickCount64();
			}
			if (GetTickCount64() - switch_start > RED_PARA_KOOPA_SWITCH_DELAY) {
				vy = RED_PARA_KOOPA_FLY_SPEED_Y;
				switch_start = -1;
			}
			
		}
		else if (y >= bot_bound) {
			if (switch_start == -1)
			{
				vy = RED_PARA_KOOPA_FLY_SMALL_SPEED_Y;
				switch_start = GetTickCount64();
			}
			if (GetTickCount64() - switch_start > RED_PARA_KOOPA_SWITCH_DELAY) {
				vy = -RED_PARA_KOOPA_FLY_SPEED_Y;
				switch_start = -1;
			}
		}
	}
	CRedKoopa::Update(dt, coObjects);
}
void CRedParakoopa::Render()
{
	int aniId = ID_ANI_RED_PARA_KOOPA_FLY;
	switch (state) {
	case (PARA_KOOPA_STATE_HASWING):
		if (vx > 0) {
			aniId = ID_ANI_RED_PARA_KOOPA_FLY_RIGHT;
		}
		break;
	case (KOOPA_STATE_DEFEND):
		if (isUpsideDown)
			aniId = ID_ANI_RED_KOOPA_DEFEND_UD;
		else aniId = ID_ANI_RED_KOOPA_DEFEND;
		break;
	case (KOOPA_STATE_DEFEND_SLIDING):
		if (isUpsideDown)
			aniId = ID_ANI_RED_KOOPA_SLIDE_UD;
		else aniId = ID_ANI_RED_KOOPA_SLIDE;
		break;
	case (KOOPA_STATE_RECOVER):
		if (isUpsideDown)
			aniId = ID_ANI_RED_KOOPA_RECOVER_UD;
		else aniId = ID_ANI_RED_KOOPA_RECOVER;
		break;
	case (KOOPA_STATE_WALKING):
		if (vx > 0) {
			aniId = ID_ANI_RED_KOOPA_WALKING_RIGHT;
		}
		else {
			aniId = ID_ANI_RED_KOOPA_WALKING;
		}
		break;
	case (ENEMY_STATE_DIE):
		aniId = ID_ANI_RED_KOOPA_DEFEND_UD;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}