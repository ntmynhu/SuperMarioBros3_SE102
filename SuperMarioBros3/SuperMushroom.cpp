#include "SuperMushroom.h"
#include "Mario.h"
#include "debug.h"

void CSuperMushroom::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_SUPER_MUSHROOM)->Render(x, y);
}

void CSuperMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isAppearing)
	{
		if (y > init_y - SUPER_MUSHROOM_BBOX_HEIGHT * 1.1f)
		{
			y -= SUPER_MUSHROOM_APPEAR_SPEED * dt;

			if (y <= init_y - SUPER_MUSHROOM_BBOX_HEIGHT * 1.1f)
			{
				y = init_y - SUPER_MUSHROOM_BBOX_HEIGHT * 1.1f;
				isAppearing = false;
				isMoving = true;

				vx = nx * SUPER_MUSHROOM_SPEED_X;
				vy = 0;
			}
		}
	}

	if (isMoving)
	{
		vy += SUPER_MUSHROOM_SPEED_Y * dt;
	}

	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CSuperMushroom::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - SUPER_MUSHROOM_BBOX_WIDTH / 2;
	t = y - SUPER_MUSHROOM_BBOX_HEIGHT / 2;
	r = l + SUPER_MUSHROOM_BBOX_WIDTH;
	b = t + SUPER_MUSHROOM_BBOX_HEIGHT;
}

void CSuperMushroom::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CMario*>(e->obj)) return;
	if (e->ny != 0)
	{
		vy = 0;
		if (e->ny < 0) isOnPlatform = true;
	}
	else if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = -vx;
	}
}

void CSuperMushroom::OnNoCollision(DWORD dt)
{
	if (isMoving)
	{
		x += vx * dt;
		y += vy * dt;
	}
}

void CSuperMushroom::AppearFromQuestionBlock(float marioX, float y)
{
	originalY = y;

	if (marioX < x)
		nx = 1;
	else
		nx = -1;

	StartAppearing();
}
