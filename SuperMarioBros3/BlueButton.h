#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BLUE_BUTTON 95000
#define ID_ANI_BLUE_BUTTON_PRESSED 95001
#define ID_ANI_BLUE_BUTTON_APPEARING 95002

#define BLUE_BUTTON_WIDTH 16
#define BLUE_BUTTON_BBOX_WIDTH 16
#define BLUE_BUTTON_BBOX_HEIGHT 16

#define BLUE_BUTTON_APPEARING_TIME 400

class CBlueButton : public CGameObject {
private:
	vector<LPGAMEOBJECT> goldenBricks;
	bool isPressed = false;
	bool isAppearing = false;
	ULONGLONG appearing_start = -1;
public:
	CBlueButton(float x, float y, vector<LPGAMEOBJECT> goldenBricks) : CGameObject(x, y)
	{
		this->goldenBricks = goldenBricks;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetTrigger();
	void StartAppearing();
};

