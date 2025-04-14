#pragma once

#include "Wall.h"

// 
// The most popular type of object in Mario! 
// 
class CTunnel : public CWall
{
protected:
	int length;				// Unit: cell 
	float cellWidth;
	float cellHeight;
	int spriteIdBeginA, spriteIdMiddleA, spriteIdEndA;
	int spriteIdBeginB, spriteIdMiddleB, spriteIdEndB;

public:
	CTunnel(float x, float y,
		float cell_width, float cell_height, int length,
		int sprite_id_begin, int sprite_id_middle, int sprite_id_end) :CWall(x, y,
			cell_width, cell_height, length,
			sprite_id_begin, sprite_id_middle, sprite_id_end)
	{	}
};

typedef CTunnel* LPTUNNEL;