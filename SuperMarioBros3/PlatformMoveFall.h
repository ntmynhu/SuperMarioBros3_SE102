#pragma once
#include "FullPlatform.h"

#define PLATFORM_MOVE_VX 0.037f
#define PLATFORM_MOVE_VY 0.1f

#define PLATFORM_FALL_VY 0.02f
#define PLATFORM_GRAVITY 0.0003f

class CMario;
class CPlatformMoveFall :
    public CFullPlatform
{
protected:
    CMario* mario;
    virtual int IsBlocking() { return 0; }
    virtual int IsBlocking(LPGAMEOBJECT objSrc);
    virtual int IsCollidable() { return 1; };

    void OnCollisionWith(LPCOLLISIONEVENT e);
    void OnCollisionWithMario(LPCOLLISIONEVENT e);

    bool isFalling = false;
    bool hasMario = false;
    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
public:
    CPlatformMoveFall(float x, float y,
        float cell_width, float cell_height, int length,
        int sprite_id_begin, int sprite_id_middle, int sprite_id_end,
        int Xdir = 0, int Ydir = 0) :CFullPlatform(x, y,
            cell_width, cell_height, length,
            sprite_id_begin, sprite_id_middle, sprite_id_end) {
        mario = NULL;

        this->vx = Xdir * PLATFORM_MOVE_VX;
        this->vy = -Ydir * PLATFORM_MOVE_VY;
    };
    void SetMario();
    void Render()
    {
        CFullPlatform::Render();
        //RenderBoundingBox();
    };

};

