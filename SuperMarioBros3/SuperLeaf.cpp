#include "SuperLeaf.h"

void CSuperLeaf::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniID = nx > 0 ? ID_ANI_SUPER_LEAF_RIGHT : ID_ANI_SUPER_LEAF_LEFT;
	animations->Get(aniID)->Render(x, y);
}

void CSuperLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isAppearing)
	{
		if (y > originalY - SUPER_LEAF_BOUNCING_HEIGHT)
		{
			y -= SUPER_LEAF_APPEAR_SPEED * dt;

			if (y <= originalY - SUPER_LEAF_BOUNCING_HEIGHT)
			{
				y = originalY - SUPER_LEAF_BOUNCING_HEIGHT;
				isAppearing = false;
				isFalling = true;

				vx = nx * SUPER_LEAF_SPEED_X;
				vy = SUPER_LEAF_SPEED_Y;
			}
		}
	}

	if (isFalling)
	{
		x += nx * vx * dt;
		y += vy * dt;

		if (x > originalX + SUPER_LEAF_FAILING_BOUNDING_RIGHT)
		{
			nx = -1;
		}
		else if (x < originalX)
		{
			nx = 1;
		}
	}
}

void CSuperLeaf::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - SUPER_LEAF_BBOX_WIDTH / 2;
	t = y - SUPER_LEAF_BBOX_HEIGHT / 2;
	r = l + SUPER_LEAF_BBOX_WIDTH;
	b = t + SUPER_LEAF_BBOX_HEIGHT;
}

void CSuperLeaf::AppearFromQuestionBlock(float x, float y)
{
	originalX = x;
	originalY = y;
	StartAppearing();
}
