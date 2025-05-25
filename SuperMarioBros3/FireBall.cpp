#include "FireBall.h"
#include "Game.h"
void CFireBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	x += abs(vx) * dt * xDir;
	y += abs(vy) * dt * yDir;
	
	CGameObject::Update(dt, coObjects);
}

void CFireBall::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x - FIRE_BALL_BBOX_WIDTH / 2;
	top = y - FIRE_BALL_BBOX_HEIGHT / 2;
	right = left + FIRE_BALL_BBOX_WIDTH;
	bottom = top + FIRE_BALL_BBOX_HEIGHT;
}

void CFireBall::Render() {
	int aniId = ID_ANI_FIRE_BALL;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}