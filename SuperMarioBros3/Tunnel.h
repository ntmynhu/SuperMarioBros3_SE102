#pragma once

#include "Wall.h"

// 
// The most popular type of object in Mario! 
// 
#define TUNNEL_ENTERABLE_OFFSET 7
class CMario;
class CTunnel : public CWall
{
protected:
	int isEnterable; //0 as cant, 1 as can
	int length;				// Unit: cell 
	CMario* mario;
	
	bool hasMarioInside = false;
	int direction; //1 as Up, -1 as Down
	virtual void SetMario();
public:
	CTunnel(float x, float y,
		float cell_width, float cell_height, int length,
		int sprite_id_begin, int sprite_id_middle, int sprite_id_end, int enterable = 0, int direction = 1) :CWall(x, y,
			cell_width, cell_height, length,
			sprite_id_begin, sprite_id_middle, sprite_id_end)
	{
		this->isEnterable = enterable;
		this->direction = direction;
	}
	int IsEnterable() { return isEnterable; }
	int GetDirection() { return direction; }
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	bool CheckEnterableRange(float o_x) {
		return o_x >= x - TUNNEL_ENTERABLE_OFFSET && o_x <= x + TUNNEL_ENTERABLE_OFFSET;
	}
};
