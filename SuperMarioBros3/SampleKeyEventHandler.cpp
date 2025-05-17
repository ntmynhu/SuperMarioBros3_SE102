#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "Mario.h"
#include "PlayScene.h"

void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CMario* mario = (CMario *)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer(); 

	DebugOut(L"%d typed\n", KeyCode);
	for (int i = 0; i < PosKeyBind.size(); i++) {
		PosKey* posKey = PosKeyBind[i];
		if (KeyCode == posKey->keyCode) {
			mario->SetPosition(posKey->x, posKey->y);
			CGame::GetInstance()->SetCamPos(posKey->x, posKey->y);
			DebugOut(L"Mario to...%f %f\n", posKey->x, posKey->y);
			return;
		}
	}

	switch (KeyCode)
	{
	//case DIK_DOWN:
	//	mario->SetState(MARIO_STATE_SIT);
	//	break;
	//case DIK_RIGHT:
	//	mario->SetState(MARIO_STATE_WALKING_RIGHT);
	//	break;
	//case DIK_LEFT:
	//	mario->SetState(MARIO_STATE_WALKING_LEFT);
	//	break;
	case DIK_S:
		mario->SetState(MARIO_STATE_JUMP);
		break;
	case DIK_A:
		mario->SetState(MARIO_STATE_B);
		break;
	case DIK_X:
		mario->SetState(MARIO_STATE_TURBO_A);
		break;
	case DIK_1:
		mario->ChangeForm(MARIO_LEVEL_SMALL);
		break;
	case DIK_2:
		mario->ChangeForm(MARIO_LEVEL_BIG);
		break;
	case DIK_3:
		mario->ChangeForm(MARIO_LEVEL_RACOON);
		break;
	case DIK_0:
		mario->SetState(MARIO_STATE_DIE);
		break;
	case DIK_R: // reset
		//Reload();
		break;
	}

	
}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (KeyCode)
	{
	case DIK_S:
		mario->SetState(MARIO_STATE_RELEASE_JUMP);
		break;
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT_RELEASE);
		break;
	case DIK_A:
		mario->SetState(MARIO_STATE_B_RELEASE);
		break;
	}
}

void CSampleKeyHandler::KeyState(BYTE* states)
{
	LPGAME game = CGame::GetInstance();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (game->IsKeyDown(DIK_DOWN) && mario->GetState() != MARIO_STATE_SIT)
	{
		mario->SetState(MARIO_STATE_SIT);
	}

	if (game->IsKeyDown(DIK_RIGHT) && mario->GetState() != MARIO_STATE_WALKING_LEFT && mario->GetState() != MARIO_STATE_RUNNING_LEFT)
	{
		if (game->IsKeyDown(DIK_A))
		{
			mario->SetState(MARIO_STATE_RUNNING_RIGHT);
		}
		else
			mario->SetState(MARIO_STATE_WALKING_RIGHT);

	}
	else if (game->IsKeyDown(DIK_LEFT) && mario->GetState() != MARIO_STATE_WALKING_RIGHT && mario->GetState() != MARIO_STATE_RUNNING_RIGHT)
	{
		if (game->IsKeyDown(DIK_A))
			mario->SetState(MARIO_STATE_RUNNING_LEFT);
		else
			mario->SetState(MARIO_STATE_WALKING_LEFT);
	}
	else if (mario->GetState() != MARIO_STATE_SIT)
		mario->SetState(MARIO_STATE_IDLE);
	else {
		mario->SetState(MARIO_STATE_IDLE);
		mario->SetState(MARIO_STATE_SIT);
	}

	if (game->IsKeyDown(DIK_X))
	{
		mario->SetState(MARIO_STATE_TURBO_A);
	}
	else if (game->IsKeyDown(DIK_Z))
	{
		mario->SetState(MARIO_STATE_TURBO_B);
	}

	if (mario->GetState() == MARIO_STATE_RUNNING_LEFT || mario->GetState() == MARIO_STATE_RUNNING_RIGHT)
	{
		mario->SetChargingPower(true);
	}
	else
	{
		mario->SetChargingPower(false);
	}


}