#include "FallCensor.h"
#include "debug.h"
void CFallCensor::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CFallCensor::OnNoCollision(DWORD dt)
{
    isOnPlatform = false;
    y += vy * dt;
};

void CFallCensor::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
    left = x - CENSOR_BBOX_WIDTH / 2;
    top = y - CENSOR_BBOX_HEIGHT / 2;
    right = left + CENSOR_BBOX_WIDTH;
    bottom = top + CENSOR_BBOX_HEIGHT;
}
void CFallCensor::OnCollisionWith(LPCOLLISIONEVENT e) {
    if (e->ny != 0 && e->obj->IsBlocking())
    {
        if (e->ny < 0)
        {
            isOnPlatform = true;
        }
    }
}