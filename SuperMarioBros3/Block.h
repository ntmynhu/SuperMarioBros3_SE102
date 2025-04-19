#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BLOCK_EMPTY 81100
#define BLOCK_WIDTH 16
#define BLOCK_BBOX_WIDTH 16
#define BLOCK_BBOX_HEIGHT 16

class CMario;
class CBlock : public CGameObject
{
protected:
	CMario* mario = NULL;
	virtual void SetMario();
public:
	CBlock(float x, float y) : CGameObject(x, y) {}
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {
		if (!mario) {
			SetMario();
		}
		CGameObject::Update(dt, coObjects);
	}
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void TriggerAction() {}
};

