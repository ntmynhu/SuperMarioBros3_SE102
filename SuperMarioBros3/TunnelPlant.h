#pragma once
#include "Tunnel.h"
#include "Plant.h"
class CTunnelPlant :
    public CTunnel
{
protected:
	CPlant* plant;

public:
	CTunnelPlant(float x, float y,
		float cell_width, float cell_height, int length,
		int sprite_id_begin, int sprite_id_middle, int sprite_id_end, CPlant* plant) :CTunnel(x, y,
			cell_width, cell_height, length,
			sprite_id_begin, sprite_id_middle, sprite_id_end)
	{
		this->plant = plant;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {}
};

