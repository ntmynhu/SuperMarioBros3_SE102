#include "Wall.h"
#include "Sprite.h"
#include "Sprites.h"

#include "Textures.h"
#include "Game.h"

void CWall::RenderBoundingBox()
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

	float yy = y - this->cellHeight / 2 + rect.bottom / 2;

	CGame::GetInstance()->Draw(x - cx, yy - cy, bbox, rect.left, rect.top = 0, rect.right - 1, rect.bottom - 1, 0.25f);
}

void CWall::Render()
{
	if (this->length <= 0) return;
	float yy = y;
	CSprites* s = CSprites::GetInstance();

	s->Get(this->spriteIdBegin)->Draw(x, yy);
	yy += this->cellHeight;
	for (int i = 1; i < this->length - 1; i++)
	{
		s->Get(this->spriteIdMiddle)->Draw(x, yy);
		yy += this->cellHeight;
	}
	if (length > 1)
		s->Get(this->spriteIdEnd)->Draw(x, yy);


	RenderBoundingBox();

}

void CWall::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	float cellWidth_div_2 = this->cellWidth / 2;
	l = x - cellWidth_div_2;
	t = y - this->cellHeight / 2;
	r = l + this->cellWidth;
	b = t + this->cellHeight * this->length;
}