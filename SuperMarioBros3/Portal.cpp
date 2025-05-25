#include "Portal.h"
#include "Game.h"
#include "Textures.h"
#include "EffectManager.h"
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
			if (effect_play == -1) {
				FadeEffect* fade = new FadeEffect(0, 0, FADE_IN_STATE);
				effect_play = 1;
			}
			if (GetTickCount64() - switch_start > delay + EFFECT_DELAY) {
				if (posObj != NULL && !posObj->IsDeleted()) {
					if (out_x >= 0 && out_y >= 0) {
						posObj->SetPosition(out_x, out_y);
					}
				}

				CGame::GetInstance()->InitiateSwitchScene(GetSceneId());
				switch_start = -1;
				effect_play = -1;
				posObj = NULL;
			}
		}
	}
}
void CPortal::Render()
{
	//RenderBoundingBox();
}

void CPortal::SwitchScene(LPGAMEOBJECT obj) {
	if (switch_start == -1) {
		posObj = obj;
		switch_start = GetTickCount64();
		effect_play = -1;
	}
}
void CPortal::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x - width/2;
	t = y - height/2;
	r = x + width/2;
	b = y + height/2;
}