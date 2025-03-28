#include "MarioRacoon.h"
#include "Mario.h"

void CMarioRacoon::Update(DWORD dt, CMario* mario, vector<LPGAMEOBJECT>* coObjects)
{
	CMarioBig::Update(dt, mario, coObjects);
}

int CMarioRacoon::GetAniId(CMario* mario)
{
	return CMarioBig::GetAniId(mario);
}

void CMarioRacoon::SetState(int state, CMario* mario)
{
	CMarioBig::SetState(state, mario);
}

void CMarioRacoon::GetBoundingBox(float& left, float& top, float& right, float& bottom, CMario* mario)
{
	CMarioBig::GetBoundingBox(left, top, right, bottom, mario);
}

int CMarioRacoon::GetLevel() const
{
	return MARIO_LEVEL_RACOON;
}

void CMarioRacoon::OnTakeDamage(CMario* mario)
{
	mario->ChangeForm(MARIO_LEVEL_BIG);
	mario->StartUntouchable();
}
