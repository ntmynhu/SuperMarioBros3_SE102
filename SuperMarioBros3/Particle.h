#pragma once
#include "GameObject.h"
#include "Animation.h"

#define ID_ANI_BRICK_PARTICLE 85100

class CBrick_Particle : public CGameObject
{
public:
	CBrick_Particle(float x, float y) : CGameObject(x, y) {}
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
};


