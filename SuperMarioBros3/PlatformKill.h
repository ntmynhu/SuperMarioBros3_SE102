#pragma once
#include "NoCollidePlatform.h"
class CPlatformKill :
    public CFullPlatform
{
protected:
    virtual int IsCollidable() { return 1; };
    virtual int IsOverlappable() { return 1; };
    virtual int IsBlocking() { return 0; }
public:
    CPlatformKill(float x, float y,
        float cell_width, float cell_height, int length,
        int sprite_id_begin, int sprite_id_middle, int sprite_id_end) :CFullPlatform(x, y,
            cell_width, cell_height, length,
            sprite_id_begin, sprite_id_middle, sprite_id_end) {
    };
    void Render() {
        //CFullPlatform::Render();
        RenderBoundingBox();
    }
};

