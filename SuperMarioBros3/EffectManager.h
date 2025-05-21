#pragma once
#include "GameObject.h"
#include "UIElement.h"
#include <vector>

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
public:
	ScoreEffect(float x, float y) : CUIElement(x, y) {
		EffectManager::GetInstance()->AddEffect(this);
	}
	void Render();
};

