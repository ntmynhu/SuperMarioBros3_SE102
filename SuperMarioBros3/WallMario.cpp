#include "WallMario.h"
#include "Mario.h"
#include "PlayScene.h"
int CWallMario::IsBlocking(LPGAMEOBJECT objSrc) { return (dynamic_cast<CMario*>(objSrc) != NULL); }