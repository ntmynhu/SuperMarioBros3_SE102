#pragma once
#include "VenusFireTrap.h"

#define RED_VENUS_BBOX_HEIGHT 28

#define ID_ANI_RED_VENUS_MOVING_UP_LEFT 7200
#define ID_ANI_RED_VENUS_MOVING_DOWN_LEFT 7201
#define ID_ANI_RED_VENUS_MOVING_UP_RIGHT 7202
#define ID_ANI_RED_VENUS_MOVING_DOWN_RIGHT 7203

#define ID_ANI_RED_VENUS_UP_LEFT 7204
#define ID_ANI_RED_VENUS_DOWN_LEFT 7205
#define ID_ANI_RED_VENUS_UP_RIGHT 7206
#define ID_ANI_RED_VENUS_DOWN_RIGHT 7207
class CRedVenusFireTrap :
    public CVenusFireTrap
{
protected:
    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    virtual void Render();
public:

    CRedVenusFireTrap(float x, float y, CFireBall* fireball) :CVenusFireTrap(x, y, fireball) {
        minY = maxY - HIDE_OFFSET - RED_VENUS_BBOX_HEIGHT;
        flowerOffsetY = RED_VENUS_BBOX_HEIGHT / 3;
    }
};

