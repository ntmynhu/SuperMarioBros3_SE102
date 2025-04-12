#include "Goomba.h"
#include "Mario.h"
#include "Enemy.h"
#include "debug.h"
CGoomba::CGoomba(float x, float y) :CEnemy(x, y)
{
	this->ay = GOOMBA_GRAVITY;
	SetState(GOOMBA_STATE_WALKING);
}

void CGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == ENEMY_STATE_DIE && !isUpsideDown)
	{
		left = x - GOOMBA_BBOX_WIDTH / 2;
		top = y - GOOMBA_BBOX_HEIGHT_DIE / 2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - GOOMBA_BBOX_WIDTH / 2;
		top = y - GOOMBA_BBOX_HEIGHT / 2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT;
	}
}

void CGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CMario*>(e->obj)) return;
	if (!e->obj->IsBlocking()) return;

	if (dynamic_cast<CEnemy*>(e->obj)) return;


	if (e->ny != 0)
	{
		vy = 0.0f;
		if (e->ny < 0)
		{
			isOnPlatform = true;
		}
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}


}

void CGoomba::OnCollisionByMario(LPCOLLISIONEVENT e)
{
	if (e->ny < 0) {
		TakeJumpDamage();
	}
}
void CGoomba::TakeJumpDamage() {
	if (GetState() != ENEMY_STATE_DIE)
	{
		SetState(ENEMY_STATE_DIE);
	}

}

void CGoomba::TakeKoopaDamage(float xKoopa) {
	if (GetState() != ENEMY_STATE_DIE)
	{
		isUpsideDown = true;
		if (xKoopa > x) {
			vx = -ENEMY_DIE_UPSIDE_DOWN_VX;
		}
		else {
			vx = ENEMY_DIE_UPSIDE_DOWN_VX;
		}
		vy = -ENEMY_DIE_UPSIDE_DOWN_VY;
		SetState(ENEMY_STATE_DIE);
	}

}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{


	if (state == ENEMY_STATE_DIE) {
		if (isUpsideDown) {
			if ((GetTickCount64() - die_start > GOOMBA_DIE_UD_TIMEOUT))
			{
				isDeleted = true;
				return;
			}
		}
		else {
			if ((GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT))
			{
				isDeleted = true;
				return;
			}
		}
	}

	CEnemy::Update(dt, coObjects);
}


void CGoomba::Render()
{
	int aniId = ID_ANI_GOOMBA_WALKING;
	if (state == ENEMY_STATE_DIE)
	{
		if (isUpsideDown)
			aniId = ID_ANI_GOOMBA_DIE_UPSIDE_DOWN;
		else aniId = ID_ANI_GOOMBA_DIE;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ENEMY_STATE_DIE:
		die_start = GetTickCount64();
		if (!isUpsideDown) {
			y += (GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE) / 2;
			vx = 0;
			vy = 0;
			ay = 0;
		}
		break;
	case GOOMBA_STATE_WALKING:
		vx = -GOOMBA_WALKING_SPEED;
		ay = GOOMBA_GRAVITY;
		break;
	}
}