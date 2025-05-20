#include "PowerUI.h"
#include "PlayScene.h"
#include "Mario.h"

void PowerUI::Render(float x, float y)
{
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	CMario* player = (CMario*)scene->GetPlayer();

	float powerCharge = player->GetChargingPowerTime();

	x -= 66;
	y -= 14;

	CSprites* s = CSprites::GetInstance();

	for (int i = 0; i < 6; i++)
	{
		s->Get(ID_SPRITE_POWER_UNCHARGED)->DrawStatic(x + i * CHARGE_BAR_WIDTH, y);
	}

	s->Get(ID_SPRITE_POWER_UNFULL)->DrawStatic(x + 5 * CHARGE_BAR_WIDTH + 11, y);
}
