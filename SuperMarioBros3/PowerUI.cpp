#include "PowerUI.h"
#include "PlayScene.h"
#include "Mario.h"

void PowerUI::Render(float x, float y)
{
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	CMario* player = (CMario*)scene->GetPlayer();

	x -= 66;
	y -= 14;

	CSprites* s = CSprites::GetInstance();

	if (player == NULL)
	{
		for (int i = 0; i < 6; i++)
		{
			s->Get(ID_SPRITE_POWER_UNCHARGED)->DrawStatic(x + i * CHARGE_BAR_WIDTH, y);
		}
		return;
	}

	float powerCharge = player->GetChargingPowerTime();

	float chargingOffset = MARIO_CHARGING_POWER_TIME / 6;

	
	for (int i = 0; i < 6; i++)
	{
		if (powerCharge > chargingOffset * i || player->IsFullPower())
		{
			s->Get(ID_SPRITE_POWER_CHARGED)->DrawStatic(x + i * CHARGE_BAR_WIDTH, y);
		}
		else
		{
			s->Get(ID_SPRITE_POWER_UNCHARGED)->DrawStatic(x + i * CHARGE_BAR_WIDTH, y);
		}
	}

	float fullPowerTime = player->GetFullPowerTime();

	int hundred = (int)(fullPowerTime / 200);
	
	if (player->IsFullPower()) {
		if (hundred % 2 == 0) s->Get(ID_SPRITE_POWER_FULL)->DrawStatic(x + 5 * CHARGE_BAR_WIDTH + 11, y);
		else s->Get(ID_SPRITE_POWER_UNFULL)->DrawStatic(x + 5 * CHARGE_BAR_WIDTH + 11, y);
	}
	else
	{
		s->Get(ID_SPRITE_POWER_UNFULL)->DrawStatic(x + 5 * CHARGE_BAR_WIDTH + 11, y);
	}
}
