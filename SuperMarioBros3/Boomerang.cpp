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
    
	x += vx * dt;
	y += vy * dt;

    float dx = x - startX;

    // Check if boomerang should return
    if (!returning) {
        if ((xDir > 0 && dx >= BOOMERANG_MAX_DISTANCE) ||
            (xDir < 0 && dx <= -BOOMERANG_MAX_DISTANCE)) {
            returning = true;
            vx = -vx;
        }
    }

	vy += 0.00008f * dt;
    if (y >= startY) vy = 0;
    
    CGameObject::Update(dt, coObjects);
}




void CBoomerang::Render() {
	RenderBoundingBox();
}