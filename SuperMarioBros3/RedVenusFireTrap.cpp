#include "RedVenusFireTrap.h"

void CRedVenusFireTrap::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x - VENUS_BBOX_WIDTH / 2;
	top = y - RED_VENUS_BBOX_HEIGHT / 2;
	right = left + VENUS_BBOX_WIDTH;
	bottom = top + RED_VENUS_BBOX_HEIGHT;
}

void CRedVenusFireTrap::Render() {

	int aniId = ID_ANI_RED_VENUS_DOWN_LEFT;
	switch (state) {
	case PLANT_STATE_MOVING:
		if (isUp) {
			if (isLeft)
				aniId = ID_ANI_RED_VENUS_MOVING_UP_LEFT;
			else
				aniId = ID_ANI_RED_VENUS_MOVING_UP_RIGHT;
		}
		else
		{
			if (isLeft)
				aniId = ID_ANI_RED_VENUS_MOVING_DOWN_LEFT;
			else
				aniId = ID_ANI_RED_VENUS_MOVING_DOWN_RIGHT;
		}
		break;
	case PLANT_STATE_UP:
		if (isUp) {
			if (isLeft)
				aniId = ID_ANI_RED_VENUS_UP_LEFT;
			else
				aniId = ID_ANI_RED_VENUS_UP_RIGHT;
		}
		else
		{
			if (isLeft)
				aniId = ID_ANI_RED_VENUS_DOWN_LEFT;
			else
				aniId = ID_ANI_RED_VENUS_DOWN_RIGHT;
		}
		break;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}