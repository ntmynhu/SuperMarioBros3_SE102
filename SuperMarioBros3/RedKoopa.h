#pragma once
#include "Koopa.h"

#define ID_ANI_RED_KOOPA_WALKING 6100
#define ID_ANI_RED_KOOPA_WALKING_RIGHT 6101
#define ID_ANI_RED_KOOPA_DEFEND 6102
#define ID_ANI_RED_KOOPA_SLIDE 6103
#define ID_ANI_RED_KOOPA_RECOVER 6104
#define ID_ANI_RED_KOOPA_DEFEND_UD 6105
#define ID_ANI_RED_KOOPA_SLIDE_UD 6106
#define ID_ANI_RED_KOOPA_RECOVER_UD 6107

class CFallCensor;
class CRedKoopa :
    public CKoopa
{
protected:
	CFallCensor* fallCensor;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual void OnNoCollision(DWORD dt);

public:
	CRedKoopa(float x, float y);
	~CRedKoopa()
	{
		if (fallCensor != nullptr)
		{
			delete fallCensor;
			fallCensor = nullptr;
		}
	}
};

