#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BLUE_BUTTON 95000
#define BLUE_BUTTON_WIDTH 16
#define BLUE_BUTTON_BBOX_WIDTH 16
#define BLUE_BUTTON_BBOX_HEIGHT 16

class CBlueButton : public CGameObject {
private:
	vector<LPGAMEOBJECT> goldenBricks;
	bool isPressed = false;
public:
	CBlueButton(float x, float y, vector<LPGAMEOBJECT> goldenBricks) : CGameObject(x, y)
	{
		this->goldenBricks = goldenBricks;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetTrigger();
};

