#pragma once

#include "GameObject.h"

/*
	Object that triggers scene switching
*/

#define EFFECT_DELAY 1000
class CPortal : public CGameObject
{
	int scene_id;	// target scene to switch to 

	float width;
	float height; 

	float out_x;
	float out_y;

	ULONGLONG switch_start = -1;

	float effect_play = -1;
	int delay = 0;
	
	LPGAMEOBJECT posObj;
public:
	CPortal(float l, float t, float r, float b, int scene_id, float out_x = -1, float out_y = -1, int delay = 0);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void SwitchScene(LPGAMEOBJECT obj = NULL);
	void RenderBoundingBox(void);
	
	void GetOutPos(float& x, float& y) {
		x = out_x;
		y = out_y;
	}
	int GetSceneId() { return scene_id;  }
	int IsCollidable() { return 1; }
	int IsBlocking() { return 0; }
	int IsOverlappable() { return 1; }
};