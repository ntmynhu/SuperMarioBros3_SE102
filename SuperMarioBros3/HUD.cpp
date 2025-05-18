#include "HUD.h"
#include "Game.h"
HUD* HUD::__instance = NULL;

HUD* HUD::GetInstance()
{
	if (__instance == NULL)
	{
		__instance = new HUD(0, 0);
		
		if (__instance->timer == NULL)
			__instance->timer = new TimerUI(0, 0);
	}
	return HUD::__instance;
}

void HUD::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

}

void HUD::Render() {
	CGame* g = CGame::GetInstance();
	CSprites* s = CSprites::GetInstance();

	s->Get(ID_SPRITE_HUD_BACKGROUND)->DrawStatic(x, y - HUD_HEIGHT/2 + 6);

	timer->Render(x, y - HUD_HEIGHT / 2 + 6);
}