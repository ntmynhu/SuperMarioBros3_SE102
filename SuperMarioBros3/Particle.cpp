#include "Particle.h"
#include "debug.h"

void CBrick_Particle::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_BRICK_PARTICLE)->Render(x, y);
	//RenderBoundingBox();
}

void CBrick_Particle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!isStarted) return;

	DebugOut(L"[INFO] Particle Update: %f\n", x);

	x += vx * dt;
	y += vy * dt;

	vy += GRAVITY * dt;
}

void CBrick_Particle::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BRICK_PARTICLE_BBOX_WIDTH / 2;
	t = y - BRICK_PARTICLE_BBOX_HEIGHT / 2;
	r = l + BRICK_PARTICLE_BBOX_WIDTH;
	b = t + BRICK_PARTICLE_BBOX_HEIGHT;
}
