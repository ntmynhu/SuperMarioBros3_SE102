#pragma once
#include "CThrowable.h"

#define FIRE_BALL_VX 0.03f
#define FIRE_BALL_VY 0.03f

#define ID_ANI_FIRE_BALL 7001

#define FIRE_BALL_BBOX_WIDTH 8
#define FIRE_BALL_BBOX_HEIGHT 8

class CFireBall :
    public CThrowable
{
protected:
	float xDir, yDir; 
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

	void Render();

public:
	CFireBall(float x, float y) : CThrowable(x, y) {
		this->xDir = 0;
		this->yDir = 0;
	}

	void Fire(float x, float y, float degree) {
		this->x = x;
		this->y = y;

		float radian = degree * (3.14 / 180);
		xDir = cos(radian) * 2;
		yDir = -sin(radian) * 2;

		this->vx = FIRE_BALL_VX;
		this->vy = FIRE_BALL_VY;
		Activate();
	}

	void Deactivate() {
		CThrowable::Deactivate();
		this->xDir = 0;
		this->yDir = 0;
		this->vx = 0;
		this->vy = 0;
	}
};

