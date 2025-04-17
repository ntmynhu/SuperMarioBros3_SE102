#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_COIN 11000

#define	COIN_WIDTH 10
#define COIN_BBOX_WIDTH 10
#define COIN_BBOX_HEIGHT 16

#define COIN_BOUNCING_TIME 385
#define COIN_BOUNCING_SPEED 0.35f
#define COIN_BOUNCING_HEIGHT 100

class CCoin : public CGameObject {
private:
	bool isBouncing = false;
	ULONGLONG bouncing_start = -1;

	float startingY;
public:
	CCoin(float x, float y) : CGameObject(x, y) {
		vy = -1;
		startingY = y;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	void StartBouncing() { isBouncing = true; bouncing_start = GetTickCount64(); Activate(); }
};