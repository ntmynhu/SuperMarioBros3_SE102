#include "BrokenBrick_Particle.h"
#include "Debug.h"

void BrokenBrick_Particle::Render()
{
}

void BrokenBrick_Particle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isBroken)
	{
		if (GetTickCount64() - broken_start < BROKEN_TIME)
		{
			for (int i = 0; i < particles.size(); i++)
			{
				
			}

			DebugOut(L"BrokenBrick_Particle: %d\n", GetTickCount64() - broken_start);
		}
		else
		{
			for (int i = 0; i < particles.size(); i++)
			{
				particles[i]->Delete();
			}

			Delete();
		}
	}
}

void BrokenBrick_Particle::SetTrigger()
{
	DebugOut(L"BrokenBrick_Particle: Strigger %f\n", x);

	isBroken = true;
	broken_start = GetTickCount64();
	Activate();

	for (int i = 0; i < particles.size(); i++)
	{
		particles[i]->Activate();
		particles[i]->SetStart();
	}

	particles[0]->SetSpeed(0.1f, -0.30f);
	particles[1]->SetSpeed(0.1f, -0.50f);
	particles[2]->SetSpeed(-0.1f, -0.30f);
	particles[3]->SetSpeed(-0.1f, -0.50f);
}

void BrokenBrick_Particle::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BRICK_PARTICLE_BBOX_WIDTH / 2;
	t = y - BRICK_PARTICLE_BBOX_HEIGHT / 2;
	r = l + BRICK_PARTICLE_BBOX_WIDTH;
	b = t + BRICK_PARTICLE_BBOX_HEIGHT;
}
