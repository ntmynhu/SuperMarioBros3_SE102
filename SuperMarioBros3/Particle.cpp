#include "Particle.h"

void CBrick_Particle::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = ID_ANI_BRICK_PARTICLE;
	animations->Get(aniId)->Render(x, y);
}

void CBrick_Particle::GetBoundingBox(float& l, float& t, float& r, float& b)
{
}
