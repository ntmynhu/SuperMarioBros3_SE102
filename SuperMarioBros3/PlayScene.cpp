#include <iostream>
#include <fstream>
#include "AssetIDs.h"

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
#include "PiranhaPlant.h"
#include "VenusFireTrap.h"
#include "RedVenusFireTrap.h"
#include "FireBall.h"
#include "Platform.h"
#include "FullPlatform.h"
#include "Wall.h"
#include "NoCollidePlatform.h"
#include "NoCollideWall.h"
#include "Tunnel.h"
#include "TunnelPlant.h"
#include "Block.h"
#include "QuestionBlock.h"
#include "SuperMushroom.h"
#include "SuperLeaf.h"

#include "SampleKeyEventHandler.h"

using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath):
	CScene(id, filePath)
{
	player = NULL;
	limit_obj = NULL;
	key_handler = new CSampleKeyHandler(this);
}


#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	1
#define SCENE_SECTION_OBJECTS	2
#define SCENE_SECTION_BACKGROUND	3

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2

#define MAX_SCENE_LINE 1024

#define MAX_Y_OFFSET 30

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

	case OBJECT_TYPE_GOOMBA: obj = new CGoomba(x,y); break;
	case OBJECT_TYPE_PARAGOOMBA: obj = new CParagoomba(x, y); break;
	case OBJECT_TYPE_KOOPA: obj = new CKoopa(x, y); break;
	case OBJECT_TYPE_RED_KOOPA: obj = new CRedKoopa(x, y); break;
	case OBJECT_TYPE_PARAKOOPA: obj = new CParakoopa(x, y); break;

	case OBJECT_TYPE_BRICK:
	{
		obj = new CBrick(x, y);
		break;
	}

	case OBJECT_TYPE_BLOCK:
	{
		obj = new CBlock(x, y);
		break;
	}

	case OBJECT_TYPE_QUESTION_BLOCK:
	{
		int itemID = atoi(tokens[3].c_str());

		switch (itemID)
		{
			case ID_ITEM_COIN:
			{
				CCoin* coin = new CCoin(x, y);
				obj = new CQuestionBlock(x, y, itemID, coin);
				objects.push_back(coin);
				break;
			}
			case ID_ITEM_SUPER_MUSHROOM:
			{
				CSuperMushroom* mushroom = new CSuperMushroom(x, y);
				obj = new CQuestionBlock(x, y, itemID, mushroom);
				objects.push_back(mushroom);
				break;
			}
			case ID_ITEM_SUPER_LEAF:
			{
				CSuperLeaf* leaf = new CSuperLeaf(x, y);
				obj = new CQuestionBlock(x, y, itemID, leaf);
				objects.push_back(leaf);
				break;
			}
			case ID_ITEM_SUPER_MUSHROOM_AND_LEAF:
			{
				CSuperMushroom* mushroom = new CSuperMushroom(x, y);
				CSuperLeaf* leaf = new CSuperLeaf(x, y);
				obj = new CQuestionBlock(x, y, itemID, mushroom, ID_ITEM_SUPER_LEAF, leaf);
				objects.push_back(mushroom);
				objects.push_back(leaf);
				break;
			}
		}

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

		obj = new CTunnel(
			x, y,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end
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
		obj = new CPortal(x, y, r, b, scene_id);
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

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene from : %s \n", sceneFilePath);

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
		if (line == "[OBJECTS]") { section = SCENE_SECTION_OBJECTS; continue; };
		if (line == "[BACKGROUND]") { section = SCENE_SECTION_BACKGROUND; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }	

		//
		// data section
		//
		switch (section)
		{ 
			case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
			case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
			case SCENE_SECTION_BACKGROUND: _ParseSection_BACKGROUND(line); break;
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

	if (GetTickCount64() - game->GetMarioPauseStart() < MARIO_STATE_CHANGE_PAUSE_TIME)
	{
		return;
	}

	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 0; i < objects.size(); i++)
	{
		if(objects[i] -> IsActive())
			coObjects.push_back(objects[i]);
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
	game->GetCamPos(cx, cy); //Get current cam pos

	// Update camera to follow mario
	float mx, my;
	player->GetPosition(mx, my);
	
	// DebugOutTitle(L"Mario x %f y %f", mx, my);

	mx -= game->GetBackBufferWidth() / 2;
	my -= game->GetBackBufferHeight() / 4;

	if (limit_obj != NULL) {
		float lim_x, lim_y;
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
	//Only update y if y offset is large enough
	cy = my;

	CGame::GetInstance()->SetCamPos(cx, cy);
	
	
	PurgeDeletedObjects();
}

void CPlayScene::Render()
{
	for (int i = 0; i < objects.size(); i++)
		if (objects[i] -> IsActive())
			objects[i]->Render();
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
	player = NULL;
	limit_obj = NULL;

	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
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

	// NOTE: remove_if will swap all deleted items to the end of the vector
	// then simply trim the vector, this is much more efficient than deleting individual items
	objects.erase(
		std::remove_if(objects.begin(), objects.end(), CPlayScene::IsGameObjectDeleted),
		objects.end());
}