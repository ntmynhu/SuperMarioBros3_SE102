#include "BrokenBrick_Particle.h"

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
				particles[i]->SetSpeed(1, 1);
			}
		}
		else
		{
			Delete();
		}
	}
}
