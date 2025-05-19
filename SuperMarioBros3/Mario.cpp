#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"

#include "Enemy.h"
#include "Plant.h"
#include "FireBall.h"
#include "Coin.h"
#include "QuestionBlock.h"
#include "SuperMushroom.h"

#include "Collision.h"
#include "Portal.h"
#include "SuperLeaf.h"
#include "Tunnel.h"
#include "BlueButton.h"
#include "WallMario.h"
#include "PlatformKill.h"

#include "GameData.h"

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	DebugOutTitle(L"MARIO POS %f %f", x, y);
	if (state == MARIO_STATE_DOWN_TUNNEL || state == MARIO_STATE_UP_TUNNEL) {
		
		nx = 0;
		y += vy * dt;
		CCollision::GetInstance()->Process(this, dt, coObjects);
		
		return;
	}
	if (GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	if (isChangingState == 1) {
		if (GetTickCount64() - stateChange_start > currentForm->GetUpStateChangeTime())
		{
			stateChange_start = 0;
			isChangingState = 0;
			CGame::GetInstance()->StopMarioPause();
		}
		else {
			return;
		}
	}
	else if (isChangingState == -1) {
		if (GetTickCount64() - stateChange_start > currentForm->GetDownStateChangeTime() / 2)
		{
			CGame::GetInstance()->StopMarioPause();
		}
		else {
			return;
		}
		if (GetTickCount64() - stateChange_start > currentForm->GetDownStateChangeTime())
		{
			stateChange_start = 0;
			isChangingState = 0;
		}
	}

	vy += ay * dt;
	vx += ax * dt;

	if (abs(vx) > abs(maxVx)) vx = maxVx;

	if (nx == 1 && ax < 0 && vx < 0) 
		vx = 0;

	if (nx == -1 && ax > 0 && vx > 0) 
		vx = 0;

	if (stickingObj) {
		float w_vx, w_vy;
		stickingObj->GetSpeed(w_vx, w_vy);
		if (w_vx < 0 && vx > w_vx) {
			vx = w_vx;
		} else if (w_vx > 0 && vx < w_vx) {
			vx = w_vx;
		}
	}

	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	if (scene) {
		CWallMario* stop_left = (CWallMario*)scene->GetStopLeft();
		if (stop_left) {
			float w_x, w_vx, w_vy;
			stop_left->GetBoundX(w_x);
			stop_left->GetSpeed(w_vx, w_vy);
			if (w_vx > 0 && x <= w_x && vx < w_vx) {
				vx = (w_x - x) / dt;
			}
		}

		CWallMario* stop_right = (CWallMario*)scene->GetStopRight();
		if (stop_right) {
			float w_x, w_vx, w_vy;
			stop_right->GetBoundX(w_x);
			stop_right->GetSpeed(w_vx, w_vy);
			if (w_vx > 0 && x >= w_x && vx > w_vx) {
				vx = (w_x - x) / dt;
			}
		}
	}

	if (isChargingPower && IsFullSpeed())
	{
		if (!isFullPower) chargingPowerTime += dt;

		if (chargingPowerTime > MARIO_CHARGING_POWER_TIME)
		{
			isFullPower = true;
			fullPowerTime = MARIO_FULL_POWER_TIME;
		}
	}
	else
	{
		isFullPower = false;

		chargingPowerTime -= dt;
		if (chargingPowerTime < 0)
			chargingPowerTime = 0;
	}

	if (isFullPower)
	{
		fullPowerTime -= dt;

		if (fullPowerTime < 0)
		{
			isFullPower = false;
			isChargingPower = false;
		}
	}

	tail->SetPosition(x + nx * 8, y + 4);

	currentForm->Update(dt, this, coObjects);

	CCollision::GetInstance()->Process(this, dt, coObjects);
	HoldingUpdate(dt);

	//if (isFullPower)
	//{
	//	DebugOutTitle(L"Full Power");
	//}
	//else if (isChargingPower || chargingPowerTime > 0)
	//{
	//	DebugOutTitle(L"Charging Power");
	//}
	//else
	//{
	DebugOutTitle(L"IsOnPlatform %d\n", isOnPlatform);
	//}

}

void CMario::OnNoCollision(DWORD dt)
{
	if (state == MARIO_STATE_DOWN_TUNNEL || state == MARIO_STATE_UP_TUNNEL) return;

	x += vx * dt;
	y += vy * dt;
	if (!isStickToPlatform)
		isOnPlatform = false;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{		
	if (dynamic_cast<CPlatformKill*>(e->obj))
		OnCollisionWithPlatformKill(e);

	if (state == MARIO_STATE_DOWN_TUNNEL || state == MARIO_STATE_UP_TUNNEL) {
		if (dynamic_cast<CPortal*>(e->obj))
			OnCollisionWithPortal(e);
		else if (dynamic_cast<CTunnel*>(e->obj))
			OnCollisionWithTunnel(e);
		return;
	}

	if (e->ny != 0 && (e->obj->IsBlocking() || e->obj->IsBlocking(this)))
	{
		vy = 0;
		if (e->ny < 0) isOnPlatform = true;
	}
	else if (e->nx != 0 && (e->obj->IsBlocking() || e->obj->IsBlocking(this)))
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
	else if (dynamic_cast<CBlock*>(e->obj))
		OnCollisionWithBlock(e);
	else if (dynamic_cast<CSuperMushroom*>(e->obj))
		OnCollisionWithMushroomAndLeaf(e);
	else if (dynamic_cast<CSuperLeaf*>(e->obj))
		OnCollisionWithMushroomAndLeaf(e);
	else if (dynamic_cast<CTunnel*>(e->obj))
		OnCollisionWithTunnel(e);
	else if (dynamic_cast<CBlueButton*>(e->obj))
		OnCollisionWithBlueButton(e);
	
	
}

void CMario::OnCollisionWithTunnel(LPCOLLISIONEVENT e) {
	CTunnel* tunnel = dynamic_cast<CTunnel*>(e->obj);
	if (tunnel->IsEnterable()) {
		if (state == MARIO_STATE_SIT && tunnel->GetDirection() == 1 && e->ny < 0) {
			SetState(MARIO_STATE_DOWN_TUNNEL);
			DebugOut(L"MARIO ENTERING HIDDEN MAP");
			InputLock();
		}
		else if (tunnel->GetDirection() == -1 && e->ny > 0) {
			SetState(MARIO_STATE_UP_TUNNEL);
			InputLock();
		}
		return;
	}
	else {
		if (state == MARIO_STATE_DOWN_TUNNEL || state == MARIO_STATE_UP_TUNNEL) {
			SetState(MARIO_STATE_IDLE);
			return;
		}
	}
	
}
void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	float out_x, out_y;
	p->GetOutPos(out_x, out_y);
	if (out_x >= 0 && out_y >= 0) {
		SetPosition(out_x, out_y);
	}

	holdingObj = NULL;
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}

