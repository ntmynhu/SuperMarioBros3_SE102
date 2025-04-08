#include "RedKoopa.h"

#include "Koopa.h"
#include "Enemy.h"
#include "Mario.h"
#include "Brick.h"
#include "Platform.h"
#include "debug.h"

void CRedKoopa::OnNoCollision(DWORD dt) {
	left_lim = 0.0f;
	right_lim = 0.0f;
	CKoopa::OnNoCollision(dt);
}
void CRedKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
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
				if (dynamic_cast<CPlatform*>(e->obj) || dynamic_cast<CBrick*>(e->obj)) {
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


void CRedKoopa::OnCollisionWithGround(LPCOLLISIONEVENT e)
{
	CGameObject* ground = dynamic_cast<CGameObject*>(e->obj);
	float t, l, r, b;
	ground->GetBoundingBox(l, t, r, b);
	if (l < left_lim || left_lim == right_lim) {
		DebugOut(L"L: %f, Left_lim: %f\n", l, left_lim);
		left_lim = l;
	}
	if (r > right_lim || left_lim == right_lim) {
		DebugOut(L"R: %f, Right_lim: %f\n", r, right_lim);
		right_lim = r;
	}
	
}


void CRedKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	DebugOutTitle(L"left_lim %f right_lim %f", left_lim, right_lim);
	if (left_lim != right_lim) {
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
	}

	CKoopa::Update(dt, coObjects);
}


void CRedKoopa::Render()
{
	int aniId = ID_ANI_RED_KOOPA_WALKING;
	switch (state) {
	case (KOOPA_STATE_DEFEND):
		aniId = ID_ANI_RED_KOOPA_DEFEND;
		break;
	case (KOOPA_STATE_DEFEND_SLIDING):
		aniId = ID_ANI_RED_KOOPA_SLIDE;
		break;
	case (KOOPA_STATE_RECOVER):
		aniId = ID_ANI_RED_KOOPA_RECOVER;
		break;
	case (KOOPA_STATE_WALKING):
		if (vx > 0) {
			aniId = ID_ANI_RED_KOOPA_WALKING_RIGHT;
		}
		break;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}