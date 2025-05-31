#include "BlueButton.h"
#include "GoldenBrick.h"

void CBlueButton::Render()
{
	CAnimations* animations = CAnimations::GetInstance();

	int aniId = -1;
	if (isAppearing)
	{
		aniId = ID_ANI_BLUE_BUTTON_APPEARING;
	}
	else if (isPressed)
	{
		aniId = ID_ANI_BLUE_BUTTON_PRESSED;
	}
	else
	{
		aniId = ID_ANI_BLUE_BUTTON;
	}

	animations->Get(aniId)->Render(x, y);
}

void CBlueButton::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isAppearing)
	{
		if (GetTickCount64() - appearing_start > BLUE_BUTTON_APPEARING_TIME)
		{
			isAppearing = false;
		}
	}

	for (int i = 0; i < goldenBricks.size(); i++)
	{
		if (!goldenBricks[i] || goldenBricks[i]->IsDeleted()) {
			goldenBricks[i] = NULL;
		}
	}
}

void CBlueButton::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BLUE_BUTTON_BBOX_WIDTH / 2;
	t = y - BLUE_BUTTON_BBOX_HEIGHT / 2;

	if (isPressed) t += BLUE_BUTTON_BBOX_HEIGHT / 2;

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
		if (!goldenBricks[i] || goldenBricks[i]->IsDeleted()) {
			goldenBricks[i] = NULL;
			continue;
		}
		CGoldenBrick* brick = dynamic_cast<CGoldenBrick*>(goldenBricks[i]);
		if (brick != NULL)
		{
			brick->TurnToCoin();
		}
	}
}

void CBlueButton::StartAppearing()
{
	appearing_start = GetTickCount64();
	isAppearing = true;
	Activate();
}
