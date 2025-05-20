#include "Tunnel.h"

#include "Enemy.h"
#include "PlayScene.h"
#include "Mario.h"

void CTunnel::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (mario == NULL) {
		SetMario();
	}
	if (mario->IsDeleted()) mario = NULL;
	if (mario) {
		if (CCollision::GetInstance()->Overlap(this, mario)->WasCollided()) {
			hasMarioInside = true;
			if (!isEnterable) {
				if (direction == 1)
					mario->SetState(MARIO_STATE_UP_TUNNEL);
				else if (direction == -1) {
					DebugOut(L"Mario in tunnel \n");
					mario->SetState(MARIO_STATE_DOWN_TUNNEL);
				}
				mario->InputLock();
			}
		}
		else if (hasMarioInside) {
			mario->InputUnlock();
			mario->SetState(MARIO_STATE_IDLE);
			hasMarioInside = false;
		}
	}

	CGameObject::Update(dt, coObjects);
}


void CTunnel::SetMario() {
	CPlayScene* scene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
	if (scene) {
		CMario* mario = dynamic_cast<CMario*>(scene->GetPlayer());
		if (mario) {
			this->mario = mario;
		}
	}
}