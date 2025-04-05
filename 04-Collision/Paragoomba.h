#pragma once
#include "Goomba.h"

#define ID_ANI_PARA_GOOMBA_WALKING 5010
#define ID_ANI_PARA_GOOMBA_DIE 5011
#define ID_ANI_PARA_GOOMBA_WING 5012
#define ID_ANI_PARA_GOOMBA_FLY 5013

#define PARA_GOOMBA_FLY_SPEED_Y 0.4f
#define PARA_GOOMBA_SMALL_JUMP_SPEED_Y 0.2f
#define PARA_GOOMBA_SMALL_JUMP_LIMIT 3
#define PARA_GOOMBA_WALK_TIMEOUT 2000

#define PARA_GOOMBA_STATE_HASWING 300

class CParagoomba : public CGoomba
{
protected:
	ULONGLONG walk_start;
	bool isFlying;
	int jumpCount;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	
	//virtual void Render();
public:
	CParagoomba(float x, float y) : CGoomba(x, y) { 
		SetState(PARA_GOOMBA_STATE_HASWING);
		jumpCount = 0;
		isFlying = false;
		walk_start = -1; 
	};
	bool HasWing() { return (state == PARA_GOOMBA_STATE_HASWING); }
	virtual void TakeJumpDamage();
};
