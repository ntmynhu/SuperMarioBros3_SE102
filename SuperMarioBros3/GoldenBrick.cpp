#include "GoldenBrick.h"
#include "Coin.h"
#include "BlueButton.h"
#include "OneUpMushroom.h"


void CGoldenBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (!isEmpty && !isBouncing)
	{
		aniId = active_ani_id;
	}
	else if (isBouncing && brick_stat == BRICK_STAT_NO_COLLIDE_Y) {
		aniId = active_ani_id;
	}
	else
	{
		aniId = ID_ANI_BLOCK_EMPTY;
	}
	if (isBrick)
		animations->Get(aniId)->Render(x, y);
}

void CGoldenBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!isEmpty)
	{
		if (isBrick) {
			if (item) {
				if (!item->IsDeleted())
					item->Deactivate();
				else
					item = NULL;
			}
		}
		if (particle) {
			if (!particle->IsDeleted())
				particle->Deactivate();
			else
				particle = NULL;
		}
	}

	if (GetTickCount64() - to_coin_start > BRICK_COIN_TURN_TIMEOUT && !isBrick)
	{
		BackToBrick();
	}

	if (isBouncing)
	{
		if (bouncing_start == 0) {
			bouncing_start = 1;
		}
		else if (bouncing_start == 1)
			y += vy * BLOCK_BOUNCING_SPEED * dt;

		if (y <= init_y - BLOCK_BOUNCING_HEIGHT)
		{
			vy = 1;
		}

		if (vy == 1 && y >= init_y)
		{
			vy = 0;
			isBouncing = false;
			y = init_y;
			bouncing_start = -1;
			SpawnItem();
		}
	}
	CBlock::Update(dt, coObjects);
	
}

void CGoldenBrick::TriggerAction(LPCOLLISIONEVENT e)
{
	if (isEmpty) return;
	if (e != NULL && brick_stat == BRICK_STAT_NO_COLLIDE_Y) {
		this->StartBouncing();
		return;
	}
	switch (itemId)
	{
	case ID_ITEM_COIN:
		particle->SetTrigger();
		isEmpty = true;
		this->Delete();
		item->Delete();
		break;
	case ID_ITEM_BLUE_BUTTON:
		this->StartBouncing();
		break;
	case ID_ITEM_ONE_UP_MUSHROOM:
		this->StartBouncing();
		break;
	}
}

void CGoldenBrick::TurnToCoin()
{
	switch (itemId)
	{
	case ID_ITEM_COIN:
		CCoin* coin = dynamic_cast<CCoin*>(item);
		if (coin) coin->Activate();
		to_coin_start = GetTickCount64();
		isBrick = 0;
		break;
	}
}

void CGoldenBrick::SpawnItem()
{
	if (!item || item->IsDeleted()) {
		item = NULL;
		return;
	}

	if (itemId2 != -1)
	{
		if (!item2 || item2->IsDeleted()) {
			item2 = NULL;
			return;
		}
	}

	switch (itemId)
	{
		case ID_ITEM_BLUE_BUTTON:
		{
			CBlueButton* blueButton = dynamic_cast<CBlueButton*>(item);
			if (blueButton != NULL)
			{
				blueButton->StartAppearing();
				isEmpty = true;
			}
			break;
		}
		case ID_ITEM_ONE_UP_MUSHROOM:
		{
			OneUpMushroom* oneUpMushroom = dynamic_cast<OneUpMushroom*>(item);
			if (oneUpMushroom != NULL)
			{
				float marioX, marioY;
				mario->GetPosition(marioX, marioY);
				oneUpMushroom->AppearFromQuestionBlock(marioX, y);
				isEmpty = true;
			}

			break;
		}
	}
}



