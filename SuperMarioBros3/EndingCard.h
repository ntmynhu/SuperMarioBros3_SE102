#pragma once
#include "GameObject.h"

#define ID_ANI_ENDING_CARD 510000
#define ID_ANI_CARD 510001

#define CARD_BBOX_WIDTH  16
#define CARD_BBOX_HEIGHT 16

#define ENDING_CARD_BBOX_WIDTH  32
#define ENDING_CARD_BBOX_HEIGHT 32

class CCard;

class CEndingCard : public CGameObject {
private:
	bool isBouncing = false;
	ULONGLONG bouncing_start = -1;
	CCard* card = NULL;
public:
	CEndingCard(float x, float y, CCard* card) : CGameObject(x, y)
	{
		this->card = card;
	}

	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	void StartBouncing(float block_y)
	{
		vy = -1;

		isBouncing = true;
		bouncing_start = GetTickCount64();
	}
};

class CCard : public CGameObject
{
public:
	CCard(float x, float y) : CGameObject(x, y) {}

	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() override { return 0; }
};


