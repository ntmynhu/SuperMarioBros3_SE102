#include "BoomerangBros.h"
#include "Mario.h"
#include "Game.h"
#include "GameData.h"
#include "debug.h"
#include "GameObject.h"
void CBoomerangBros::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	if (state == BOOMERANG_BRO_STATE_PREPARE_THROWING)
	{
		left = x - BOOMERANG_BRO_BBOX_WIDTH / 2;
		top = y - BOOMERANG_BRO_PREPARE_BBOX_HEIGHT / 2;
		right = left + BOOMERANG_BRO_BBOX_WIDTH;
		bottom = top + BOOMERANG_BRO_PREPARE_BBOX_HEIGHT;
	}
	else
	{
		left = x - BOOMERANG_BRO_BBOX_WIDTH / 2;
		top = y - BOOMERANG_BRO_BBOX_HEIGHT / 2;
		right = left + BOOMERANG_BRO_BBOX_WIDTH;
		bottom = top + BOOMERANG_BRO_BBOX_HEIGHT;
	}
}
void CBoomerangBros::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	if (state == ENEMY_STATE_DIE) {
		if ((GetTickCount64() - die_start > BOOMERANG_BRO_DIE_TIMEOUT))
		{
			isDeleted = true;
			return;
		}
		CEnemy::Update(dt, coObjects);
		return;
	}

	if (x <= min_x)
	{
		if (switch_start == -1)
		{
			vx = 0;
			switch_start = GetTickCount64();
		}
		if (GetTickCount64() - switch_start > BOOMERANG_BRO_TURN_DELAY) {
			vx = BOOMERANG_BRO_VX;
			switch_start = -1;
		}

	}
	else if (x >= max_x) {
		if (switch_start == -1)
		{
			vx = 0;
			switch_start = GetTickCount64();
		}
		if (GetTickCount64() - switch_start > BOOMERANG_BRO_TURN_DELAY) {
			vx = -BOOMERANG_BRO_VX;
			switch_start = -1;
		}
	}

	if (GetTickCount64() - jump_start > BOOMERANG_BRO_JUMP_TIMEOUT) {
		jump_start = GetTickCount64();
		MakeJump();
	}
	if (state == BOOMERANG_BRO_STATE_WALKING && GetTickCount64() - throw_start > throw_timeout) {
		if (Throwable() != 0) {
			SetState(BOOMERANG_BRO_STATE_PREPARE_THROWING);
			prepare_start = GetTickCount64();
		}
	}
	if (state == BOOMERANG_BRO_STATE_PREPARE_THROWING && GetTickCount64() - prepare_start > BOOMERANG_BRO_PREPARE_TIMEOUT) {
		switch (Throwable())
		{
		case 1:
			SetState(BOOMERANG_BRO_STATE_WALKING);
			MakeThrow1();
			break;
		case 2:
			SetState(BOOMERANG_BRO_STATE_WALKING);
			if (throw_timeout == BOOMERANG_BRO_BOOMERANG_DELAY)
				MakeThrow1();
			else
				MakeThrow2();
			break;
		}
	}

	FaceMario();
	
	//DebugOutTitle(L"vy %f y %f", vy, y);
	CEnemy::Update(dt, coObjects);
}

