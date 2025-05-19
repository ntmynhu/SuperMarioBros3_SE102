#pragma once
#include "GameObject.h"

#define ID_SPRITE_NUMBER_0	301000
#define ID_SPRITE_NUMBER_1	301001
#define ID_SPRITE_NUMBER_2	301002
#define ID_SPRITE_NUMBER_3	301003
#define ID_SPRITE_NUMBER_4	301004
#define ID_SPRITE_NUMBER_5	301005
#define ID_SPRITE_NUMBER_6	301006
#define ID_SPRITE_NUMBER_7	301007
#define ID_SPRITE_NUMBER_8	301008
#define ID_SPRITE_NUMBER_9	301009

#define NUMBER_WIDTH	8

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

