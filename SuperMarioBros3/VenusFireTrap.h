#pragma once
#include "Plant.h"
#include "FireBall.h"
#define VENUS_BBOX_WIDTH 16
#define VENUS_BBOX_HEIGHT 20

#define VENUS_DOWN_TIME_OUT 1500
#define VENUS_UP_TIME_OUT 1500
#define VENUS_FIRE_TIME_OUT 500

#define ID_ANI_VENUS_MOVING_UP_LEFT 7100
#define ID_ANI_VENUS_MOVING_DOWN_LEFT 7101
#define ID_ANI_VENUS_MOVING_UP_RIGHT 7102
#define ID_ANI_VENUS_MOVING_DOWN_RIGHT 7103

#define ID_ANI_VENUS_UP_LEFT 7104
#define ID_ANI_VENUS_DOWN_LEFT 7105
#define ID_ANI_VENUS_UP_RIGHT 7106
#define ID_ANI_VENUS_DOWN_RIGHT 7107

#define VENUS_FIRE_RANGE 150

class CVenusFireTrap :
    public CPlant
{
protected:
    bool isLeft = false, isUp = false, isFire = false;
    float flowerOffsetY;
    CFireBall* fireball = NULL;
    virtual float GetFireDegree();
    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    virtual void Render();
public:

    CVenusFireTrap(float x, float y, CFireBall* fireball) :CPlant(x, y) {
        maxY = y;
        minY = maxY - HIDE_OFFSET - VENUS_BBOX_HEIGHT;
        this->fireball = fireball;
        flowerOffsetY = VENUS_BBOX_HEIGHT / 4;
    }
    virtual void SetState(int state);
};