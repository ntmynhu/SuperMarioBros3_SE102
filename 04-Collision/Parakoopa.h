#pragma once
#include "Koopa.h"


#define ID_ANI_PARA_KOOPA_WALKING 5010
#define ID_ANI_PARA_KOOPA_DIE 5011
#define ID_ANI_PARA_KOOPA_WING 5012
#define ID_ANI_PARA_KOOPA_FLY 5013

#define PARA_KOOPA_FLY_SPEED_Y 0.3f

#define PARA_KOOPA_STATE_HASWING 600

class CParakoopa : public CKoopa
{
protected:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

	//virtual void Render();
public:
	CParakoopa(float x, float y) : CKoopa(x, y) {
		this->ay = KOOPA_GRAVITY*0.6f;
		SetState(PARA_KOOPA_STATE_HASWING);
	};
	bool HasWing() { return (state == PARA_KOOPA_STATE_HASWING); }
	virtual void TakeJumpDamage();
};
