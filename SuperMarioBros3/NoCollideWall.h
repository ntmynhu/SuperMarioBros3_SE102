#pragma once
#include "Wall.h"
class CNoCollideWall :
    public CWall
{
    virtual int IsCollidable() { return 0; };
    virtual int IsBlocking() { return 0; }
    virtual int IsDirectionColliable(float nx, float ny) { return 0; }
public:
    CNoCollideWall(float x, float y,
        float cell_width, float cell_height, int length,
        int sprite_id_begin, int sprite_id_middle, int sprite_id_end) :CWall(x, y,
            cell_width, cell_height, length,
            sprite_id_begin, sprite_id_middle, sprite_id_end) {
    };
};

