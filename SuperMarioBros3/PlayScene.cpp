#include <iostream>
#include <fstream>
#include "AssetIDs.h"

#include "GameData.h"
#include "PlayScene.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "Coin.h"
#include "Background.h"

#include "Goomba.h"
#include "Paragoomba.h"
#include "Koopa.h"
#include "Parakoopa.h"
#include "RedKoopa.h"
#include "RedParakoopa.h"
#include "PiranhaPlant.h"
#include "VenusFireTrap.h"
#include "RedVenusFireTrap.h"
#include "FireBall.h"
#include "Platform.h"
#include "PlatformMoveFall.h"
#include "FullPlatform.h"
#include "PlatformKill.h"
#include "Wall.h"
#include "WallMario.h"
#include "NoCollidePlatform.h"
#include "NoCollideWall.h"
#include "Tunnel.h"
#include "TunnelPlant.h"
#include "Block.h"
#include "QuestionBlock.h"
#include "GoldenBrick.h"
#include "GoldenNBrick.h"
#include "SuperMushroom.h"
#include "SuperLeaf.h"
#include "Particle.h"
#include "BrokenBrick_Particle.h"
#include "BlueButton.h"

#include "HUD.h"
#include "SampleKeyEventHandler.h"
#include "OneUpMushroom.h"
#include "EffectManager.h"

using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath, int sceneGroup):
	CScene(id, filePath, sceneGroup)
{
	cam_mode = CAMERA_MODE_NORMAL;
	player = NULL;
	limit_obj = NULL;
	stop_mario_l = NULL;
	stop_mario_r = NULL;
	key_handler = new CSampleKeyHandler(this);
}


#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	1
#define SCENE_SECTION_OBJECTS	2
#define SCENE_SECTION_BACKGROUND	3
#define SCENE_SECTION_SETTING	4

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2

#define MAX_SCENE_LINE 1024

#define MAX_Y_OFFSET 30

vector<LPGAMEOBJECT> goldenBricks;

void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPTEXTURE tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return; 
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CPlayScene::_ParseSection_ASSETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return;

	wstring path = ToWSTR(tokens[0]);
	
	LoadAssets(path.c_str());
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i+1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

/*
	Parse a line in section [SETTING]
*/
void CPlayScene::_ParseSection_SETTING(string line)
{
	vector<string> tokens = split(line);
	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;

	if (tokens[0] == "mode") {
		int mode = atoi(tokens[1].c_str());
		switch (mode) {
		case CAMERA_MODE_NORMAL:
			cam_mode = CAMERA_MODE_NORMAL;
			break;
		case CAMERA_MODE_SCROLL_X:
			cam_mode = CAMERA_MODE_SCROLL_X;
			break;
		}
	}

	else if (tokens[0] == "poskeycode") {
		int keycode = atoi(tokens[1].c_str());
		float key_x = (float)atof(tokens[2].c_str());
		float key_y = (float)atof(tokens[3].c_str());
		
		PosKey* posKey = new PosKey(keycode, key_x, key_y);
		((CSampleKeyHandler*)key_handler)->AddPosKey(posKey);
	}
}

/*
	Parse a line in section [BACKGROUND]
*/
void CPlayScene::_ParseSection_BACKGROUND(string line)
{
	vector<string> tokens = split(line);
	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;

	//Background is always the first object if any
	if (objects.empty())
	{
		int object_type = atoi(tokens[0].c_str());
		float x = (float)atof(tokens[1].c_str());
		float y = (float)atof(tokens[2].c_str());
		int w = atoi(tokens[3].c_str());
		int h = atoi(tokens[4].c_str());
		int base_asset_id = atoi(tokens[5].c_str());

		CGameObject* obj = NULL;
		if (object_type == OBJECT_TYPE_BACKGROUND) {
			obj = new CBackground(x, y, w, h, base_asset_id);

			DebugOut(L"[INFO] Background object has been created!\n");
			// General object setup
			obj->SetPosition(x, y);
			objects.push_back(obj);
		}
	}
	else {
		CBackground* background = dynamic_cast<CBackground*>(objects[0]);
		if (background) {
			int row = atoi(tokens[0].c_str());
			for (int col = 1; col <= background->GetWidth(); col++) {
				background->SetTile(col - 1, row, atoi(tokens[col].c_str()));
			}
		}
		return;
	}
}

