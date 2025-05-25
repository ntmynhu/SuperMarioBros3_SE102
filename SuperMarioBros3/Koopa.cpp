#include "Koopa.h"
#include "Enemy.h"
#include "Mario.h"
#include "PlayScene.h"
#include "Game.h"
#include "Plant.h"
#include "Block.h"
#include "debug.h"
#include "GameData.h"

CKoopa::CKoopa(float x, float y) :CEnemy(x, y)
{
	this->shakeVx = KOOPA_SHAKE_SPEED;
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
	if (dynamic_cast<CEnemy*>(e->obj) && state == KOOPA_STATE_DEFEND) return;
	if (!isBeingHold) {
		if (e->ny != 0 && e->obj->IsBlocking())
		{
			vy = 0.0f;
			if (e->ny < 0)
			{
				if (state == KOOPA_STATE_DEFEND) {
					vx = 0;
				}
				isOnPlatform = true;
			}
		}
		else if (e->nx != 0 && e->obj->IsBlocking())
		{
			vx = -vx;
		}
	}

	if (dynamic_cast<CBlock*>(e->obj)) {
		OnCollisionWithBlock(e);
	}

	if (state == KOOPA_STATE_DEFEND_SLIDING || isBeingHold) {
		if (dynamic_cast<CEnemy*>(e->obj)) {
			OnCollisionWithEnemy(e);
		}
		if (dynamic_cast<CPlant*>(e->obj)) {
			OnCollisionWithPlant(e);
		}
		
	}
	else {
		if (dynamic_cast<CKoopa*>(e->obj)) {
			CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);
			if (koopa->GetState() != KOOPA_STATE_DEFEND_SLIDING && !koopa->isBeingHold)
			{
				float k_vx, k_vy;
				koopa->GetSpeed(k_vx, k_vy);
				koopa->SetSpeed(-k_vx, k_vy);
				vx = -vx;
			}
		}
	}
}

void CKoopa::HoldingUpdate(DWORD dt) {
	if (mario) {
		float m_x, m_y, m_vx, m_vy, m_ax, m_ay, m_nx, m_ox, m_oy;
		mario->GetPosition(m_x, m_y);
		mario->GetPhysics(m_vx, m_vy, m_ax, m_ay, m_nx);
		mario->GetHoldOffset(m_ox, m_oy);
		// As Mario will be updated first, predict next Mario pos
		if (m_vy == 0) m_ay = 0;
		m_vy += m_ay * dt;
		m_vx += m_ax * dt;
		/*if (m_nx == 1 && m_ax < 0 && m_vx < 0) m_vx = 0;
		if (m_nx == -1 && m_ax > 0 && m_vx > 0) m_vx = 0;*/

		m_x += m_vx * dt;
		m_y += m_ay * dt;

		
		float targetX = (m_nx > 0) ? (m_x + m_ox) : (m_x - m_ox);
		if (m_nx == 0) targetX = m_x;
		float targetY = m_y - m_oy;

		float dx = targetX - x;
		float dy = targetY - y;
		if (dt != 0)
			SetSpeed(dx / dt, dy / dt);

		if (state == KOOPA_STATE_RECOVER)
		{
			vx += shakeVx;
		}
		x += vx * dt;
		y += vy * dt;
	}
}

void CKoopa::OnCollisionWithBlock(LPCOLLISIONEVENT e)
{
	CBlock* block = dynamic_cast<CBlock*>(e->obj);

	if (state == KOOPA_STATE_DEFEND_SLIDING && e->nx != 0) {
		block->TriggerAction();
	}
	else if (state != KOOPA_STATE_DEFEND_SLIDING && e->ny < 0) {
		if (block->IsBouncing()) {
			float b_x, b_y;
			block->GetPosition(b_x, b_y);
			TakeBlockBounceDamage(b_x);
		}
	}
}

void CKoopa::OnCollisionWithPlant(LPCOLLISIONEVENT e)
{
	CPlant* plant = dynamic_cast<CPlant*>(e->obj);

	if (isBeingHold) {
		this->TakeKoopaDamage(x - e->nx);
	}
	plant->TakeKoopaDamage(x);
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

		CGameData* game = CGameData::GetInstance();
		game->AddScore(100, x, y, this);

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
		mario->TriggerKick();
		DebugOut(L"Release DEFEND\n");
	}
	else {
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

void CKoopa::TakeTailAttackDamage(float xMario)
{
	isUpsideDown = true;
	if (xMario > x) {
		vx = -KOOPA_TAIL_HIT_VX;
	}
	else {
		vx = KOOPA_TAIL_HIT_VX;
	}
	vy = -KOOPA_TAIL_HIT_VY;
	SetState(KOOPA_STATE_DEFEND);
}

void CKoopa::TakeBlockBounceDamage(float xBlock)
{
	isUpsideDown = true;
	if (xBlock > x) {
		vx = -KOOPA_BLOCK_HIT_VX;
	}
	else {
		vx = KOOPA_BLOCK_HIT_VX;
	}
	vy = -KOOPA_BLOCK_HIT_VY;
	SetState(KOOPA_STATE_DEFEND);
}


void CKoopa::OnCollisionByMario(LPCOLLISIONEVENT e)
{
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
		else if (e->ny > 0) {
			if (mario->IsReadyToHold()) {
				isBeingHold = true;
				ay = 0;
				mario->SetHoldingObject(this);
			}
			else {
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


}

void CKoopa::OnNoCollision(DWORD dt) {
	if (isBeingHold) return;
	
	CEnemy::OnNoCollision(dt);
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
		shakeVx = -shakeVx;
		if (!isBeingHold) {
			vx = 0 + shakeVx;
		}
		
		if (GetTickCount64() - recover_start > KOOPA_RECOVER_TIMEOUT) {
			SetState(KOOPA_STATE_WALKING);
			if (isBeingHold) {
				HandleMarioRelease(0);
				DebugOut(L"Recovered!\n");
			}
			return;
		}
	}

	if (isBeingHold)
		HoldingUpdate(dt);

	CEnemy::Update(dt, coObjects);

	
}

void CKoopa::ResetPos() {
	if (state != ENEMY_STATE_DIE) {
		SetState(KOOPA_STATE_WALKING);
		isBeingHold = false;
		isUpsideDown = false;
		CEnemy::ResetPos();
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
		isBeingHold = false;
		ay = KOOPA_GRAVITY;
		break;
	case KOOPA_STATE_DEFEND_SLIDING:
		ay = KOOPA_GRAVITY;
		break;
	}
}