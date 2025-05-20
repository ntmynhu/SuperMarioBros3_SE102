#pragma once
#include "UIElement.h"

class CoinUI : public CUIElement
{
public:
	CoinUI(float x, float y) : CUIElement(x, y) {}
	void Render(float x, float y);
};

