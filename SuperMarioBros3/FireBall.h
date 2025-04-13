#pragma once
#include "GameObject.h"

#define FIRE_BALL_VX 0.05f
#define FIRE_BALL_VY 0.05f

#define ID_ANI_FIRE_BALL 7001

#define FIRE_BALL_STATE_IDLE 100
#define FIRE_BALL_STATE_FLY 101

#define FIRE_BALL_BBOX_WIDTH 8
#define FIRE_BALL_BBOX_HEIGHT 8

class CFireBall :
    public CGameObject
{
protected:
	float xDir, yDir; 
	float init_x, init_y;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();

public:
	CFireBall(float x, float y) : CGameObject(x, y) {
		this->vx = FIRE_BALL_VX;
		this->vy = FIRE_BALL_VY;
		this->init_x = x;
		this->init_y = y;
		this->xDir = 0;
		this->yDir = 0;
		SetState(FIRE_BALL_STATE_IDLE);
	}

	void SetDir(float degree) {
		float radian = degree * (3.14 / 180);
		if (state == FIRE_BALL_STATE_IDLE) {
			xDir = cos(radian) * 2;
			yDir = -sin(radian) * 2;
		}
	}

	void ResetPos() {
		this->x = init_x;
		this->y = init_y;
		this->xDir = 0;
		this->yDir = 0;
		SetState(FIRE_BALL_STATE_IDLE);
	}
};

