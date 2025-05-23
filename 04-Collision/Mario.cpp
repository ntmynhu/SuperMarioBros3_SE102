#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"

#include "Enemy.h"
#include "Coin.h"

#include "Collision.h"

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (abs(vx) > abs(maxVx)) vx = maxVx;
	
	if (nx == 1 && ax < 0 && vx < 0) vx = 0;

	if (nx == -1 && ax > 0 && vx > 0) vx = 0;

	//DebugOutTitle(L"Vx: %d", vx);

	// reset untouchable timer if untouchable time has passed
	if ( GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	currentForm->Update(dt, this, coObjects);

	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
	isOnPlatform = false;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny < 0) isOnPlatform = true;
	}
	else 
	if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = 0;
	}

	if (dynamic_cast<CEnemy*>(e->obj))
		OnCollisionWithEnemy(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
}

void CMario::OnCollisionWithEnemy(LPCOLLISIONEVENT e)
{
	CEnemy* enemy = dynamic_cast<CEnemy*>(e->obj);
	DebugOut(L"Collided! Enemy state %d\n", enemy->GetState());
	if (e->ny < 0)
	{	
		vy = -MARIO_JUMP_DEFLECT_SPEED;
	}
	else // hit by Goomba
	{
		if (untouchable == 0)
		{
			if (enemy->IsDamagable())
			{
				currentForm->OnTakeDamage(this);
			}
		}
	}
	// jump on top >> kill Goomba and deflect a bit 
	enemy->OnCollisionByMario(e);
}

void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	coin++;
}

void CMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (state == MARIO_STATE_DIE)
		aniId = ID_ANI_MARIO_DIE;
	else 
		aniId = currentForm->GetAniId(this);

	animations->Get(aniId)->Render(x, y);

	//RenderBoundingBox();
	
	//DebugOutTitle(L"Coins: %d", coin);
	//DebugOutTitle(L"Mario State: %d", currentForm->GetLevel());
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return; 

	if (state == MARIO_STATE_DIE)
	{
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
	}

	currentForm->SetState(state, this);
	CGameObject::SetState(state);
}

void CMario::ChangeForm(int newLevel)
{
	switch (newLevel) {
	case MARIO_LEVEL_SMALL:
		y += (currentForm->GetLevel() > MARIO_LEVEL_SMALL) ? (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2 : 0;
		currentForm = new CMarioSmall();
		break;
	case MARIO_LEVEL_BIG:
		currentForm = new CMarioBig();
		break;
	}
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	currentForm->GetBoundingBox(left, top, right, bottom, this);
}

void CMario::SetLevel(int l)
{
	// Adjust position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	level = l;
}

