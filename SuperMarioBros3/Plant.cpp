#include "Plant.h"
void CPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

	if (state == PLANT_STATE_DIE) {
		if ((GetTickCount64() - die_start > PLANT_DIE_TIME_OUT))
		{
			isDeleted = true;
			return;
		}
	}

	if (state == PLANT_STATE_DOWN && isAbleToUp) {
		if (GetTickCount64() - down_start >= PLANT_DOWN_TIME_OUT) {
			this->vy = -PLANT_VY;
			SetState(PLANT_STATE_MOVING);
		}
	}
	else if (state == PLANT_STATE_UP) {
		if (GetTickCount64() - up_start >= PLANT_UP_TIME_OUT) {
			this->vy = PLANT_VY;
			SetState(PLANT_STATE_MOVING);
		}
	}
	else if (state == PLANT_STATE_MOVING) {
		if (y <= minY) {
			y = minY;
			SetState(PLANT_STATE_UP);
		}
		else if (y >= maxY) {
			y = maxY;
			SetState(PLANT_STATE_DOWN);
		}
	}
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
	case PLANT_STATE_DOWN:
		down_start = GetTickCount64();
		vy = 0;
		break;
	case PLANT_STATE_DIE:
		die_start = GetTickCount64();
		vy = 0;
		break;
	}
}