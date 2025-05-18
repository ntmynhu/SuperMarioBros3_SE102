#pragma once
#include "GameObject.h"

class CUIElement : public CGameObject
{
protected:
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {}
	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 0; }
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {}
public:
	CUIElement(float x, float y) :CGameObject(x, y) {}
	void Deactivate() {}
	virtual void Render() {}
	virtual void Render(float x, float y) {}
};

