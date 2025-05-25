#include "EndingCard.h"
#include "debug.h"

void CEndingCard::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_ENDING_CARD)->Render(x, y);

	card->Render();
} 

void CEndingCard::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
}

void CEndingCard::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - ENDING_CARD_BBOX_WIDTH / 2;
	t = y - ENDING_CARD_BBOX_HEIGHT / 2;
	r = l + ENDING_CARD_BBOX_WIDTH;
	b = t + ENDING_CARD_BBOX_HEIGHT;
}

void CCard::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_CARD)->Render(x, y);
}


void CCard::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
}

void CCard::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - CARD_BBOX_WIDTH / 2;
	t = y - CARD_BBOX_HEIGHT / 2;
	r = l + CARD_BBOX_WIDTH;
	b = t + CARD_BBOX_HEIGHT;
}
