#include "EndingCard.h"
#include "EffectManager.h"
#include "debug.h"
#include <random>
#include "HUD.h"

void CEndingCard::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_ENDING_CARD)->Render(x, y);

	card->Render();
} 

void CEndingCard::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (card != NULL)
	{
		card->Update(dt, coObjects);
	}
}

void CEndingCard::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - ENDING_CARD_BBOX_WIDTH / 2;
	t = y - ENDING_CARD_BBOX_HEIGHT / 2;
	r = l + ENDING_CARD_BBOX_WIDTH;
	b = t + ENDING_CARD_BBOX_HEIGHT;
}

void CEndingCard::SetTrigger()
{
	if (card != NULL)
	{
		if (!card->IsMoving())
			card->StartMovingUp();
	}
}

void CCard::Render()
{
	CAnimations* animations = CAnimations::GetInstance();

	if (isMoving)
	{
		switch (card_id)
		{
		case 1:
			animations->Get(ID_ANI_CARD_STAR)->Render(x, y);
			break;
		case 2:
			animations->Get(ID_ANI_CARD_PLANT)->Render(x, y);
			break;
		case 3:
			animations->Get(ID_ANI_CARD_MUSHROOM)->Render(x, y);
			break;
		}
	}
	else
	{
		animations->Get(ID_ANI_CARD)->Render(x, y);
	}
}


void CCard::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isMoving)
	{
		if (GetTickCount64() - moving_start < CARD_MOVING_TIME)
		{
			y += vy * CARD_MOVING_SPEED * dt;
		}
		else
		{
			if (moving_start != -1) {
				moving_start = -1;
				TextEffect* textEffect = new TextEffect("course clear !", x - 60, 275);
				TextEffect* textEffect2 = new TextEffect("you got a card", x - 76, 300);
				Image* image = new Image(ID_SPRITE_CARD + card_id, x - 76 + LETTER_WIDTH * 16, 300);
			}
			if (!isDeleted) HUD::GetInstance()->AddCard(card_id);

			Delete();
		}
	}
}

void CCard::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - CARD_BBOX_WIDTH / 2;
	t = y - CARD_BBOX_HEIGHT / 2;
	r = l + CARD_BBOX_WIDTH;
	b = t + CARD_BBOX_HEIGHT;
}

void CCard::StartMovingUp()
{
	if (isMoving) return;

	vy = -1;
	moving_start = GetTickCount64();
	isMoving = true;

	std::random_device rd;                         // nguồn random thực
	std::mt19937 gen(rd());                        // Mersenne Twister engine
	std::uniform_int_distribution<> dis(1, 3);    // phân phối đều từ 0 đến 99

	card_id = dis(gen);
}
