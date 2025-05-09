#pragma once
#include "SuperMushroom.h"

#define ID_ANI_ONE_UP_MUSHROOM 100011

class OneUpMushroom : public CSuperMushroom
{
public:
	OneUpMushroom(float x, float y) : CSuperMushroom(x, y) {}
	virtual void Render();
};

