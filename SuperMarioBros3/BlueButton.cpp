#include "BlueButton.h"
#include "GoldenBrick.h"

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

void CBlueButton::SetTrigger()
{
	if (isPressed) return;

	isPressed = true;
	DebugOut(L"[INFO] Blue button pressed: %d\n", goldenBricks.size());
	for (int i = 0; i < goldenBricks.size(); i++)
	{
		if (goldenBricks[i] == NULL) continue;
		CGoldenBrick* brick = dynamic_cast<CGoldenBrick*>(goldenBricks[i]);
		if (brick != NULL)
		{
			brick->TurnToCoin();
		}
	}
}
