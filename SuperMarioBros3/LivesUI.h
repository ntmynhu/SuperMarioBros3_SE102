#pragma once
#include "UIElement.h"

class LivesUI : public CUIElement
{
public:
	LivesUI(float x, float y) :CUIElement(x, y) {}
	void Render(float x, float y);
};

class WorldUI : public CUIElement
{
public:
	WorldUI(float x, float y) :CUIElement(x, y) {}
	void Render(float x, float y);
};


