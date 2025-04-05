#include "Parakoopa.h"
#include "Debug.h"
void CParakoopa::TakeJumpDamage() {
	if (state == PARA_KOOPA_STATE_HASWING) {
		SetState(KOOPA_STATE_WALKING);
		return;
	}
	CKoopa::TakeJumpDamage();
}

void CParakoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	DebugOutTitle(L"Left lim %f, Right lim %f, x %f, y %f", left_lim, right_lim, x, y);
	if (HasWing()) {
		if (isOnPlatform) {
			vy = -PARA_KOOPA_FLY_SPEED_Y;
		}
	}

	CKoopa::Update(dt, coObjects);
}