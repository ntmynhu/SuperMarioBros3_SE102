#pragma once

#include "MarioForm.h"

#define ID_ANI_MARIO_IDLE_RIGHT 400
#define ID_ANI_MARIO_IDLE_LEFT 401
#define ID_ANI_MARIO_PIPE 402

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

#define ID_ANI_MARIO_BIG_KICK_RIGHT 1050
#define ID_ANI_MARIO_BIG_KICK_LEFT 1051

#define ID_ANI_MARIO_BIG_FULL_POWER_JUMP_RIGHT 850
#define ID_ANI_MARIO_BIG_FULL_POWER_JUMP_LEFT 851

#define ID_ANI_MARIO_BIG_FULL_POWER_RUN_RIGHT 820
#define ID_ANI_MARIO_BIG_FULL_POWER_RUN_LEFT 821

#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 24
#define MARIO_BIG_SITTING_BBOX_WIDTH  14
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16

#define MARIO_BIG_HOLD_OFFSET_X 12
#define MARIO_BIG_HOLD_OFFSET_Y 1

#define ID_ANI_FROM_SMALL_TO_BIG_LEFT 1901
#define ID_ANI_FROM_SMALL_TO_BIG_RIGHT 1900

#define ID_ANI_MARIO_BIG_IDLE_HOLDING_LEFT 451
#define ID_ANI_MARIO_BIG_IDLE_HOLDING_RIGHT 450

#define ID_ANI_MARIO_BIG_WALKING_HOLDING_LEFT 551
#define ID_ANI_MARIO_BIG_WALKING_HOLDING_RIGHT 550

#define ID_ANI_MARIO_BIG_RUNNING_HOLDING_LEFT 651
#define ID_ANI_MARIO_BIG_RUNNING_HOLDING_RIGHT 650

#define ID_ANI_MARIO_BIG_FULL_POWER_RUN_HOLDING_LEFT 825
#define ID_ANI_MARIO_BIG_FULL_POWER_RUN_HOLDING_RIGHT 827

#define ID_ANI_MARIO_BIG_JUMP_HOLDING_LEFT 751
#define ID_ANI_MARIO_BIG_JUMP_HOLDING_RIGHT 750

#define MARIO_SMALL_TO_BIG_DURATION 1000

class CMario;

class CMarioBig : public CMarioForm
{
protected:
	bool isSitting = false;
public:
	void Update(DWORD dt, CMario* mario, vector<LPGAMEOBJECT>* coObjects);
	int GetAniId(CMario* mario);
	void SetState(int state, CMario* mario);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom, CMario* mario);
	int GetLevel() const;
	int GetUpStateChangeTime() { return MARIO_SMALL_TO_BIG_DURATION; }
	void GetHoldOffset(float& ox, float& oy) { ox = MARIO_BIG_HOLD_OFFSET_X; oy = MARIO_BIG_HOLD_OFFSET_Y; }
	void OnTakeDamage(CMario* mario);
	void OnSitRelease(int state, CMario* mario);
	int GetKickAniId(CMario* mario);
	float GetHeight() {
		if (isSitting)
		{
			return MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else
		{
			return MARIO_BIG_BBOX_HEIGHT;
		}
	}
};

