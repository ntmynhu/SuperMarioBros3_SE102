#include "GameObject.h"
#include "CoinUI.h"
#include "TimerUI.h"
#include "LivesUI.h"
#include "ScoreUI.h"
#include "PowerUI.h"
#include "CardUI.h"

#pragma once
#define ID_SPRITE_HUD_BACKGROUND 300001
#define HUD_WIDTH 250
#define HUD_HEIGHT 54

class HUD : public CGameObject
{
private:
	TimerUI* timer;
	CoinUI* coin;
	LivesUI* lives;
	WorldUI* world;
	ScoreUI* score;
	PowerUI* power;
	CardUI* cards;
protected:
	static HUD* __instance;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {}
	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 0; }
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
public:
	HUD(float x, float y):CGameObject(x, y) {}
	void Deactivate(){}
	void Render();
	static HUD* GetInstance();
	void AddCard(int id);
	void ClearCard();
};

