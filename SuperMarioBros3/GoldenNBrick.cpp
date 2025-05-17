#include "GoldenNBrick.h"
void CGoldenNBrick :: Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	if (spawn_point != 0 && GetTickCount64() - spawn_start > SPAWN_TIMEOUT) {
		spawn_point = coins.size() - 1;
	}

	if (!isEmpty)
	{
		for (int i = 0; i < coins.size(); i++)
		{
			if (!coins[i]) continue;
			if (!coins[i]->IsDeleted())
				coins[i]->Deactivate();
			else
				coins[i] = NULL;
		}
		
	}

	if (isBouncing)
	{
		// If the item is coin, spawn it immediately
		if (!isEmpty && bouncing_start == 0)
		{
			SpawnItem();
		}

		if (bouncing_start == 0) {
			bouncing_start = 1;
		}
		else if (bouncing_start == 1)
			y += vy * BLOCK_BOUNCING_SPEED * dt;

		if (y <= init_y - BLOCK_BOUNCING_HEIGHT)
		{
			vy = 1;
		}

		if (vy == 1 && y >= init_y)
		{
			vy = 0;
			isBouncing = false;
			y = init_y;
			bouncing_start = -1;
		}
	}
	CBlock::Update(dt, coObjects);
}

void CGoldenNBrick :: Render() {
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (!isEmpty)
	{
		aniId = ID_ANI_GOLDEN_BRICK;
	}
	else
	{
		aniId = ID_ANI_BLOCK_EMPTY;
	}
	animations->Get(aniId)->Render(x, y);
}
void CGoldenNBrick::TriggerAction(LPCOLLISIONEVENT e) {
	if (!isEmpty && !isBouncing) {
		StartBouncing();
		
	}
}
void CGoldenNBrick::SpawnItem(){
	coins[spawn_point]->StartBouncing(y);
	coins[spawn_point++] = NULL;

	if (spawn_point == coins.size())
		isEmpty = true;

	spawn_start = GetTickCount64();

	if (isEmpty)
		CleanList();
}

void CGoldenNBrick::CleanList() {
	for (int i = 0; i < coins.size(); i++)
	{
		if (!coins[i]) continue;
		if (!coins[i]->IsDeleted())
			coins[i]->Delete();
	}
	coins.clear();
}