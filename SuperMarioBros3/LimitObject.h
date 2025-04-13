#pragma once
#include "GameObject.h"
class CLimitObject :
    public CGameObject
{
protected:
	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 0; }
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {};
	virtual void Render() {};
public:
	CLimitObject(float x, float y) :CGameObject(x, y) {};
};

