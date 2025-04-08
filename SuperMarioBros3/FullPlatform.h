#pragma once
#include "Platform.h"
class CFullPlatform :
    public CPlatform
{
public:
    virtual int IsDirectionColliable(float nx, float ny) { return 1; };
    CFullPlatform(float x, float y,
        float cell_width, float cell_height, int length,
        int sprite_id_begin, int sprite_id_middle, int sprite_id_end) :CPlatform(x, y,
            cell_width, cell_height, length,
            sprite_id_begin, sprite_id_middle, sprite_id_end) {
    };

};

