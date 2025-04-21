#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "Mario.h"
#include "PlayScene.h"

void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CMario* mario = (CMario *)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer(); 

	switch (KeyCode)
	{
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

void CSampleKeyHandler::KeyState(BYTE *states)
{
	LPGAME game = CGame::GetInstance();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (game->IsKeyDown(DIK_DOWN) && mario->GetState() != MARIO_STATE_SIT)
	{
		mario->SetState(MARIO_STATE_SIT);
	}

	if (game->IsKeyDown(DIK_RIGHT))
	{
		if (game->IsKeyDown(DIK_A))
		{
			mario->SetState(MARIO_STATE_RUNNING_RIGHT);
		}
		else
			mario->SetState(MARIO_STATE_WALKING_RIGHT);
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		if (game->IsKeyDown(DIK_A))
			mario->SetState(MARIO_STATE_RUNNING_LEFT);
		else
			mario->SetState(MARIO_STATE_WALKING_LEFT);
	}
	else
		mario->SetState(MARIO_STATE_IDLE);

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