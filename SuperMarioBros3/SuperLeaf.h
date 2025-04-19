#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_SUPER_LEAF_LEFT 110010
#define ID_ANI_SUPER_LEAF_RIGHT 110011

#define	SUPER_LEAF_WIDTH 15
#define SUPER_LEAF_BBOX_WIDTH 15
#define SUPER_LEAF_BBOX_HEIGHT 13

#define SUPER_LEAF_APPEAR_SPEED 0.3f

#define SUPER_LEAF_OSCILLATION_AMPLITUDE 0.07f
#define SUPER_LEAF_OSCILLATION_FREQ 0.003f

#define SUPER_LEAF_GRAVITY 0.0003f
#define SUPER_LEAF_MAX_FALL_SPEED 0.08f           

#define SUPER_LEAF_FLUTTER_LIFT 0.0005f       

#define SUPER_LEAF_BOUNCING_HEIGHT 60

#define SUPER_LEAF_PAUSE_OFFSET 100

class CSuperLeaf : public CGameObject
{
protected:
	bool isAppearing = false;
	bool isFalling = false;
	ULONGLONG reach_time = 0;
	int nx = 1; // Staring direction of the leaf
	ULONGLONG oscillation_time = 0;
public:
	CSuperLeaf(float x, float y) : CGameObject(x, y) {}

	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	virtual int IsBlocking() { return 0; }

	void AppearFromQuestionBlock(float x, float y);
	void StartAppearing() { isAppearing = true; Activate(); }
};

