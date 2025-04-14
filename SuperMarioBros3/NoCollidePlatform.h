#pragma once
#include "FullPlatform.h"
class CNoCollidePlatform :
    public CFullPlatform
{
	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 0; }
	virtual int IsDirectionColliable(float nx, float ny) { return 0; }
public:
    CNoCollidePlatform(float x, float y,
        float cell_width, float cell_height, int length,
        int sprite_id_begin, int sprite_id_middle, int sprite_id_end) :CFullPlatform(x, y,
            cell_width, cell_height, length,
            sprite_id_begin, sprite_id_middle, sprite_id_end) {
    };
};

