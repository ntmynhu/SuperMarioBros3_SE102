#pragma once
#include "Goomba.h"

#define ID_ANI_PARA_GOOMBA_WALKING 5100
#define ID_ANI_PARA_GOOMBA_DIE 5101
#define ID_ANI_PARA_GOOMBA_DIE_UPSIDE_DOWN 5102
#define ID_ANI_PARA_GOOMBA_WING 5103
#define ID_ANI_PARA_GOOMBA_FLY 5104
#define ID_ANI_PARA_GOOMBA_HOP 5105

#define PARA_GOOMBA_FLY_SPEED_Y 0.2f
#define PARA_GOOMBA_SMALL_JUMP_SPEED_Y 0.2f
#define PARA_GOOMBA_SMALL_JUMP_LIMIT 3
#define PARA_GOOMBA_WALK_TIMEOUT 2000

#define PARA_GOOMBA_STATE_HASWING 300

#define PARA_GOOMBA_BBOX_WIDTH 20
#define PARA_GOOMBA_BBOX_HEIGHT 22

class CParagoomba : public CGoomba
{
protected:
	ULONGLONG walk_start;
	bool isFlying;
	int jumpCount;
	
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Render();
	virtual void ResetPos();
	
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
