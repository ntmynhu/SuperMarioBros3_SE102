#include "SuperMushroom.h"

void CSuperMushroom::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_SUPER_MUSHROOM)->Render(x, y);
}

void CSuperMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isAppearing)
	{
		if (y > originalY - SUPER_MUSHROOM_BBOX_HEIGHT)
		{
			y -= SUPER_MUSHROOM_APPEAR_SPEED * dt;

			if (y <= originalY - SUPER_MUSHROOM_BBOX_HEIGHT)
			{
				y = originalY - SUPER_MUSHROOM_BBOX_HEIGHT;
				isAppearing = false;
				isMoving = true;
			}
		}
	}

	if (isMoving)
	{
		
	}
}

void CSuperMushroom::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - SUPER_MUSHROOM_BBOX_WIDTH / 2;
	t = y - SUPER_MUSHROOM_BBOX_HEIGHT / 2;
	r = l + SUPER_MUSHROOM_BBOX_WIDTH;
	b = t + SUPER_MUSHROOM_BBOX_HEIGHT;
}

void CSuperMushroom::AppearFromQuestionBlock(float x, float y)
{
	originalY = y;

	StartAppearing();
}
