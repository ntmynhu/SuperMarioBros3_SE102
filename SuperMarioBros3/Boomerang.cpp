#include "Boomerang.h"
#include "debug.h"
void CBoomerang::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x - BOOMERANG_BBOX_WIDTH / 2;
	top = y - BOOMERANG_BBOX_HEIGHT / 2;
	right = left + BOOMERANG_BBOX_WIDTH;
	bottom = top + BOOMERANG_BBOX_HEIGHT;
}

void CBoomerang::Throw(float x, float y, float xDir) {
	this->startX = x;
	this->startY = y;
	this->x = x;
	this->y = y;
	this->xDir = xDir;
	this->vx = BOOMERANG_VX * xDir;
	this->vy = -BOOMERANG_VY;
	returning = false;
	Activate();
}

void CBoomerang::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
    const float GRAVITY = 0.000095f;
    const float RETURN_ACCEL = 0.005f;  // controls how fast vx eases

    x += vx * dt;
    y += vy * dt;
    

    float dxFromStart = x - startX;

    if (!returning) {
        if ((xDir > 0 && dxFromStart >= BOOMERANG_MAX_DISTANCE) ||
            (xDir < 0 && dxFromStart <= -BOOMERANG_MAX_DISTANCE)) {
            returning = true;
        }
    }
    else {
        float targetVx = -xDir * BOOMERANG_VX;
        float deltaVx = targetVx - vx;

        if (abs(deltaVx) < 0.0001f)
            vx = targetVx;
        else
            vx += deltaVx * RETURN_ACCEL * dt;
    }

    vy += GRAVITY * dt;

    if (y >= startY) {
        y = startY;
        vy = 0;
    }

    CGameObject::Update(dt, coObjects);
    
}





void CBoomerang::Render() {
	int aniId = ID_ANI_BOOMERANG;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}