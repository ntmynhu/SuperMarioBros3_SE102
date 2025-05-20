#pragma once
#include "RedKoopa.h"
#include "Parakoopa.h"

#define ID_ANI_RED_PARA_KOOPA_FLY 6300
#define ID_ANI_RED_PARA_KOOPA_FLY_RIGHT 6301

#define RED_PARA_KOOPA_FLY_SMALL_SPEED_Y 0.0000001f
#define RED_PARA_KOOPA_FLY_SPEED_Y 0.05f

#define RED_PARA_KOOPA_FLY_RANGE 100
#define RED_PARA_KOOPA_SWITCH_DELAY 500
class CRedParakoopa :
    public CRedKoopa
{
protected:
	float top_bound;
	float bot_bound;
	ULONGLONG switch_start = -1;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void ResetPos();
public:
	CRedParakoopa(float x, float y, float fly_range = RED_PARA_KOOPA_FLY_RANGE) : CRedKoopa(x, y) {
		this->ay = 0;
		this->vx = 0;
		this->vy = -RED_PARA_KOOPA_FLY_SPEED_Y;

		this->bot_bound = init_y + fly_range;
		this->top_bound = init_y;

		SetState(PARA_KOOPA_STATE_HASWING);
	};
	bool HasWing() { return (state == PARA_KOOPA_STATE_HASWING); }
	virtual void TakeJumpDamage();
};

