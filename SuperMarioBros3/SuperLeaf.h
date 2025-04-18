#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_SUPER_LEAF_LEFT 110010
#define ID_ANI_SUPER_LEAF_RIGHT 110011

#define	SUPER_LEAF_WIDTH 15
#define SUPER_LEAF_BBOX_WIDTH 15
#define SUPER_LEAF_BBOX_HEIGHT 13

#define SUPER_LEAF_APPEAR_SPEED 0.1f

#define SUPER_LEAF_SPEED_X 0.05f
#define SUPER_LEAF_SPEED_Y 0.005f

#define SUPER_LEAF_BOUNCING_HEIGHT 50
#define SUPER_LEAF_FAILING_BOUNDING_RIGHT 30

class CSuperLeaf : public CGameObject
{
	bool isAppearing = false;
	bool isFalling = false;
	float originalY = 0;
	float originalX = 0;
	int nx = 1; // Staring direction of the leaf
public:
	CSuperLeaf(float x, float y) : CGameObject(x, y) {}

	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	virtual int IsBlocking() { return 0; }

	void AppearFromQuestionBlock(float x, float y);
	void StartAppearing() { isAppearing = true; Activate(); }
};

