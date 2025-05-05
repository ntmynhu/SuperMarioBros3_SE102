#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BRICK_PARTICLE 85100
#define BRICK_PARTICLE_WIDTH 16
#define BRICK_PARTICLE_BBOX_WIDTH 16
#define BRICK_PARTICLE_BBOX_HEIGHT 16

#define GRAVITY 0.002f

class CBrick_Particle : public CGameObject
{
private:
	bool isStarted = false;
public:
	CBrick_Particle(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetStart() { isStarted = true;}	
	int IsBlocking() { return 0; }
};


