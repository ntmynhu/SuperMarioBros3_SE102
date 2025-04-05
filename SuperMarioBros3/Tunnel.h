#pragma once

#include "GameObject.h"

// 
// The most popular type of object in Mario! 
// 
class CTunnel : public CGameObject
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
		int sprite_id_begin, int sprite_id_middle, int sprite_id_end, int sprite_id_begin_b, int sprite_id_middle_b, int sprite_id_end_b) :CGameObject(x, y)
	{
		this->length = length;
		this->cellWidth = cell_width;
		this->cellHeight = cell_height;
		this->spriteIdBeginA = sprite_id_begin;
		this->spriteIdMiddleA = sprite_id_middle;
		this->spriteIdEndA = sprite_id_end;
		this->spriteIdBeginB = sprite_id_begin_b;
		this->spriteIdMiddleB = sprite_id_middle_b;
		this->spriteIdEndB = sprite_id_end_b;
	}

	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();
};

typedef CTunnel* LPTUNNEL;