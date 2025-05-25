#pragma once
#include "GameObject.h"
class CThrowable :
    public CGameObject
{
protected:
	virtual int IsOverlappable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual int IsCollidable() { return 1; };
public:
	CThrowable(float x, float y) :CGameObject(x, y) {
		this->vx = 0;
		this->vy = 0;
	}
	void ResetPos() {}
};

