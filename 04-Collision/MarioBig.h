#pragma once
#include "MarioForm.h"

#define ID_ANI_MARIO_IDLE_RIGHT 400
#define ID_ANI_MARIO_IDLE_LEFT 401

#define ID_ANI_MARIO_WALKING_RIGHT 500
#define ID_ANI_MARIO_WALKING_LEFT 501

#define ID_ANI_MARIO_RUNNING_RIGHT 600
#define ID_ANI_MARIO_RUNNING_LEFT 601

#define ID_ANI_MARIO_JUMP_WALK_RIGHT 700
#define ID_ANI_MARIO_JUMP_WALK_LEFT 701

#define ID_ANI_MARIO_JUMP_RUN_RIGHT 800
#define ID_ANI_MARIO_JUMP_RUN_LEFT 801

#define ID_ANI_MARIO_SIT_RIGHT 900
#define ID_ANI_MARIO_SIT_LEFT 901

#define ID_ANI_MARIO_BRACE_RIGHT 1000
#define ID_ANI_MARIO_BRACE_LEFT 1001

class MarioBig : public MarioForm
{
private:
	bool isSitting = false;
public:
	void Update(DWORD dt, CMario* mario, vector<LPGAMEOBJECT>* coObjects) override;
	int GetAniId(CMario* mario) override;
	void SetState(int state, CMario* mario) override;
	void GetBoundingBox(float& left, float& top, float& right, float& bottom, CMario* mario) override;
	int GetLevel() const override;
	void OnTakeDamage(CMario* mario) override;
};

