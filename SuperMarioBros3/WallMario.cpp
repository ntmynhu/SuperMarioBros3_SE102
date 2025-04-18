#include "WallMario.h"
#include "Mario.h"
int CWallMario::IsBlocking(LPGAMEOBJECT objSrc) { return (dynamic_cast<CMario*>(objSrc) != NULL); }