#pragma once
#include "GameObject.h"

#define ID_ANI_ENDING_CARD 510000
#define ID_ANI_CARD 510001

#define ID_ANI_CARD_STAR 510010
#define ID_ANI_CARD_PLANT 510020
#define ID_ANI_CARD_MUSHROOM 510030

#define CARD_BBOX_WIDTH  16
#define CARD_BBOX_HEIGHT 16

#define ENDING_CARD_BBOX_WIDTH  32
#define ENDING_CARD_BBOX_HEIGHT 32

#define CARD_MOVING_TIME 2000
#define CARD_MOVING_SPEED 0.1f

class CCard;

class CEndingCard : public CGameObject {
private:
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
	void SetTrigger();
};

class CCard : public CGameObject
{
private:
	bool isMoving = false;
	ULONGLONG moving_start = -1;
	int card_id = -1;
public:
	CCard(float x, float y) : CGameObject(x, y) {}

	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	void StartMovingUp();
	bool IsMoving() { return isMoving; }
};


