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

class CMario;

class CMarioBig : public CMarioForm
{
private:
	bool isSitting = false;
public:
	void Update(DWORD dt, CMario* mario, vector<LPGAMEOBJECT>* coObjects);
	int GetAniId(CMario* mario);
	void SetState(int state, CMario* mario);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom, CMario* mario);
	int GetLevel() const;
	void OnTakeDamage(CMario* mario);
};

