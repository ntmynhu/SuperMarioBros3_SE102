#pragma once

#include "GameObject.h"

/*
	Object that triggers scene switching
*/
class CPortal : public CGameObject
{
	int scene_id;	// target scene to switch to 

	float width;
	float height; 

	float out_x;
	float out_y;
public:
	CPortal(float l, float t, float r, float b, int scene_id, float out_x = -1, float out_y = -1);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);

	void RenderBoundingBox(void);
	
	void GetOutPos(float& x, float& y) {
		x = out_x;
		y = out_y;
	}
	int GetSceneId() { return scene_id;  }
	int IsBlocking() { return 0; }
};