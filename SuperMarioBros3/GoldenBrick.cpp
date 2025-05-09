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
		aniId = ID_ANI_GOLDEN_BRICK;
	}
	else
	{
		aniId = ID_ANI_BLOCK_EMPTY;
	}

	animations->Get(aniId)->Render(x, y);
}

void CGoldenBrick::TriggerAction()
{
	if (isEmpty) return;

	switch (itemId)
	{
	case ID_ITEM_COIN:
		particle->SetTrigger();
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
		particle->RemoveParticle();
		break;
	}

	isEmpty = true;
	this->Delete();
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
			}

			break;
		}
	}

	isEmpty = true;
}



