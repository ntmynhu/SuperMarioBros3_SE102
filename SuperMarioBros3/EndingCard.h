#pragma once
#include "GameObject.h"

class CEndingCard : public CGameObject {
private:
	bool isBouncing = false;
	ULONGLONG bouncing_start = -1;
public:
	CEndingCard(float x, float y) : CGameObject(x, y) {}

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

