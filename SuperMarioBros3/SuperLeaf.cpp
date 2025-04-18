#include "SuperLeaf.h"

void CSuperLeaf::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniID = nx > 0 ? ID_ANI_SUPER_LEAF_RIGHT : ID_ANI_SUPER_LEAF_LEFT;
	animations->Get(aniID)->Render(x, y);
}

void CSuperLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
}

void CSuperLeaf::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - SUPER_LEAF_BBOX_WIDTH / 2;
	t = y - SUPER_LEAF_BBOX_HEIGHT / 2;
	r = l + SUPER_LEAF_BBOX_WIDTH;
	b = t + SUPER_LEAF_BBOX_HEIGHT;
}

void CSuperLeaf::AppearFromQuestionBlock()
{
}
