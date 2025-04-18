#pragma once
#include "Plant.h"

#define PIRANHA_BBOX_WIDTH 16
#define PIRANHA_BBOX_HEIGHT 18

#define PIRANHA_DOWN_TIME_OUT 2000
#define PIRANHA_UP_TIME_OUT 2000

#define ID_ANI_PIRANHA 7000
class CPiranhaPlant :
    public CPlant
{
protected:
    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    virtual void Render();
public:

    CPiranhaPlant(float x, float y) :CPlant(x, y) {
        maxY = y;
        minY = maxY - HIDE_OFFSET - PIRANHA_BBOX_HEIGHT;
    }
};

