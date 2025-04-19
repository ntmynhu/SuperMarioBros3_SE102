#include "SuperLeaf.h"
#include "debug.h"
void CSuperLeaf::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniID = nx > 0 ? ID_ANI_SUPER_LEAF_RIGHT : ID_ANI_SUPER_LEAF_LEFT;
	animations->Get(aniID)->Render(x, y);
	//RenderBoundingBox();
}

void CSuperLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isAppearing)
	{
		if (y > init_y - SUPER_LEAF_BOUNCING_HEIGHT)
		{
			float distanceToTop = y - (init_y - SUPER_LEAF_BOUNCING_HEIGHT) + 6;
			float ratio = distanceToTop / SUPER_LEAF_BOUNCING_HEIGHT;

			vy = - SUPER_LEAF_APPEAR_SPEED * ratio;

			if (y <= init_y - SUPER_LEAF_BOUNCING_HEIGHT)
			{
				y = init_y - SUPER_LEAF_BOUNCING_HEIGHT;
				vy = 0.0f;

				reach_time = GetTickCount64();
			}
		}
		else
		{
			if (GetTickCount64() - reach_time >= SUPER_LEAF_PAUSE_OFFSET)
			{
				isAppearing = false;
				isFalling = true;

				oscillation_time = 0;
				vy = 0.0f;
			}
		}
	}
	else if (isFalling)
	{
		// Oscillating horizontal motion using a sine wave
		oscillation_time += dt;

		vx = SUPER_LEAF_OSCILLATION_AMPLITUDE * sin(oscillation_time * SUPER_LEAF_OSCILLATION_FREQ);

		float absVx = abs(vx);
		if (absVx < 0.01f) // Turning point threshold
		{
			vy -= SUPER_LEAF_FLUTTER_LIFT * dt;
			if (vy < 0) vy = 0;
		}
		else
		{
			if (vy < SUPER_LEAF_MAX_FALL_SPEED)
				vy += SUPER_LEAF_GRAVITY * dt;
		}

		// Update direction
		nx = (vx > 0) ? 1 : -1;
	}
	// Position update
	x += vx * dt;
	y += vy * dt;
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
	StartAppearing();
}
