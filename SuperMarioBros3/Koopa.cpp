#include "Koopa.h"
#include "Enemy.h"
#include "Mario.h"
#include "PlayScene.h"
#include "Game.h"
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
	if (state == KOOPA_STATE_DEFEND || state == KOOPA_STATE_DEFEND_SLIDING || state == KOOPA_STATE_RECOVER || state == ENEMY_STATE_DIE)
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
	if (dynamic_cast<CEnemy*>(e->obj) && state != KOOPA_STATE_DEFEND_SLIDING && !isBeingHold) return;

	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0.0f;
		if (e->ny < 0)
		{
			isOnPlatform = true;
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

	if (isBeingHold) {
		this->TakeKoopaDamage(x - e->nx);	
	}
	else {
		CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);
		if (koopa) {
			if (koopa->GetState() == KOOPA_STATE_DEFEND_SLIDING || koopa->isBeingHold)
				this->TakeKoopaDamage(koopa->x);
		}
	}	
	enemy->TakeKoopaDamage(x);
}

void CKoopa::TakeKoopaDamage(float xKoopa)
{
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

void CKoopa::HandleMarioRelease(float nx) {
	ay = KOOPA_GRAVITY;
	isBeingHold = false;
	if (state == KOOPA_STATE_DEFEND || state == KOOPA_STATE_RECOVER) {
		SetState(KOOPA_STATE_DEFEND_SLIDING);
		if (nx >= 0) vx = KOOPA_SLIDING_SPEED;
		else vx = -KOOPA_SLIDING_SPEED;
		DebugOut(L"Release DEFEND\n");
	}
	else {
		CPlayScene* scene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
		CMario* mario = scene ? dynamic_cast<CMario*>(scene->GetPlayer()) : nullptr;
		if (mario) {
			mario->TakeDamage();
			mario->SetHoldingObject(NULL);
		}
		DebugOut(L"Release\n");
	}
}
void CKoopa::TakeJumpDamage() {
	if (GetState() != KOOPA_STATE_DEFEND)
	{
		SetState(KOOPA_STATE_DEFEND);
	}
}

void CKoopa::OnCollisionByMario(LPCOLLISIONEVENT e)
{
	CMario* mario = dynamic_cast<CMario*>(e->src_obj);

	float mario_x, mario_y;
	mario->GetPosition(mario_x, mario_y);
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
			if (mario->IsReadyToHold()) {
				isBeingHold = true;
				ay = 0;
				mario->SetHoldingObject(this);
			}
			else {
				SetState(KOOPA_STATE_DEFEND_SLIDING);
				vx = -KOOPA_SLIDING_SPEED;
			}
		}
		else if (e->nx < 0) {
			if (mario->IsReadyToHold()) {
				isBeingHold = true;
				ay = 0;
				mario->SetHoldingObject(this);
			}
			else {
				SetState(KOOPA_STATE_DEFEND_SLIDING);
				vx = KOOPA_SLIDING_SPEED;
			}
		}
		else if (e->ny < 0) {
			SetState(KOOPA_STATE_DEFEND_SLIDING);
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
	if ((state == ENEMY_STATE_DIE) && (GetTickCount64() - die_start > KOOPA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}

	if ((state == KOOPA_STATE_DEFEND) && (GetTickCount64() - defend_start > KOOPA_DEFEND_TIMEOUT))
	{
		SetState(KOOPA_STATE_RECOVER);
		return;
	}
	if (state == KOOPA_STATE_RECOVER)
	{
		vx = -vx;
		if (GetTickCount64() - recover_start > KOOPA_RECOVER_TIMEOUT) {
			SetState(KOOPA_STATE_WALKING);
			if (isBeingHold) {
				HandleMarioRelease(0);
				DebugOut(L"Recovered!\n");
			}
			return;
		}
	}

	CEnemy::Update(dt, coObjects);
}

void CKoopa::ResetPos() {
	if (state != ENEMY_STATE_DIE) {
		CEnemy::ResetPos();
		SetState(KOOPA_STATE_WALKING);
	}
}

void CKoopa::Render()
{
	int aniId = ID_ANI_KOOPA_WALKING;
	switch (state) {
	case (KOOPA_STATE_DEFEND):
		if (isUpsideDown)
			aniId = ID_ANI_KOOPA_DEFEND_UD;
		else aniId = ID_ANI_KOOPA_DEFEND;
		break;
	case (KOOPA_STATE_DEFEND_SLIDING):
		if (isUpsideDown)
			aniId = ID_ANI_KOOPA_SLIDE_UD;
		else aniId = ID_ANI_KOOPA_SLIDE;
		break;
	case (KOOPA_STATE_RECOVER):
		if (isUpsideDown)
			aniId = ID_ANI_KOOPA_RECOVER_UD;
		else aniId = ID_ANI_KOOPA_RECOVER;
		break;
	case (KOOPA_STATE_WALKING):
		if (vx > 0) {
			aniId = ID_ANI_KOOPA_WALKING_RIGHT;
		}
		break;
	case (ENEMY_STATE_DIE):
		aniId = ID_ANI_KOOPA_DEFEND_UD;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CKoopa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPA_STATE_DEFEND:
		defend_start = GetTickCount64();
		vx = 0;
		vy = 0;
		break;
	case KOOPA_STATE_RECOVER:
		recover_start = GetTickCount64();
		vx = -KOOPA_SHAKE_SPEED;
		break;
	case KOOPA_STATE_WALKING:
		isUpsideDown = false;
		y -= (float)(KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_DEFEND) / 2;
		vx = -KOOPA_WALKING_SPEED;
		ay = KOOPA_GRAVITY;
		break;
	case ENEMY_STATE_DIE:
		die_start = GetTickCount64();
		ay = KOOPA_GRAVITY;
		break;
	case KOOPA_STATE_DEFEND_SLIDING:
		ay = KOOPA_GRAVITY;
		break;
	}
}