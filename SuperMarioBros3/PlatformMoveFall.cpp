#include "PlatformMoveFall.h"
#include "PlayScene.h"
#include "Mario.h"

int CPlatformMoveFall::IsBlocking(LPGAMEOBJECT objSrc) {
    return (dynamic_cast<CMario*>(objSrc) != NULL);
}

void CPlatformMoveFall::SetMario() {
    CPlayScene* scene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
    if (scene) {
        CMario* m = dynamic_cast<CMario*>(scene->GetPlayer());
        if (m) {
            this->mario = m;
        }
    }
}

void CPlatformMoveFall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
    if (mario == NULL) SetMario();
    if (mario == NULL || mario->IsDeleted()) return;

    float m_vx, m_vy;
    mario->GetSpeed(m_vx, m_vy);

    // Handle falling
    if (isFalling) {
        vy += PLATFORM_GRAVITY * dt;

        if (hasMario) {
            mario->SetIsStickToPlatform(this);  // Stick Mario to this platform
        }
    }

    x += vx * dt;
    y += vy * dt;

    CCollision::GetInstance()->Process(this, dt, coObjects);

    float mx, my;
    mario->GetPosition(mx, my);

    float pl_left, pl_top, pl_right, pl_bottom;
    GetBoundingBox(pl_left, pl_top, pl_right, pl_bottom);

    const float MARGIN_X = 25.0f;
    const float MARGIN_Y = 25.0f;

    bool outOfBounds =
        mx < pl_left - MARGIN_X ||
        mx > pl_right + MARGIN_X ||
        my < pl_top - MARGIN_Y ||
        my > pl_bottom + MARGIN_Y;

    if (outOfBounds && hasMario) {
        if (mario->IsStickToPlatform()) {
            mario->SetIsStickToPlatform(NULL);
        }
        hasMario = false;
        DebugOut(L"Mario is not on platform at (%f, %f) Mario pos (%f, %f)\n", x, y, mx, my);
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
    else if (e->nx != 0 && vx != 0) {
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
    else if (e->nx != 0 && vx != 0) {
        mario->SetIsStickToPlatform(this);
        hasMario = true;
    }
}
