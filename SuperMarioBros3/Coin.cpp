#include "Coin.h"
#include "debug.h"

void CCoin::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_COIN)->Render(x, y);

	//RenderBoundingBox();
}

void CCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - COIN_BBOX_WIDTH / 2;
	t = y - COIN_BBOX_HEIGHT / 2;
	r = l + COIN_BBOX_WIDTH;
	b = t + COIN_BBOX_HEIGHT;
}

void CCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isBouncing)
	{
		if (GetTickCount64() - bouncing_start < COIN_BOUNCING_TIME)
		{
			if (y < startingY - COIN_BOUNCING_HEIGHT)
			{
				vy = 1;
			}

			y += vy * COIN_BOUNCING_SPEED * dt;
		}
		else
		{
			Delete();
		}
	}
}