void CMario::OnCollisionWithPlant(LPCOLLISIONEVENT e)
{
	CPlant* plant = dynamic_cast<CPlant*>(e->obj);
	if(plant->isDamagable() && untouchable == 0)
		TakeDamage();
}


void CMario::OnCollisionWithFireBall(LPCOLLISIONEVENT e)
{
	CFireBall* fireball = dynamic_cast<CFireBall*>(e->obj);
	if (fireball->GetState() != FIRE_BALL_STATE_IDLE && untouchable == 0)
		TakeDamage();
}

void CMario::OnCollisionWithBlock(LPCOLLISIONEVENT e)
{
	CBlock* qBlock = dynamic_cast<CBlock*>(e->obj);

	if (e->ny > 0)
	{
		qBlock->TriggerAction(e);
	}
}

void CMario::OnCollisionWithMushroomAndLeaf(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	int nextForm = currentForm->GetLevel() + 1;
	if (nextForm > MARIO_LEVEL_RACOON) return; // max level is racoon, update point logic will come later

	ChangeForm(nextForm, 1);
}

void CMario::OnCollisionWithBlueButton(LPCOLLISIONEVENT e)
{
	if (e->ny < 0)
	{
		CBlueButton* button = dynamic_cast<CBlueButton*>(e->obj);
		button->SetTrigger();
	}
}

void CMario::OnCollisionWithPlatformKill(LPCOLLISIONEVENT e) {
	SetState(MARIO_STATE_DIE);
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
		if (untouchable == 0)
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

	float x_offset = 0;
	if (currentForm->GetLevel() == MARIO_LEVEL_RACOON) {
		if (nx < 0) x_offset = 4;
		else x_offset = -4;
	}

	if (isChangingState != -1)
		animations->Get(aniId)->Render(x + x_offset, y, 1, true);
	else
	{
		float a = (GetTickCount64() - stateChange_start) % 5 == 0? 1 : 0;
		animations->Get(aniId)->Render(x + x_offset, y, a, true);
	}

	tail->Render();
	//RenderBoundingBox();

	//DebugOutTitle(L"Coins: %d", coin);
	//DebugOutTitle(L"Mario State: %d", currentForm->GetLevel());
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (isInputLock) return;
	if (this->state == MARIO_STATE_DIE) return;
	
	CGameObject::SetState(state);

	if (state == MARIO_STATE_DIE)
	{
		die_start = GetTickCount64();
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
	else if (state == MARIO_STATE_DOWN_TUNNEL) {
		vy = MARIO_TUNNEL_SPEED_Y;
		vx = 0;
		ax = 0;
	}
	else if (state == MARIO_STATE_UP_TUNNEL) {
		vy = -MARIO_TUNNEL_SPEED_Y;
		vx = 0;
		ax = 0;
	}

	currentForm->SetState(state, this);
}

void CMario::ChangeForm(int newLevel, int isChanging) //-1 as down, 1 as up, 0 as no need to count
{
	if (isChanging == -1) {
		StartChangingStateDown();
		CGame::GetInstance()->StartMarioPause();
	}
	else if (isChanging == 1) {
		StartChangingStateUp();
		CGame::GetInstance()->StartMarioPause();
	}

	
	switch (newLevel) {
		case MARIO_LEVEL_SMALL:
			y += (currentForm->GetLevel() > MARIO_LEVEL_SMALL) ? (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2 : 0;
			currentForm = new CMarioSmall();
			break;
		case MARIO_LEVEL_BIG:
			y -= (currentForm->GetLevel() < MARIO_LEVEL_BIG) ? (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2 : 0;
			currentForm = new CMarioBig();
			break;
		case MARIO_LEVEL_RACOON:
			currentForm = new CMarioRacoon();
			break;
	}
	
	CGameData::GetInstance()->SetLevel(newLevel);
	DebugOut(L"[INFO] Mario changed to level %d\n", newLevel);
	DebugOut(L"[INFO] CurrentForm %d\n", currentForm->GetLevel());
}

void CMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	currentForm->GetBoundingBox(left, top, right, bottom, this);
}

// Check if Mario is in full speed -> to decrease the power bar when mario change his direction
bool CMario::IsFullSpeed()
{
	return abs(vx) >= MARIO_RUNNING_SPEED;
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

