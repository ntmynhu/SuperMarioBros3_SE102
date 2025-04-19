#include "RedKoopa.h"

#include "Koopa.h"
#include "Enemy.h"
#include "Mario.h"
#include "Brick.h"
#include "Block.h"
#include "Plant.h"
#include "Platform.h"
#include "debug.h"
#include "FallCensor.h"

CRedKoopa::CRedKoopa(float x, float y) :CKoopa(x, y) {
	fallCensor = new CFallCensor(x, y);
};
void CRedKoopa::OnNoCollision(DWORD dt) {
	fallCensor->SetPosition(x, y);
	CKoopa::OnNoCollision(dt);
}

void CRedKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//DebugOutTitle(L"left_lim %f right_lim %f", left_lim, right_lim);
	if (vx > 0) {
		fallCensor->SetX(this->x + KOOPA_BBOX_WIDTH / 2);
	}
	else {
		fallCensor->SetX(this->x - KOOPA_BBOX_WIDTH / 2);
	}
	if (this->isOnPlatform && state == KOOPA_STATE_WALKING) {
		if (!fallCensor->IsOnPlatform())
		{
			this->vx = -this->vx;
			fallCensor->SetPosition(x, y);
		}
	}

	if (state != KOOPA_STATE_WALKING) {
		fallCensor->SetPosition(x, y);
	}
	
	CKoopa::Update(dt, coObjects);
	fallCensor->Update(dt, coObjects);
}


void CRedKoopa::Render()
{
	int aniId = ID_ANI_RED_KOOPA_WALKING;
	switch (state) {
	case (KOOPA_STATE_DEFEND):
		if (isUpsideDown)
			aniId = ID_ANI_RED_KOOPA_DEFEND_UD;
		else aniId = ID_ANI_RED_KOOPA_DEFEND;
		break;
	case (KOOPA_STATE_DEFEND_SLIDING):
		if (isUpsideDown)
			aniId = ID_ANI_RED_KOOPA_SLIDE_UD;
		else aniId = ID_ANI_RED_KOOPA_SLIDE;
		break;
	case (KOOPA_STATE_RECOVER):
		if (isUpsideDown)
			aniId = ID_ANI_RED_KOOPA_RECOVER_UD;
		else aniId = ID_ANI_RED_KOOPA_RECOVER;
		break;
	case (KOOPA_STATE_WALKING):
		if (vx > 0) {
			aniId = ID_ANI_RED_KOOPA_WALKING_RIGHT;
		}
		break;
	case (ENEMY_STATE_DIE):
		aniId = ID_ANI_RED_KOOPA_DEFEND_UD;
	}

	fallCensor->Render();
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}