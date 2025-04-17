#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_SUPER_MUSHROOM 100001

#define	SUPER_MUSHROOM_WIDTH 15
#define SUPER_MUSHROOM_BBOX_WIDTH 15
#define SUPER_MUSHROOM_BBOX_HEIGHT 15

#define SUPER_MUSHROOM_APPEAR_SPEED 0.01f

#define SUPER_MUSHROOM_SPEED_X 0.05f
#define SUPER_MUSHROOM_SPEED_Y 0.0015f

class CSuperMushroom : public CGameObject
{
	bool isAppearing = false;
	float originalY = 0;
	bool isMoving = false;
	bool isOnPlatform = false;
public:
	CSuperMushroom(float x, float y) : CGameObject(x, y) {}

	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	virtual int IsCollidable() { return 1; }
	virtual int IsBlocking() { return 0; }
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual void OnNoCollision(DWORD dt);

	void AppearFromQuestionBlock(float x, float y);
	void StartAppearing() { isAppearing = true; Activate(); }
};