void CBoomerangBros::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (this->state == ENEMY_STATE_DIE) return;
	if (dynamic_cast<CBoomerang*> (e->obj))
		OnCollisionWithBoomerang(e);
	if (dynamic_cast<CMario*>(e->obj)) return;
	if (dynamic_cast<CEnemy*>(e->obj)) return;
	if (!e->obj->IsBlocking()) return;

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
void CBoomerangBros::OnCollisionWithBoomerang(LPCOLLISIONEVENT e) {
	if (e->obj == boomerang1 || e->obj == boomerang2) {
		e->obj->Deactivate();
	}
}
void CBoomerangBros::Render() {
	int aniId = ID_ANI_BOOMERANG_BRO_WALK_LEFT;
	switch (state) {
	case (BOOMERANG_BRO_STATE_WALKING):
		if (nx < 0)
			aniId = ID_ANI_BOOMERANG_BRO_WALK_LEFT;
		else aniId = ID_ANI_BOOMERANG_BRO_WALK_RIGHT;
		break;
	case (BOOMERANG_BRO_STATE_PREPARE_THROWING):
		if (nx < 0)
			aniId = ID_ANI_BOOMERANG_BRO_PREPARE_LEFT;
		else aniId = ID_ANI_BOOMERANG_BRO_PREPARE_RIGHT;
		break;

	case (ENEMY_STATE_DIE):
		if (nx < 0)
			aniId = ID_ANI_BOOMERANG_BRO_DIE_LEFT;
		else aniId = ID_ANI_BOOMERANG_BRO_DIE_RIGHT;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}

void CBoomerangBros::FaceMario() {
	if (mario != NULL) {
		float mx, my;
		mario->GetPosition(mx, my);

		float dx = mx - x;

		nx = (dx < 0) ? -1 : 1;
	}
}

void CBoomerangBros::MakeJump() {
	uniform_real_distribution<> dis(-1, 1);
	double random_value = dis(gen);
	vy = random_value < 0 ? 0.0f : -BOOMERANG_BRO_VY;

	if (random_value > 0) 
		DebugOut(L"[INFO] Jump\n");
}

int CBoomerangBros::Throwable() {
	if (mario != NULL) {
		float mx, my;
		mario->GetPosition(mx, my);

		float dx = mx - x;

		if (abs(dx) > BOOMERANG_BRO_ATTACK_RANGE) return 0;
		if (abs(dx) > BOOMERANG_BRO_2_BOOMERANG_RANGE) return 1;
		return 2;
	}
	return 0;
}
void CBoomerangBros::MakeThrow1() {
	DebugOut(L"[INFO] Boomerang Throw 1\n");
	boomerang1->Throw(x, y, nx);
	throw_timeout = BOOMERANG_BRO_THROW_TIMEOUT;
	throw_start = GetTickCount64();
}

void CBoomerangBros::MakeThrow2() {
	DebugOut(L"[INFO] Boomerang Throw 2\n");
	boomerang2->Throw(x, y, nx);
	throw_timeout = BOOMERANG_BRO_BOOMERANG_DELAY;
	throw_start = GetTickCount64();
}


void CBoomerangBros::SetState(int state) {
	int prevState = GetState();
	CGameObject::SetState(state);
	switch (state)
	{
	case ENEMY_STATE_DIE:
		die_start = GetTickCount64();
		vx = 0;
		vy = 0;
		break;
	case BOOMERANG_BRO_STATE_WALKING:
		if (prevState == BOOMERANG_BRO_STATE_PREPARE_THROWING)
			y += (BOOMERANG_BRO_PREPARE_BBOX_HEIGHT - BOOMERANG_BRO_BBOX_HEIGHT) / 2 + 2;
	case BOOMERANG_BRO_STATE_PREPARE_THROWING:
		y -= (BOOMERANG_BRO_PREPARE_BBOX_HEIGHT - BOOMERANG_BRO_BBOX_HEIGHT) / 2;
		break;
	}
}

void CBoomerangBros::OnCollisionByMario(LPCOLLISIONEVENT e) {
	if (e->ny < 0) {
		TakeJumpDamage();
	}
}
void CBoomerangBros::TakeJumpDamage() {
	if (GetState() != ENEMY_STATE_DIE)
	{
		CGameData* game = CGameData::GetInstance();
		game->AddScore(1000, x, y, this);
		SetState(ENEMY_STATE_DIE);
	}
}
void CBoomerangBros::TakeTailAttackDamage(float xMario) {
	if (GetState() != ENEMY_STATE_DIE)
	{
		SetState(ENEMY_STATE_DIE);

		if (xMario > x) {
			vx = -ENEMY_DIE_UPSIDE_DOWN_VX;
		}
		else {
			vx = ENEMY_DIE_UPSIDE_DOWN_VX;
		}

		CGameData* game = CGameData::GetInstance();
		game->AddScore(100, x, y, this);

		vy = -ENEMY_DIE_UPSIDE_DOWN_VY;
		
	}
}
void CBoomerangBros::TakeKoopaDamage(float xKoopa) {
	if (GetState() != ENEMY_STATE_DIE)
	{
		SetState(ENEMY_STATE_DIE);

		if (xKoopa > x) {
			vx = -ENEMY_DIE_UPSIDE_DOWN_VX;
		}
		else {
			vx = ENEMY_DIE_UPSIDE_DOWN_VX;
		}

		CGameData* game = CGameData::GetInstance();
		game->AddScore(100, x, y, this);

		vy = -ENEMY_DIE_UPSIDE_DOWN_VY;
		
	}
}