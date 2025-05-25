#pragma once
#include "UIElement.h"

using namespace std;

#define ID_SPRITE_CARD	500100

#define ID_SPRITE_CARD_STAR	500101
#define ID_SPRITE_CARD_PLANT	500102
#define ID_SPRITE_CARD_MUSHROOM	500103

#define CARD_WIDTH 24;

class CardUI : public CUIElement
{
private:
	vector<int> card_ids;
public:
	CardUI(float x, float y) : CUIElement(x, y)
	{
		for (int i = 0; i < 3; i++)
		{
			card_ids.push_back(-1); // Initialize with -1 to indicate no card
		}
	}

	void Render(float x, float y);
	void AddCard(int id)
	{
		for (int i = 0; i < 3; i++)
		{
			if (card_ids[i] == -1)
			{
				card_ids[i] = id;
				return;
			}
		}
	}
};
