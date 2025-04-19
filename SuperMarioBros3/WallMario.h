#pragma once
#include "Wall.h"

class CWallMario :
    public CWall
{
protected:
    virtual int IsBlocking() { return 0; }
    virtual int IsBlocking(LPGAMEOBJECT objSrc);
    virtual int IsCollidable() { return 1; };
public:
    CWallMario(float x, float y,
        float cell_width, float cell_height, int length,
        int sprite_id_begin, int sprite_id_middle, int sprite_id_end) :CWall(x, y,
            cell_width, cell_height, length,
            sprite_id_begin, sprite_id_middle, sprite_id_end) {
    };
    
};

