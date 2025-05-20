#pragma once
#include "UIElement.h"

class TimerUI : public CUIElement
{
public:
	TimerUI(float x, float y) :CUIElement(x, y) {}
	void Render(float x, float y);
};

