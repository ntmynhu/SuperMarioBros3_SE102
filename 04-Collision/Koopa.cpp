#include "Koopa.h"
#include "Enemy.h"
#include "Mario.h"
#include "Brick.h"
#include "Platform.h"
#include "debug.h"

CKoopa::CKoopa(float x, float y) :CEnemy(x, y)
{
	this->ay = KOOPA_GRAVITY;
	SetState(KOOPA_STATE_WALKING);
}

void CKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == KOOPA_STATE_DEFEND || state == KOOPA_STATE_DEFEND_SLIDING || state == KOOPA_STATE_RECOVER)
	{
		left = x - KOOPA_BBOX_WIDTH_DEFEND / 2;
		top = y - KOOPA_BBOX_HEIGHT_DEFEND / 2;
		right = left + KOOPA_BBOX_WIDTH_DEFEND;
		bottom = top + KOOPA_BBOX_HEIGHT_DEFEND;
	}
	else
	{
		left = x - KOOPA_BBOX_WIDTH / 2;
		top = y - KOOPA_BBOX_HEIGHT / 2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + KOOPA_BBOX_HEIGHT;
	}
}

void CKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CMario*>(e->obj)) return;
	if (dynamic_cast<CEnemy*>(e->obj) && state != KOOPA_STATE_DEFEND_SLIDING) return;
	
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0.0f;
		if (e->ny < 0)
		{
			isOnPlatform = true;
			if (state != KOOPA_STATE_DEFEND_SLIDING) {
				if (dynamic_cast<CPlatform*>(e->obj)) {
					OnCollisionWithGround(e);
					
				}
			}
			
			
		}
	}
	else if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = -vx;
	}

	if (dynamic_cast<CEnemy*>(e->obj)) {
		OnCollisionWithEnemy(e);
	}
	
}

void CKoopa::OnCollisionWithEnemy(LPCOLLISIONEVENT e)
{
	CEnemy* enemy = dynamic_cast<CEnemy*>(e->obj);
	enemy->TakeKoopaDamage();
}

void CKoopa::OnCollisionWithGround(LPCOLLISIONEVENT e)
{
	CGameObject* ground = dynamic_cast<CGameObject*>(e->obj);
	float t, l, r, b;
	ground->GetBoundingBox(l, t, r, b);
	left_lim = l + KOOPA_BBOX_WIDTH/2;
	right_lim = r - KOOPA_BBOX_WIDTH/2;
}
void CKoopa::TakeJumpDamage() {
	if (GetState() != KOOPA_STATE_DEFEND)
	{
		SetState(KOOPA_STATE_DEFEND);
	}
}

void CKoopa::OnCollisionByMario(LPCOLLISIONEVENT e)
{
	//Mario collide from top
	if (state != KOOPA_STATE_DEFEND && state != KOOPA_STATE_RECOVER)
	{
		if (e->ny < 0) {
			TakeJumpDamage();
		}
	}
	else {
		//Mario collide from right
		if (e->nx > 0) {
			SetState(KOOPA_STATE_DEFEND_SLIDING);
			vx = -KOOPA_SLIDING_SPEED;
		}
		else if (e->nx < 0) {
			SetState(KOOPA_STATE_DEFEND_SLIDING);
			vx = KOOPA_SLIDING_SPEED;
		}
		else if (e->ny < 0) {
			SetState(KOOPA_STATE_DEFEND_SLIDING);
			CMario* mario = dynamic_cast<CMario*>(e->src_obj);

			float mario_x, mario_y;
			mario->GetPosition(mario_x, mario_y);
			//Mario collide from right
			if (x <= mario_x) {
				vx = -KOOPA_SLIDING_SPEED;
			}
			else
			{
				vx = KOOPA_SLIDING_SPEED;
			}
		}
	}

	
}


void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	
	if (this->isOnPlatform && state == KOOPA_STATE_WALKING) {
		if (this->x <= left_lim) {
			this->x = left_lim;
			this->vx = -this->vx;
		}
		else if (this->x >= right_lim)
		{
			this->x = right_lim;
			this->vx = -this->vx;
		}
	}
	
	if ((state == KOOPA_STATE_DEFEND) && (GetTickCount64() - die_start > KOOPA_DEFEND_TIMEOUT))
	{
		SetState(KOOPA_STATE_RECOVER);
		return;
	}
	if ((state == KOOPA_STATE_RECOVER))
	{
		vx = -vx;
		if (GetTickCount64() - recover_start > KOOPA_RECOVER_TIMEOUT) {
			SetState(KOOPA_STATE_WALKING);
			return;
		}
	}
	CEnemy::Update(dt, coObjects);
}


void CKoopa::Render()
{
	int aniId = ID_ANI_KOOPA_WALKING;
	switch (state) {
	case (KOOPA_STATE_DEFEND):
		aniId = ID_ANI_KOOPA_DEFEND;
		break;
	case (KOOPA_STATE_DEFEND_SLIDING):
		aniId = ID_ANI_KOOPA_SLIDE;
		break;
	case (KOOPA_STATE_RECOVER):
		aniId = ID_ANI_KOOPA_RECOVER;
		break;
	case (KOOPA_STATE_WALKING):
		if (vx > 0) {
			aniId = ID_ANI_KOOPA_WALKING_RIGHT;
		}
		break;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CKoopa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPA_STATE_DEFEND:
		die_start = GetTickCount64();
		vx = 0;
		vy = 0;
		break;
	case KOOPA_STATE_RECOVER:
		recover_start = GetTickCount64();
		vx = -KOOPA_SHAKE_SPEED;
		break;
	case KOOPA_STATE_WALKING:
		y -= (float)(KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_DEFEND) / 2;
		vx = -KOOPA_WALKING_SPEED;
		break;
	}
}