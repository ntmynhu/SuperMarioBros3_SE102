#include "Block.h"
#include "Brick.h"
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

void CBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BLOCK_BBOX_WIDTH / 2;
	t = y - BLOCK_BBOX_HEIGHT / 2;
	r = l + BLOCK_BBOX_WIDTH;
	b = t + BLOCK_BBOX_HEIGHT;
}
