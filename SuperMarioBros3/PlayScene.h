#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "LimitObject.h"
#include "Goomba.h"
#include "EffectManager.h"
//#include "Koopas.h"

#define CAMERA_MODE_NORMAL 0
#define CAMERA_MODE_SCROLL_X 1

#define CAMERA_SCROLL_VX 0.035f

#define EFFECT_PLAY_TIMEOUT 1000
#define PLAYER_DIE_TIMEOUT 2000
class CPlayScene: public CScene
{
protected: 
	// A play scene has to have player, right? 
	LPGAMEOBJECT player;	
	// An object that set the limit right bottom of the scene
	LPGAMEOBJECT limit_obj;
	// An object that aim to stop mario from moving out of x dir of screen, move along with camera
	LPGAMEOBJECT stop_mario_r;
	LPGAMEOBJECT stop_mario_l;

	ULONGLONG player_die_start = -1;

	float effect_play = -1;
	float scene_start = -1;

	int cam_mode;

	vector<LPGAMEOBJECT> objects;

	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_BACKGROUND(string line);
	void _ParseSection_SETTING(string line);

	void LoadAssets(LPCWSTR assetFile);
	
public: 
	CPlayScene(int id, LPCWSTR filePath, int sceneGroup);

	virtual void Load();
	virtual void Reload();
	virtual void SoftLoad(); //Load scene but keep the old object list - only load asset
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	virtual void SoftUnload(); //Unload scene but keep the old object list

	LPGAMEOBJECT GetPlayer() { return player; }
	LPGAMEOBJECT GetStopLeft() { return stop_mario_l; }
	LPGAMEOBJECT GetStopRight() { return stop_mario_r; }

	void Clear();
	void PurgeDeletedObjects();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

typedef CPlayScene* LPPLAYSCENE;

