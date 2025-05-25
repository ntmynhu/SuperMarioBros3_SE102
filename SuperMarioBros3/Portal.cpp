#include "Portal.h"
#include "Game.h"
#include "Textures.h"

CPortal::CPortal(float l, float t, float r, float b, int scene_id, float out_x, float out_y, int delay )
{
	this->scene_id = scene_id;
	x = l; 
	y = t;
	width = r - l;
	height = b - t;
	this->out_x = out_x;
	this->out_y = out_y;
	this->delay = delay;
}

void CPortal::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);

	CGame::GetInstance()->Draw(x - cx, y - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}

void CPortal::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	if (switch_start != -1) {
		if (GetTickCount64() - switch_start > delay) {
			CGame::GetInstance()->InitiateSwitchScene(GetSceneId());
			switch_start = -1;
		}
	}
}
void CPortal::Render()
{
	//RenderBoundingBox();
}

void CPortal::SwitchScene() {
	if (delay == 0) {
		CGame::GetInstance()->InitiateSwitchScene(GetSceneId());
		return;
	}
	if (switch_start == -1)
		switch_start = GetTickCount64();
}
void CPortal::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x - width/2;
	t = y - height/2;
	r = x + width/2;
	b = y + height/2;
}