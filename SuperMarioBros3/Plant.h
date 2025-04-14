#pragma once
#include "GameObject.h"
#include "Mario.h"
#include "PlayScene.h"
#include "Game.h"

#define PLANT_DIE_TIME_OUT 200

#define PLANT_VY 0.05f

#define PLANT_STATE_DIE 1000
#define PLANT_STATE_UP 100
#define PLANT_STATE_MOVING 200
#define PLANT_STATE_HIDE 300

#define HIDE_OFFSET 4
#define PLANT_NOT_UP_RANGE 30

class CPlant :
    public CGameObject
{
protected:
    ULONGLONG up_start;
    ULONGLONG down_start;
	ULONGLONG die_start;

	CMario* mario = NULL;

	float maxY;
	float minY;

	int isAbleToUp; //-1, 0, 1 for face left, can't, face right

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render() {};
	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }

	virtual void CheckAbleToUp() {
		if (!mario) return;
		float marioX, marioY;

		mario->GetPosition(marioX, marioY);
		if (abs(x - marioX) <= PLANT_NOT_UP_RANGE) {
			isAbleToUp = 0;
		}
		else {
			if (x < marioX) //on the left of Mario => facing right
				isAbleToUp = 1;
			else
				isAbleToUp = -1;
		}
	}
	virtual void SetMario() {
		CPlayScene* scene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
		if (scene) {
			CMario* mario = dynamic_cast<CMario*>(scene->GetPlayer());
			if (mario) {
				this->mario = mario;
			}
		}
	}
public:
	CPlant(float x, float y) : CGameObject(x, y) {
		maxY = 0;
		minY = 0;
		up_start = -1;
		down_start = -1;
		die_start = -1;
		isAbleToUp = 0;
		SetState(PLANT_STATE_HIDE);
	};
	virtual void SetState(int state);
	virtual void SetIsAbleToUp(bool isAbleToUp) {
		this->isAbleToUp = isAbleToUp;
	}
	virtual void TakeAttackDamage() {};
};

