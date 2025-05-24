#include "Tail.h"
#include "Enemy.h"
#include "Plant.h"
#include "Block.h"
#include "debug.h"
#include "EffectManager.h"

void CTail::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
    left = x - TAIL_BBOX_WIDTH / 2;
    top = y - TAIL_BBOX_HEIGHT / 2;
    right = left + TAIL_BBOX_WIDTH;
    bottom = top + TAIL_BBOX_HEIGHT;
}
void CTail::OnCollisionWith(LPCOLLISIONEVENT e) {
    if (dynamic_cast<CEnemy*> (e->obj)) {
        OnCollisionWithEnemy(e);
    }
    else if (dynamic_cast<CBlock*>(e->obj)) {
        OnCollisionWithBlock(e);
    }
    else if (dynamic_cast<CPlant*>(e->obj)) {
        OnCollisionWithPlant(e);
    }
}

void CTail::OnCollisionWithPlant(LPCOLLISIONEVENT e) 
{
    CPlant* plant = dynamic_cast<CPlant*>(e->obj);
    if (plant->GetState() != PLANT_STATE_DIE)
    {
		float e_x, e_y;
		e->obj->GetPosition(e_x, e_y);
        TailEffect* effect = new TailEffect(e_x, e_y);
        plant->TakeTailAttackDamage(this->x);
    }
    DebugOut(L"Tail Collided! Plant state: %d\n", e->obj->GetState());
}

void CTail::OnCollisionWithEnemy(LPCOLLISIONEVENT e) {
    CEnemy* enemy = dynamic_cast<CEnemy*> (e->obj);
    if (enemy->GetState() != ENEMY_STATE_DIE)
    {
		float e_x, e_y;
		e->obj->GetPosition(e_x, e_y);
		TailEffect* effect = new TailEffect(e_x, e_y);
        enemy->TakeTailAttackDamage(this->x);
    }
    
    DebugOut(L"Tail Collided! Enemy state: %d\n", e->obj->GetState());
}

void CTail::OnCollisionWithBlock(LPCOLLISIONEVENT e)
{
    CBlock* qBlock = dynamic_cast<CBlock*>(e->obj);
    qBlock->TriggerAction();

    DebugOut(L"Tail Collided! Block state: %d\n", e->obj->GetState());
}

void CTail::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
    CCollision::GetInstance()->Process(this, dt, coObjects);
}