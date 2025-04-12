#include "PiranhaPlant.h"
#include "debug.h"
void CPiranhaPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	if (state == PLANT_STATE_DOWN && isAbleToUp != 0) {
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
			SetState(PLANT_STATE_DOWN);
		}
	}

	//DebugOutTitle(L"isAbleToUp: %d", isAbleToUp);
	CPlant::Update(dt, coObjects);
}

void CPiranhaPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x - PIRANHA_BBOX_WIDTH / 2;
	top = y - PIRANHA_BBOX_HEIGHT / 2;
	right = left + PIRANHA_BBOX_WIDTH;
	bottom = top + PIRANHA_BBOX_HEIGHT;
}

void CPiranhaPlant::Render() {
	int aniId = ID_ANI_PIRANHA;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}