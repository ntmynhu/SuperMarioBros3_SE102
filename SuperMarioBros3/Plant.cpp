#include "Plant.h"
void CPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	if (mario == NULL) {
		SetMario();
		return;
	}

	CheckAbleToUp();

	if (state == PLANT_STATE_DIE) {
		if ((GetTickCount64() - die_start > PLANT_DIE_TIME_OUT))
		{
			isDeleted = true;
			return;
		}
	}

	y += vy * dt;
	CGameObject::Update(dt, coObjects);
}

void CPlant::SetState(int state) {
	CGameObject::SetState(state);
	switch (state)
	{
	case PLANT_STATE_UP:
		up_start = GetTickCount64();
		vy = 0;
		break;
	case PLANT_STATE_HIDE:
		down_start = GetTickCount64();
		vy = 0;
		break;
	case PLANT_STATE_DIE:
		die_start = GetTickCount64();
		vy = 0;
		break;
	}
}