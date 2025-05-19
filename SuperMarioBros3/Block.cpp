#include "Block.h"
#include "Brick.h"
#include "Koopa.h"
#include "Mario.h"
#include "Game.h"
#include "PlayScene.h"

void CBlock::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_BLOCK_EMPTY)->Render(x, y);
}

void CBlock::SetMario() {
	CPlayScene* scene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
	if (scene) {
		CMario* mario = dynamic_cast<CMario*>(scene->GetPlayer());
		if (mario) {
			this->mario = mario;
		}
	}
}

void CBlock::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	if (!mario) {
		SetMario();
	}
	if (mario->IsDeleted()) mario = NULL;
	CGameObject::Update(dt, coObjects);
}
void CBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BLOCK_BBOX_WIDTH / 2;
	t = y - BLOCK_BBOX_HEIGHT / 2;
	r = l + BLOCK_BBOX_WIDTH;
	b = t + BLOCK_BBOX_HEIGHT;
}

//void CBlock::OnCollisionWith(LPCOLLISIONEVENT e)
//{
//	if (!IsBouncing()) return;
//	if (dynamic_cast<CKoopa*>(e->obj))
//		OnCollisionWithKoopa(e);
//}
//void CBlock::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
//{
//	CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);
//
//	if (koopa->GetState() != KOOPA_STATE_DEFEND_SLIDING && e->ny > 0) {
//		if (IsBouncing()) {
//			koopa->TakeBlockBounceDamage(x);
//		}
//	}
//}