#pragma once
#include "GameObject.h"
#include "debug.h"
#define FALL_CENSOR_GRAVITY 0.2f
#define CENSOR_BBOX_WIDTH 16.0f
#define CENSOR_BBOX_HEIGHT 24.0f
class CKoopa;
class CFallCensor :
    public CGameObject
{
protected:
    bool isOnPlatform;
    virtual int IsCollidable() { return 1; };
    virtual int IsBlocking() { return 0; }
    void OnNoCollision(DWORD dt);

    void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    void OnCollisionWith(LPCOLLISIONEVENT e);
    
public:
    CFallCensor(float x, float y) : CGameObject(x, y){
        vy = FALL_CENSOR_GRAVITY;
        isOnPlatform = true;
    }
    void SetX(float x) { this->x = x; }
    bool IsOnPlatform() {
        return isOnPlatform;
    }
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    virtual void Render() { }
};

