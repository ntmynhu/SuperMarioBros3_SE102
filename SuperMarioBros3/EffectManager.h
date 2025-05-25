#pragma once
#include "GameObject.h"
#include "UIElement.h"
#include <vector>
#include <string>

using namespace std;

#define ID_SPRITE_SCORE_EFFECT_100	400001
#define ID_SPRITE_SCORE_EFFECT_200	400002
#define ID_SPRITE_SCORE_EFFECT_400	400003
#define ID_SPRITE_SCORE_EFFECT_800	400004
#define ID_SPRITE_SCORE_EFFECT_1000	400005
#define ID_SPRITE_SCORE_EFFECT_2000	400006
#define ID_SPRITE_SCORE_EFFECT_4000	400007
#define ID_SPRITE_SCORE_EFFECT_8000	400008
#define ID_SPRITE_SCORE_EFFECT_1UP	400009

#define SCORE_EFFECT_TIME	1100
#define VISUAL_EFFECT_TIME	225

#define ID_SPRITE_TAIL_EFFECT_PINK_LEFT 400010
#define ID_SPRITE_TAIL_EFFECT_PINK_RIGHT 400011
#define ID_SPRITE_TAIL_EFFECT_WHITE_LEFT 400012
#define ID_SPRITE_TAIL_EFFECT_WHITE_RIGHT 400013

#define ID_SPRITE_CARD_STAR 500101
#define ID_SPRITE_CARD_PLANT 500102
#define ID_SPRITE_CARD_MUSHROOM 500103

#define ID_SPRITE_LETTER_A 400100 
#define ID_SPRITE_EXCLAMATION 400126

#define LETTER_WIDTH	8

class EffectManager : public CGameObject
{
	vector<CUIElement*> effects;
protected:
	static EffectManager* __instance;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {}
	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 0; }
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
public:
	EffectManager(float x, float y) :CGameObject(x, y) {}
	void Deactivate() {}
	void Render();
	static EffectManager* GetInstance();
	void AddEffect(CUIElement* effect) { effects.push_back(effect); }
};

class ScoreEffect : public CUIElement
{
private:
	ULONGLONG startTime;
	ULONGLONG currentTime;

	float increasement = 0;

	int id_sprite = -1;
public:
	ScoreEffect(int score, float x, float y) : CUIElement(x, y) {
		EffectManager::GetInstance()->AddEffect(this);
		this->startTime = GetTickCount64();
		this->currentTime = startTime;

		switch (score)
		{
		case 1:
			this->id_sprite = ID_SPRITE_SCORE_EFFECT_1UP;
			break;
		case 100:
			this->id_sprite = ID_SPRITE_SCORE_EFFECT_100;
			break;
		case 200:
			this->id_sprite = ID_SPRITE_SCORE_EFFECT_200;
			break;
		case 400:
			this->id_sprite = ID_SPRITE_SCORE_EFFECT_400;
			break;
		case 800:
			this->id_sprite = ID_SPRITE_SCORE_EFFECT_800;
			break;
		case 1000:
			this->id_sprite = ID_SPRITE_SCORE_EFFECT_1000;
			break;
		case 2000:
			this->id_sprite = ID_SPRITE_SCORE_EFFECT_2000;
			break;
		case 4000:
			this->id_sprite = ID_SPRITE_SCORE_EFFECT_4000;
			break;
		case 8000:
			this->id_sprite = ID_SPRITE_SCORE_EFFECT_8000;
			break;
		default:
			break;
		}
	}

	void Render();
};

class TailEffect : public CUIElement
{
private:
	ULONGLONG startTime;
public:
	TailEffect(float x, float y) : CUIElement(x, y) {
		EffectManager::GetInstance()->AddEffect(this);
		this->startTime = GetTickCount64();
	}
	
	void Render();
};

class Image : public CUIElement
{
private:
	int id_sprite = -1;
public:
	Image(int id_sprite, float x, float y) : CUIElement(x, y) {
		this->id_sprite = id_sprite;
		EffectManager::GetInstance()->AddEffect(this);
	}

	void Render();
};

class TextEffect : public CUIElement
{
private:
	ULONGLONG startTime;
	string text;
public:
	TextEffect(string text, float x, float y) : CUIElement(x, y) {
		EffectManager::GetInstance()->AddEffect(this);
		this->startTime = GetTickCount64();
		this->text = text;
	}

	void Render();
};