/*
	Parse a line in section [OBJECTS] 
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());

	CGameObject *obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
		if (player!=NULL) 
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = new CMario(x,y); 
		player = (CMario*)obj;  

		int level;
		CGameData::GetInstance()->GetLevel(level);
		((CMario*)player)->ChangeForm(level);

		DebugOut(L"[INFO] Player object has been created!\n");
		break;
	case OBJECT_TYPE_LIMIT_OBJ:
		if (limit_obj != NULL)
		{
			DebugOut(L"[ERROR] LIMIT object was created before!\n");
			return;
		}
		obj = new CLimitObject(x, y);
		limit_obj = (CLimitObject*)obj;

		DebugOut(L"[INFO] Limit object has been created!\n");
		break;
	case OBJECT_TYPE_ONLY_MARIO_COLLIDE_WALL:
	{
		if (stop_mario_l != NULL && stop_mario_r != NULL)
		{
			DebugOut(L"[ERROR] STOP object was created before!\n");
			return;
		}
		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int side = atoi(tokens[6].c_str());

		obj = new CWallMario(
			x, y,
			cell_width, cell_height, length,
			side
		);
		if (stop_mario_l == NULL && side == -1) {
			x = 0;
			stop_mario_l = (CWallMario*)obj;
			DebugOut(L"[INFO] Stop left object has been created!\n");
		}
		else if (stop_mario_r == NULL && side == 1) {
			x = CGame::GetInstance()->GetBackBufferWidth();
			stop_mario_r = (CWallMario*)obj;
			DebugOut(L"[INFO] Stop right object has been created!\n");
		}
		break;
	}
	case OBJECT_TYPE_GOOMBA: obj = new CGoomba(x,y); break;
	case OBJECT_TYPE_PARAGOOMBA: obj = new CParagoomba(x, y); break;
	case OBJECT_TYPE_KOOPA: obj = new CKoopa(x, y); break;
	case OBJECT_TYPE_RED_KOOPA: obj = new CRedKoopa(x, y); break;
	case OBJECT_TYPE_PARAKOOPA: obj = new CParakoopa(x, y); break;
	case OBJECT_TYPE_RED_PARAKOOPA:
	{
		float range = RED_PARA_KOOPA_FLY_RANGE;
		if (tokens.size() > 3)
			range = (float)atof(tokens[3].c_str());
		obj = new CRedParakoopa(x, y, range);
		break;
	}
	case OBJECT_TYPE_BRICK:
	{
		obj = new CBrick(x, y);
		break;
	}

	case OBJECT_TYPE_BLOCK:
	{
		obj = new CBlock(x, y, ID_ANI_BLOCK_EMPTY);
		break;
	}

	case OBJECT_TYPE_QUESTION_BLOCK:
	{
		int itemID = atoi(tokens[3].c_str());
		int ani_id = ID_ANI_QUESTION_BLOCK;
		if (tokens.size() > 4) {
			ani_id = atoi(tokens[4].c_str());
		}
		switch (itemID)
		{
			case ID_ITEM_COIN:
			{
				CCoin* coin = new CCoin(x, y - COIN_APPEARING_HEIGHT);
				obj = new CQuestionBlock(x, y, itemID, coin, -1, NULL, ani_id);
				objects.push_back(coin);
				break;
			}
			case ID_ITEM_SUPER_MUSHROOM:
			{
				CSuperMushroom* mushroom = new CSuperMushroom(x, y);
				obj = new CQuestionBlock(x, y, itemID, mushroom, -1, NULL, ani_id);
				objects.push_back(mushroom);
				break;
			}
			case ID_ITEM_SUPER_LEAF:
			{
				CSuperLeaf* leaf = new CSuperLeaf(x, y);
				obj = new CQuestionBlock(x, y, itemID, leaf, -1, NULL, ani_id);
				objects.push_back(leaf);
				break;
			}
			case ID_ITEM_SUPER_MUSHROOM_AND_LEAF:
			{
				CSuperMushroom* mushroom = new CSuperMushroom(x, y);
				CSuperLeaf* leaf = new CSuperLeaf(x, y);
				obj = new CQuestionBlock(x, y, itemID, mushroom, ID_ITEM_SUPER_LEAF, leaf, ani_id);
				objects.push_back(mushroom);
				objects.push_back(leaf);
				break;
			}
		}

		break;
	}

	case OBJECT_TYPE_GOLDEN_BRICK:
	{
		int itemID = atoi(tokens[3].c_str());
		int ani_id = ID_ANI_GOLDEN_BRICK;
		if (tokens.size() > 5) {
			ani_id = atoi(tokens[5].c_str());
		}
		switch (itemID)
		{
		case ID_ITEM_COIN:
		{
			int stat = atoi(tokens[4].c_str());
			vector<CBrick_Particle*> particles;
			for (int i = 0; i < 4; i++)
			{
				CBrick_Particle* particle = new CBrick_Particle(x, y);
				particle->Deactivate();
				particles.push_back(particle);
				objects.push_back(particle);
			}

			BrokenBrick_Particle* broken_particle = new BrokenBrick_Particle(x, y, particles);
			objects.push_back(broken_particle);

			CCoin* coin = new CCoin(x, y);
			obj = new CGoldenBrick(x, y, itemID, coin, broken_particle, stat, ani_id);
			objects.push_back(coin);

			goldenBricks.push_back(obj);

			break;
		}
		case ID_ITEM_ONE_UP_MUSHROOM:
		{
			OneUpMushroom* oneUpMushroom = new OneUpMushroom(x, y);
			obj = new CGoldenBrick(x, y, itemID, oneUpMushroom, NULL, 0, ani_id);
			objects.push_back(oneUpMushroom);

			goldenBricks.push_back(obj);

			break;
		}
		}

		break;
	}

	case OBJECT_TYPE_GOLDEN_N_BRICK:
	{
		int ani_id = ID_ANI_GOLDEN_BRICK;
		if (tokens.size() > 4) {
			ani_id = atoi(tokens[4].c_str());
		}
		int num_coins = atoi(tokens[3].c_str());
		vector<CCoin*> coins;
		for (int i = 0; i < num_coins; i++) {
			CCoin* coin = new CCoin(x, y);
			coins.push_back(coin);
			objects.push_back(coin);
		}
		obj = new CGoldenNBrick(x, y, coins, ani_id);
		break;
	}

	case OBJECT_TYPE_BLUE_BUTTON:
	{
		CBlueButton* button = new CBlueButton(x, y - BLUE_BUTTON_BBOX_HEIGHT, goldenBricks);
		button->Deactivate();
		objects.push_back(button);

		obj = new CGoldenBrick(x, y, ID_ITEM_BLUE_BUTTON, button, NULL);
		break;
	}

	case OBJECT_TYPE_COIN: obj = new CCoin(x, y); break;

	case OBJECT_TYPE_SUPER_MUSHROOM:
	{
		obj = new CSuperMushroom(x, y);
		break;
	}

	case OBJECT_TYPE_SUPER_LEAF:
	{
		obj = new CSuperLeaf(x, y);
		break;
	}

	case OBJECT_TYPE_PLATFORM:
	{

		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());

		obj = new CPlatform(
			x, y,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end
		);

		break;
	}

	case OBJECT_TYPE_PLATFORM_KILL:
	{

		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());

		obj = new CPlatformKill(
			x, y,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end
		);

		break;
	}

	case OBJECT_TYPE_FULL_PLATFORM:
	{

		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());

		obj = new CFullPlatform(
			x, y,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end
		);

		break;
	}

	case OBJECT_TYPE_PLATFORM_MOVE_FALL:
	{

		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());

		int XDir = atoi(tokens[9].c_str());
		int YDir = atoi(tokens[10].c_str());

		obj = new CPlatformMoveFall(
			x, y,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end,
			XDir, YDir
		);

		break;
	}

	case OBJECT_TYPE_WALL:
	{

		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());

		obj = new CWall(
			x, y,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end
		);

		break;
	}

	case OBJECT_TYPE_NO_COLLIDE_PLATFORM:
	{

		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());

		obj = new CNoCollidePlatform(
			x, y,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end
		);

		break;
	}

	case OBJECT_TYPE_NO_COLLIDE_WALL:
	{

		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());

		obj = new CNoCollideWall(
			x, y,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end
		);

		break;
	}

	case OBJECT_TYPE_TUNNEL:
	{

		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());

		int isEnterable = 0, direction = 1;
		if (tokens.size() == 11) {
			isEnterable = atoi(tokens[9].c_str());
			direction = atoi(tokens[10].c_str());
		}
		obj = new CTunnel(
			x, y,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end,
			isEnterable, direction
		);

		break;
	}

	case OBJECT_TYPE_PLANT_TUNNEL:
	{

		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());
		int plantId = atoi(tokens[9].c_str());

		CPlant* plantObj = NULL;
		CFireBall* fireball = NULL;
		switch (plantId) {
		case OBJECT_TYPE_PIRANHA:
			plantObj = new CPiranhaPlant(x, y - cell_height / 2 + PIRANHA_BBOX_HEIGHT / 2 + HIDE_OFFSET);
			break;
		case OBJECT_TYPE_VENUS:
			fireball = new CFireBall(x, y - cell_height / 2 + VENUS_BBOX_HEIGHT / 2 + HIDE_OFFSET);
			objects.push_back(fireball);
			plantObj = new CVenusFireTrap(x, y - cell_height / 2 + VENUS_BBOX_HEIGHT / 2 + HIDE_OFFSET, fireball);
			break;
		case OBJECT_TYPE_RED_VENUS:
			fireball = new CFireBall(x, y - cell_height / 2 + RED_VENUS_BBOX_HEIGHT / 2 + HIDE_OFFSET);
			objects.push_back(fireball);
			plantObj = new CRedVenusFireTrap(x, y - cell_height / 2 + RED_VENUS_BBOX_HEIGHT / 2 + HIDE_OFFSET, fireball);
			break;
		}

		obj = new CTunnelPlant(
			x, y,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end, plantObj
		);

		objects.push_back(plantObj);
		break;
	}

	case OBJECT_TYPE_PORTAL:
	{
		float r = (float)atof(tokens[3].c_str());
		float b = (float)atof(tokens[4].c_str());
		int scene_id = atoi(tokens[5].c_str());
		float out_x = -1;
		float out_y = -1;
		if (tokens.size() > 6) {
			out_x = (float)atof(tokens[6].c_str());
			out_y = (float)atof(tokens[7].c_str());
		}
		obj = new CPortal(x, y, r, b, scene_id, out_x, out_y);
	}
	break;


	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);


	objects.push_back(obj);
}

void CPlayScene::LoadAssets(LPCWSTR assetFile)
{
	DebugOut(L"[INFO] Start loading assets from : %s \n", assetFile);

	ifstream f;
	f.open(assetFile);

	int section = ASSETS_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SPRITES]") { section = ASSETS_SECTION_SPRITES; continue; };
		if (line == "[ANIMATIONS]") { section = ASSETS_SECTION_ANIMATIONS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case ASSETS_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case ASSETS_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading assets from %s\n", assetFile);
}

void CPlayScene::SoftLoad()
{
	DebugOut(L"[INFO] Start soft loading scene from : %s \n", sceneFilePath);

	if (objects.empty())
	{
		Load();
		return;
	}
	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[ASSETS]") { section = SCENE_SECTION_ASSETS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
		}
	}

	f.close();

	if (player) {
		int level;
		CGameData::GetInstance()->GetLevel(level);
		((CMario*)player)->ChangeForm(level);
	}

	DebugOut(L"[INFO] Done soft loading scene  %s\n", sceneFilePath);
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);
	CGame::GetInstance()->SetCamPos(0, 0);
	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;					

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[ASSETS]") { section = SCENE_SECTION_ASSETS; continue; };
		if (line == "[OBJECTS]") { section = SCENE_SECTION_OBJECTS; continue; };
		if (line == "[BACKGROUND]") { section = SCENE_SECTION_BACKGROUND; continue; };
		if (line == "[SETTING]") { section = SCENE_SECTION_SETTING; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }	

		//
		// data section
		//
		switch (section)
		{ 
			case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
			case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
			case SCENE_SECTION_BACKGROUND: _ParseSection_BACKGROUND(line); break;
			case SCENE_SECTION_SETTING: _ParseSection_SETTING(line); break;
		}
	}

	f.close();
	
	
	DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: Set a max camY
	CGame* game = CGame::GetInstance();

	HUD::GetInstance()->SetPosition(game->GetBackBufferWidth()/2, game->GetBackBufferHeight());

	game->ProcessTimer(dt);

	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 0; i < objects.size(); i++)
	{
		if(objects[i] -> IsActive())
			coObjects.push_back(objects[i]);
	}

	if (player == NULL || player->IsDeleted()) return;
	if (game->IsMarioStateChangedPause())
	{
		player->Update(dt, &coObjects);
		return;
	}

	if (player->GetState() == MARIO_STATE_DIE)
	{
		player->Update(dt, &coObjects);
		game->StartMarioPause();
		return;
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		if (game->IsInCam(objects[i]) && objects[i] -> IsActive()) {
			objects[i]->Update(dt, &coObjects);
		}
		else {
			objects[i]->Deactivate();
			float x, y;
			objects[i]->GetInitPosition(x, y);
			if (!game->IsInCam(y, x, x, y)) {
				objects[i]->ResetPos();
			}
		}
	}

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return; 

	
	float cx, cy;
	float cam_vx = 0;
	game->GetCamPos(cx, cy); //Get current cam pos

	float mx, my;
	player->GetPosition(mx, my);

	if (!game->IsInCam(player)) {
		if (my <= -CAM_MARGIN) {
			my = -CAM_MARGIN;
			player->SetPosition(mx, my);
		}
	}

	if (cam_mode == CAMERA_MODE_NORMAL) {
		// Update camera to follow mario
		// DebugOutTitle(L"Mario x %f y %f", mx, my);

		mx -= game->GetBackBufferWidth() / 2;
		my -= game->GetBackBufferHeight() / 2.3f;

		float lim_x, lim_y = -1;
		if (limit_obj != NULL) {
			
			limit_obj->GetPosition(lim_x, lim_y);

			//Cam lim is in the right bottom
			lim_x -= game->GetBackBufferWidth();
			lim_y -= game->GetBackBufferHeight();

			if (mx > lim_x) mx = lim_x;
			if (my > lim_y) my = lim_y;
		}
		//Prevent camera from moving out of world range
		if (mx < 0) mx = 0;
		if (my < 0) my = 0;

		cx = mx;

		if ((lim_y != -1 && cy != lim_y) || ((CMario*)player)->IsFlying())
		{
			cy = my;
		}
	}
	else if (cam_mode == CAMERA_MODE_SCROLL_X) {
		cam_vx = CAMERA_SCROLL_VX;
		cx += CAMERA_SCROLL_VX * dt;
		if (limit_obj != NULL) {
			float lim_x, lim_y;
			limit_obj->GetPosition(lim_x, lim_y);

			lim_x -= game->GetBackBufferWidth();
			lim_y -= game->GetBackBufferHeight();
			if (cx > lim_x) {
				cx = lim_x;
				cam_vx = 0;
			}
			cy = lim_y;
		}
		if (cx < 0) cx = 0;
		if (cy < 0) cy = 0;
	}

	CGame::GetInstance()->SetCamPos(cx, cy);

	float m_vx, m_vy;
	
	if (stop_mario_l != NULL) {
		if (cam_mode == CAMERA_MODE_SCROLL_X) {
			if (cam_vx == 0) {
				stop_mario_l->SetPosition(cx, 0);
			}
			stop_mario_l->SetSpeed(cam_vx, 0);
		}
		else if (cam_mode == CAMERA_MODE_NORMAL)
			stop_mario_l->SetPosition(cx, 0);

	}
	if (stop_mario_r != NULL) {
		if (cam_mode == CAMERA_MODE_SCROLL_X) 
		{
			if (cam_vx == 0) {
				stop_mario_r->SetPosition(cx + game->GetBackBufferWidth(), 0);
			}
			stop_mario_r->SetSpeed(cam_vx, 0);
		}
		else if (cam_mode == CAMERA_MODE_NORMAL)
			stop_mario_r->SetPosition(cx + game->GetBackBufferWidth(), 0);
	}
	
	PurgeDeletedObjects();
}

void CPlayScene::Render()
{
	for (int i = 0; i < objects.size(); i++)
		if (objects[i] -> IsActive())
			objects[i]->Render();

	HUD::GetInstance()->Render();
	EffectManager::GetInstance()->Render();
}

/*
*	Clear all objects from this scene
*/
void CPlayScene::Clear()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		delete (*it);
	}
	objects.clear();
}

/*
	Unload scene

	TODO: Beside objects, we need to clean up sprites, animations and textures as well 

*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	
	objects.clear();
	((CSampleKeyHandler*)key_handler)->ClearKey();
	player = NULL;
	limit_obj = NULL;
	stop_mario_l = NULL;
	stop_mario_r = NULL;
	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}

void CPlayScene::SoftUnload()
{
	DebugOut(L"[INFO] Scene soft %d unloaded! \n", id);
}

bool CPlayScene::IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }

void CPlayScene::PurgeDeletedObjects()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			delete o;
			*it = NULL;
		}
	}

	if (player->IsDeleted()) player = NULL;
	// NOTE: remove_if will swap all deleted items to the end of the vector
	// then simply trim the vector, this is much more efficient than deleting individual items
	objects.erase(
		std::remove_if(objects.begin(), objects.end(), CPlayScene::IsGameObjectDeleted),
		objects.end());
}