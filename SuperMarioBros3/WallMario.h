#pragma once
#include "Wall.h"
#include "Mario.h"
#include "debug.h"

class CMario;
class CWallMario :
    public CWall
{
protected:
    CMario* mario;
    int side; // -1 as left, 1 as right
    virtual int IsBlocking() { return 0; }
    virtual int IsBlocking(LPGAMEOBJECT objSrc);
    virtual int IsCollidable() { return 1; };
    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
        x += vx * dt;
    };
public:
    CWallMario(float x, float y,
        float cell_width, float cell_height, int length,
        int side = 0) :CWall(x, y,
            cell_width, cell_height, length,
            -1, -1, -1) {
        mario = NULL;
        this->side = side;
        this->vx = 0;
    };
    void GetBoundX(float& x) {
        if (side == -1)
            x = this->x + cellWidth;
        else if (side == 1)
            x = this->x - cellWidth;
        else x = this->x;
    }
    void Render()
    {
        //RenderBoundingBox();
    };
    
};

