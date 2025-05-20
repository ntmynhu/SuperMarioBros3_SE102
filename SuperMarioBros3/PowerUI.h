#pragma once
#include "UIElement.h"

class PowerUI : public CUIElement
{
public:
	PowerUI(float x, float y) :CUIElement(x, y) {}
	void Render(float x, float y);
};

