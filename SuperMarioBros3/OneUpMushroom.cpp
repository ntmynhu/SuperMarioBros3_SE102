#include "OneUpMushroom.h"

void OneUpMushroom::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_ONE_UP_MUSHROOM)->Render(x, y);
}
