#pragma once
#include "GameObject.h"

#define TAIL_STATE_NORMAL 0
#define TAIL_STATE_WHACKED 1

#define TAIL_BBOX_WIDTH 16
#define TAIL_BBOX_HEIGHT 3
class CTail :
    public CGameObject
{
protected:
    virtual int IsCollidable() { return 1; };
    virtual int IsBlocking() { return 0; }
    virtual int IsOverlappable() { return 1; }

    void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    void OnCollisionWith(LPCOLLISIONEVENT e);
    void OnCollisionWithEnemy(LPCOLLISIONEVENT e);
    void OnCollisionWithPlant(LPCOLLISIONEVENT e);
    void OnCollisionWithBlock(LPCOLLISIONEVENT e);
public:
    CTail(float x, float y) : CGameObject(x, y) { }
    void SetX(float x) { this->x = x; }
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    virtual void Render() { 
        //RenderBoundingBox(); 
    }
};

