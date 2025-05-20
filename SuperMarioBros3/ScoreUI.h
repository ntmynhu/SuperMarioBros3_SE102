#pragma once
#include "UIElement.h"

class ScoreUI : public CUIElement
{
public:
	ScoreUI(float x, float y) :CUIElement(x, y) {}
	void Render(float x, float y);
};

