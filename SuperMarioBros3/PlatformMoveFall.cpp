#include "PlatformMoveFall.h"
#include "PlayScene.h"
#include "Mario.h"

int CPlatformMoveFall::IsBlocking(LPGAMEOBJECT objSrc) { return (dynamic_cast<CMario*>(objSrc) != NULL); }
void CPlatformMoveFall::SetMario() {
    CPlayScene* scene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
    if (scene) {
        CMario* mario = dynamic_cast<CMario*>(scene->GetPlayer());
        if (mario) {
            this->mario = mario;
        }
    }
}

void CPlatformMoveFall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
    if (mario == NULL) SetMario();
    if (mario == NULL || mario->IsDeleted()) return;

    float m_vx, m_vy;
    mario->GetSpeed(m_vx, m_vy);

    if (isFalling) {
        if (m_vy >= 0 && hasMario)
            mario->SetIsStickToPlatform(this);

        vy += PLATFORM_GRAVITY * dt;
    }

    x += vx * dt;
    y += vy * dt;

    CCollision::GetInstance()->Process(this, dt, coObjects);

    // if Mario is out of platform bounds ----
    float mx, my;
    mario->GetPosition(mx, my);

    float pl_left, pl_top, pl_right, pl_bottom;

    GetBoundingBox(pl_left, pl_top, pl_right, pl_bottom);

    if (mx < pl_left - 20 || mx > pl_right || my > pl_bottom || my < pl_top - 20) {
        if (mario->IsStickToPlatform() && hasMario)
        {
            mario->SetIsStickToPlatform(NULL);
            hasMario = false;
        }
    }
}


void CPlatformMoveFall::OnCollisionWith(LPCOLLISIONEVENT e) {
    if (dynamic_cast<CMario*>(e->obj)) {
        OnCollisionWithMario(e);
    }
}
void CPlatformMoveFall::OnCollisionWithMario(LPCOLLISIONEVENT e) {
    if (mario == NULL) SetMario();
    if (mario->GetState() == MARIO_STATE_DIE) return;
    if (e->ny > 0 && !isFalling) {
        isFalling = true;
        hasMario = true;
        vx = 0;
        vy = PLATFORM_FALL_VY;
    }
    else if (e->nx > 0 && vx < 0) {
        mario->SetIsStickToPlatform(this);
        hasMario = true;
    }
}

void CPlatformMoveFall::OnCollidedByMario(LPCOLLISIONEVENT e) {
    if (mario == NULL) SetMario();
    if (mario->GetState() == MARIO_STATE_DIE) return;
    if (e->ny < 0 && !isFalling) {
        isFalling = true;
        hasMario = true;
        vx = 0;
        vy = PLATFORM_FALL_VY;
    }
    else if (e->nx < 0 && vx < 0) {
        mario->SetIsStickToPlatform(this);
        hasMario = true;
    }
}