#pragma once
#include "GameObject.h"

#define BOOMERANG_VX 0.07f
#define BOOMERANG_VY 0.077f

#define ID_ANI_BOOMERANG 7001

#define BOOMERANG_BBOX_WIDTH 16
#define BOOMERANG_BBOX_HEIGHT 16

#define BOOMERANG_MAX_DISTANCE 112
class CBoomerang :
	public CGameObject
{
protected:
	float xDir;
	float startX, startY;
	float returning;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual int IsOverlappable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual int IsCollidable() { return 1; };
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

	void Render();

public:
	CBoomerang(float x, float y) : CGameObject(x, y) {
		this->vx = 0;
		this->vy = 0;
		this->startX = 0;
		this->startY = 0;
		this->xDir = 0;
	}
	void Throw(float x, float y, float xDir);
	virtual void Deactivate() {
		CGameObject::Deactivate();
		xDir = 0;
		vx = 0;
		vy = 0;
		returning = true;
	}
	void ResetPos() {}
};

