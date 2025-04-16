#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"

#include "Enemy.h"
#include "Plant.h"
#include "FireBall.h"
#include "Coin.h"
#include "QuestionBlock.h"

#include "Collision.h"
#include "Portal.h"

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (abs(vx) > abs(maxVx)) vx = maxVx;

	if (nx == 1 && ax < 0 && vx < 0) vx = 0;

	if (nx == -1 && ax > 0 && vx > 0) vx = 0;

	//DebugOutTitle(L"Vx: %d", vx);

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}
  
	if (GetTickCount64() - stateChange_start > MARIO_STATE_CHANGE_TIME)
	{
		stateChange_start = 0;
		isChangingState = false;
	}
  
	currentForm->Update(dt, this, coObjects);
	
	CCollision::GetInstance()->Process(this, dt, coObjects);
	HoldingUpdate(dt);
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
	else if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = 0;
	}

	if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CEnemy*>(e->obj))
		OnCollisionWithEnemy(e);
	else if (dynamic_cast<CPlant*>(e->obj))
		OnCollisionWithPlant(e);
	else if (dynamic_cast<CFireBall*>(e->obj))
		OnCollisionWithFireBall(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<CQuestionBlock*>(e->obj))
		OnCollisionWithQuestionBlock(e);
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}

void CMario::OnCollisionWithPlant(LPCOLLISIONEVENT e)
{
	CPlant* plant = dynamic_cast<CPlant*>(e->obj);

	bool isTailAttack = false;
	CMarioRacoon* racoon = dynamic_cast<CMarioRacoon*>(currentForm);
	if (racoon)
	{
		if (racoon->IsTailAttacking())
		{
			plant->TakeTailAttackDamage(e->nx);
			isTailAttack = true;
		}
	}

	if(plant->GetState() != PLANT_STATE_DIE && untouchable == 0 && !isTailAttack)
		TakeDamage();
}


void CMario::OnCollisionWithFireBall(LPCOLLISIONEVENT e)
{
	CFireBall* fireball = dynamic_cast<CFireBall*>(e->obj);
	if (fireball->GetState() != FIRE_BALL_STATE_IDLE && untouchable == 0)
		TakeDamage();
}

void CMario::OnCollisionWithQuestionBlock(LPCOLLISIONEVENT e)
{
	CQuestionBlock* qBlock = dynamic_cast<CQuestionBlock*>(e->obj);

	if (e->ny > 0)
	{
		if (!qBlock->IsEmpty())
		{
			qBlock->SpawnItem();
		}
	}
}

void CMario::OnCollisionWithEnemy(LPCOLLISIONEVENT e)
{
	CEnemy* enemy = dynamic_cast<CEnemy*>(e->obj);
	DebugOut(L"Collided! Enemy state %d\n", enemy->GetState());
	if (e->ny < 0 && enemy->GetState() != ENEMY_STATE_DIE)
	{
		vy = -MARIO_JUMP_DEFLECT_SPEED;
	}
	else // hit by Goomba
	{
		bool isTailAttack = false;
		CMarioRacoon* racoon = dynamic_cast<CMarioRacoon*>(currentForm);
		if (racoon)
		{
			if (racoon->IsTailAttacking())
			{
				enemy->TakeTailAttackDamage(e->nx);
				isTailAttack = true;
			}
		}

		if (untouchable == 0 && !isTailAttack)
		{
			if (enemy->IsDamagable())
			{
				TakeDamage();
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

void CMario::HoldingUpdate(DWORD dt) {
	if (holdingObj != NULL) {
		if (holdingObj->GetState() != ENEMY_STATE_DIE) {
			if (!isReadyToHold) {
				holdingObj->HandleMarioRelease(nx);
				holdingObj = NULL;
			}
		}
		else {
			holdingObj = NULL;
		}
	}
}
void CMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (state == MARIO_STATE_DIE)
		aniId = ID_ANI_MARIO_DIE;
	else
		aniId = currentForm->GetAniId(this);

	if (!isChangingState)
		animations->Get(aniId)->Render(x, y);
	else
	{
		float a = (GetTickCount64() - stateChange_start) % 5 == 0? 1 : 0;
		animations->Get(aniId)->Render(x, y, a);
	}

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
		isReadyToHold = false;
	}
	else if (state == MARIO_STATE_B)
	{
		isReadyToHold = true;
	}
	else if (state == MARIO_STATE_B_RELEASE) {
		isReadyToHold = false;
	}

	int old_nx = nx;

	currentForm->SetState(state, this);

	CGameObject::SetState(state);
}

void CMario::ChangeForm(int newLevel)
{
	StartChangingState();

	// Pause game for a bit
	CGame::GetInstance()->StartMarioPause();

	switch (newLevel) {
		case MARIO_LEVEL_SMALL:
			y += (currentForm->GetLevel() > MARIO_LEVEL_SMALL) ? (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2 : 0;
			currentForm = new CMarioSmall();
			break;
		case MARIO_LEVEL_BIG:
			currentForm = new CMarioBig();
			break;
		case MARIO_LEVEL_RACOON:
			currentForm = new CMarioRacoon();
			break;
	}

	DebugOut(L"[INFO] Mario changed to level %d\n", newLevel);
	DebugOut(L"[INFO] CurrentForm %d\n", currentForm->GetLevel());
}

void CMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
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

