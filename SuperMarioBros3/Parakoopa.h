#pragma once
#include "Koopa.h"


#define ID_ANI_PARA_KOOPA_FLY 6200
#define ID_ANI_PARA_KOOPA_FLY_RIGHT 6201

#define PARA_KOOPA_FLY_SPEED_Y 0.20f

#define PARA_KOOPA_STATE_HASWING 600

class CParakoopa : public CKoopa
{
protected:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

	virtual void Render();
	virtual void ResetPos();
public:
	CParakoopa(float x, float y) : CKoopa(x, y) {
		this->ay = KOOPA_GRAVITY * 0.50f;
		SetState(PARA_KOOPA_STATE_HASWING);
	};
	bool HasWing() { return (state == PARA_KOOPA_STATE_HASWING); }
	virtual void TakeJumpDamage();
};
