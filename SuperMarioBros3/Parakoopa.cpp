#include "Parakoopa.h"
void CParakoopa::TakeJumpDamage() {
	if (state == PARA_KOOPA_STATE_HASWING) {
		SetState(KOOPA_STATE_WALKING);
		return;
	}
	CKoopa::TakeJumpDamage();
}

void CParakoopa::ResetPos() {
	if (state != ENEMY_STATE_DIE) {
		CEnemy::ResetPos();
		SetState(PARA_KOOPA_STATE_HASWING);
	}
}


void CParakoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (HasWing()) {
		if (isOnPlatform) {
			vy = -PARA_KOOPA_FLY_SPEED_Y;
		}
	}

	CKoopa::Update(dt, coObjects);
}
void CParakoopa::Render()
{
	int aniId = ID_ANI_PARA_KOOPA_FLY;
	switch (state) {
	case (PARA_KOOPA_STATE_HASWING):
		if (vx > 0) {
			aniId = ID_ANI_PARA_KOOPA_FLY_RIGHT;
		}
		break;
	case (KOOPA_STATE_DEFEND):
		aniId = ID_ANI_KOOPA_DEFEND;
		break;
	case (KOOPA_STATE_DEFEND_SLIDING):
		aniId = ID_ANI_KOOPA_SLIDE;
		break;
	case (KOOPA_STATE_RECOVER):
		aniId = ID_ANI_KOOPA_RECOVER;
		break;
	case (KOOPA_STATE_WALKING):
		if (vx > 0) {
			aniId = ID_ANI_KOOPA_WALKING_RIGHT;
		}
		else {
			aniId = ID_ANI_KOOPA_WALKING;
		}
		break;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}