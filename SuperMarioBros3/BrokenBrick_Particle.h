#pragma once
#include "GameObject.h"
#include "Particle.h"
#include <vector>

using namespace std;

#define BROKEN_TIME 1000

class BrokenBrick_Particle : public CGameObject
{
	vector<CBrick_Particle*> particles;

	bool isBroken = false;
	ULONGLONG broken_start = -1;
	
public:
	BrokenBrick_Particle(float x, float y, vector<CBrick_Particle*> objects) : CGameObject(x, y)
	{
		this->particles = objects;
	}

	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void SetTrigger();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void RemoveParticle();
	int IsBlocking() { return 0; }

	void Deactivate() {
		for (int i = 0; i < particles.size(); i++)
		{
			particles[i]->Deactivate();
		}
		CGameObject::Deactivate();
	}
	void Delete() {
		for (int i = 0; i < particles.size(); i++)
		{
			particles[i]->Delete();
		}
		CGameObject::Delete();
	}
};
