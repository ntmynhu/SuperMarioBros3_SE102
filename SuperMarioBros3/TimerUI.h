#pragma once
#include "UIElement.h"

#define ID_SPRITE_TIMER_0	301000
#define ID_SPRITE_TIMER_1	301001
#define ID_SPRITE_TIMER_2	301002
#define ID_SPRITE_TIMER_3	301003
#define ID_SPRITE_TIMER_4	301004
#define ID_SPRITE_TIMER_5	301005
#define ID_SPRITE_TIMER_6	301006
#define ID_SPRITE_TIMER_7	301007
#define ID_SPRITE_TIMER_8	301008
#define ID_SPRITE_TIMER_9	301009

#define NUMBER_WIDTH	7

class TimerUI : public CUIElement
{
public:
	TimerUI(float x, float y) :CUIElement(x, y) {}
	void Render(float x, float y);
};

