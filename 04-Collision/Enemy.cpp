#include "Enemy.h"

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
	vy += ay * dt;
	vx += ax * dt;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
