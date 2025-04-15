#include "Enemy.h"
#include "PlayScene.h"
#include "Mario.h"
CEnemy::CEnemy(float x, float y) :CGameObject(x, y)
{
	this->die_start = -1;
	this->ax = 0;
	this->ay = 0;
	this->isOnPlatform = false;
}

void CEnemy::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
	isOnPlatform = false;
};

void CEnemy::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (mario == NULL) {
		SetMario();
	}
	vy += ay * dt;
	vx += ax * dt;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CEnemy::ResetPos() {
	CGameObject::ResetPos();
	this->x = init_x;
	this->y = init_y;
	vx = abs(vx) * CheckXDirection();
}

void CEnemy::SetMario() {
	CPlayScene* scene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
	if (scene) {
		CMario* mario = dynamic_cast<CMario*>(scene->GetPlayer());
		if (mario) {
			this->mario = mario;
		}
	}
}
int CEnemy::CheckXDirection() {
	if (mario == NULL) {
		SetMario();
	}
	if (mario != NULL) {
		float mx, my;
		mario->GetPosition(mx, my);

		float dx = mx - x;

		return (dx < 0) ? -1 : 1;
	}
	return 1;
}
