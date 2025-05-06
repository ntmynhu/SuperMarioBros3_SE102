#include "BlueButton.h"

void CBlueButton::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_BLUE_BUTTON)->Render(x, y);
}

void CBlueButton::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BLUE_BUTTON_BBOX_WIDTH / 2;
	t = y - BLUE_BUTTON_BBOX_HEIGHT / 2;
	r = l + BLUE_BUTTON_BBOX_WIDTH;
	b = t + BLUE_BUTTON_BBOX_HEIGHT;
}
