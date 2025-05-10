#pragma once

#include "Scene.h"
#include "PosKey.h"

#include <vector>
using namespace std;

class CSampleKeyHandler: public CSceneKeyHandler
{
protected:
	vector<PosKey*> PosKeyBind;

public:
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	virtual void AddPosKey(PosKey* KeyCode) {
		PosKeyBind.push_back(KeyCode);
	};
	CSampleKeyHandler(LPSCENE s) :CSceneKeyHandler(s) {};
};
