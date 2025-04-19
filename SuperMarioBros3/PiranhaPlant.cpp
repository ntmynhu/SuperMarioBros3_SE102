#include "PiranhaPlant.h"
#include "debug.h"
void CPiranhaPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	CPlant::Update(dt, coObjects);
	if (state == PLANT_STATE_HIDE && isAbleToUp != 0) {
		if (GetTickCount64() - down_start >= PIRANHA_DOWN_TIME_OUT) {
			this->vy = -PLANT_VY;
			SetState(PLANT_STATE_MOVING);
		}
	}
	else if (state == PLANT_STATE_UP) {
		if (GetTickCount64() - up_start >= PIRANHA_UP_TIME_OUT) {
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
			SetState(PLANT_STATE_HIDE);
		}
	}

	//DebugOutTitle(L"isAbleToUp: %d", isAbleToUp);
	
}

void CPiranhaPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	if (state == PLANT_STATE_DIE) {
		left = x - PLANT_DIE_BBOX_WIDTH / 2;
		top = y - PLANT_DIE_BBOX_HEIGHT / 2;
		right = left + PLANT_DIE_BBOX_WIDTH;
		bottom = top + PLANT_DIE_BBOX_HEIGHT;
	}
	else {
		left = x - PIRANHA_BBOX_WIDTH / 2;
		top = y - PIRANHA_BBOX_HEIGHT / 2;
		right = left + PIRANHA_BBOX_WIDTH;
		bottom = top + PIRANHA_BBOX_HEIGHT;
	}
}

void CPiranhaPlant::Render() {
	int aniId = ID_ANI_PIRANHA;
	switch (state) {
	case PLANT_STATE_DIE:
		aniId = ID_ANI_PLANT_DIE;
		break;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}