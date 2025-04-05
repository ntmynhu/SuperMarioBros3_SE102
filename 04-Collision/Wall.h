#pragma once
#include "FullPlatform.h"
class CWall :
    public CFullPlatform
{
public:
    CWall(float x, float y,
        float cell_width, float cell_height, int length,
        int sprite_id_begin, int sprite_id_middle, int sprite_id_end) :CFullPlatform(x, y,
            cell_width, cell_height, length,
            sprite_id_begin, sprite_id_middle, sprite_id_end) {
    };
    void Render();
    void RenderBoundingBox();
    void GetBoundingBox(float& l, float& t, float& r, float& b);
};

