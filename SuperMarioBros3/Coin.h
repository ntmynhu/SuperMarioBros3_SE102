#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_COIN 11000

#define	COIN_WIDTH 10
#define COIN_BBOX_WIDTH 10
#define COIN_BBOX_HEIGHT 16

#define COIN_BOUNCING_TIME 325
#define COIN_BOUNCING_SPEED 0.2f
#define COIN_BOUNCING_HEIGHT 70

#define COIN_APPEARING_HEIGHT COIN_BBOX_HEIGHT + 5

class CCoin : public CGameObject {
private:
	bool isBouncing = false;
	ULONGLONG bouncing_start = -1;

	float startingY;
public:
	CCoin(float x, float y) : CGameObject(x, y) {
		startingY = y;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	void StartBouncing(float block_y)
	{ 
		vy = -1;

		isBouncing = true;
		bouncing_start = GetTickCount64();
		Activate();
	}
};