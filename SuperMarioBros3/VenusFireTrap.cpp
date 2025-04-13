#include "VenusFireTrap.h"
#include "FireBall.h"
#include "debug.h"
void CVenusFireTrap::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	float fireDegree = GetFireDegree();
	if (state == PLANT_STATE_HIDE && isAbleToUp != 0) {
		if (GetTickCount64() - down_start >= VENUS_DOWN_TIME_OUT) {
			this->vy = -PLANT_VY;
			SetState(PLANT_STATE_MOVING);
		}
	}
	else if (state == PLANT_STATE_UP) {
		if (GetTickCount64() - up_start >= VENUS_UP_TIME_OUT) {
			this->vy = PLANT_VY;
			SetState(PLANT_STATE_MOVING);
		}
		if (GetTickCount64() - up_start >= VENUS_FIRE_TIME_OUT) {
			if (fireDegree > 0 && isFire == false) {
				if (fireball && fireball->GetState()==FIRE_BALL_STATE_IDLE) {
					fireball->SetPosition(x, y - flowerOffsetY);
					fireball->SetDir(fireDegree);
					fireball->SetState(FIRE_BALL_STATE_FLY);
					isFire = true;
				}
			}
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
	CPlant::Update(dt, coObjects);
}

void CVenusFireTrap::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x - VENUS_BBOX_WIDTH / 2;
	top = y - VENUS_BBOX_HEIGHT / 2;
	right = left + VENUS_BBOX_WIDTH;
	bottom = top + VENUS_BBOX_HEIGHT;
}

float CVenusFireTrap::GetFireDegree() {
	float flowerY = this->y - flowerOffsetY;
	float degree = 0;
	float angles[] = { 15, 45, 135, 165, 195, 225, 315, 345 };
	int numAngles = sizeof(angles) / sizeof(angles[0]);
	

	if (mario != NULL) {
		float mx, my;
		mario->GetPosition(mx, my);

		float dx = mx - x;
		float dy = flowerY - my;

		degree = atan2(dy, dx) * (180.0f / 3.14159265f);

		// Normalize to [0, 360)
		if (degree < 0) {
			degree += 360.0f;
		}

		int selected_degree = 0;
		float minDiff = 600;
		for (int i = 0; i < numAngles; i++) {
			float diff = abs(degree - angles[i]);
			// If the difference is smaller, update the closest angle
			if (diff < minDiff) {
				minDiff = diff;
				selected_degree = i;
			}
		}
		degree = angles[selected_degree];

		isLeft = (dx < 0);
		isUp = (dy > 0);

	}

	return degree;
}
void CVenusFireTrap::Render() {
	
	int aniId = ID_ANI_VENUS_DOWN_LEFT;
	switch (state) {
	case PLANT_STATE_MOVING:
		if (isUp) {
			if (isLeft)
				aniId = ID_ANI_VENUS_MOVING_UP_LEFT;
			else
				aniId = ID_ANI_VENUS_MOVING_UP_RIGHT;
		}
		else
		{
			if (isLeft)
				aniId = ID_ANI_VENUS_MOVING_DOWN_LEFT;
			else
				aniId = ID_ANI_VENUS_MOVING_DOWN_RIGHT;
		}
		break;
	case PLANT_STATE_UP:
		if (isUp) {
			if (isLeft)
				aniId = ID_ANI_VENUS_UP_LEFT;
			else
				aniId = ID_ANI_VENUS_UP_RIGHT;
		}
		else
		{
			if (isLeft)
				aniId = ID_ANI_VENUS_DOWN_LEFT;
			else
				aniId = ID_ANI_VENUS_DOWN_RIGHT;
		}
		break;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CVenusFireTrap::SetState(int state) {
	CPlant::SetState(state);
	if (state == PLANT_STATE_MOVING) {
		isFire = false;
	}
}