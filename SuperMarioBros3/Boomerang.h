#pragma once
#include "CThrowable.h"

#define BOOMERANG_VX 0.07f
#define BOOMERANG_VY 0.09f

#define ID_ANI_BOOMERANG 8007

#define BOOMERANG_BBOX_WIDTH 16
#define BOOMERANG_BBOX_HEIGHT 16

#define BOOMERANG_MAX_DISTANCE 112

class CBoomerang :
	public CThrowable
{
protected:
	float xDir;
	float startX, startY;
	float returning;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

	void Render();

public:
	CBoomerang(float x, float y) : CThrowable(x, y) {
		this->startX = 0;
		this->startY = 0;
		this->xDir = 0;
	}
	void Throw(float x, float y, float xDir);

	virtual void Deactivate() {
		if (returning == true) {
			CThrowable::Deactivate();
			xDir = 0;
			vx = 0;
			vy = 0;
			returning = true;
		}
	}
};

