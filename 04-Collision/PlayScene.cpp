#include <iostream>
#include <fstream>
#include "Portal.h"
#include "PlayScene.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"

using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	key_handler = new CPlayScenceKeyHandler(this);
}


/*
	Load scene resources from scene file (textures, sprites, animations and objects)
	See scene1.txt, scene2.txt for detail format specification
*/

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_TEXTURES 2
#define SCENE_SECTION_SPRITES 3
#define SCENE_SECTION_ANIMATIONS 4
#define SCENE_SECTION_ANIMATION_SETS	5
#define SCENE_SECTION_OBJECTS	6

#define OBJECT_TYPE_SIMON	0
#define OBJECT_TYPE_GROUND	1
#define OBJECT_TYPE_CANDLE	2
#define OBJECT_TYPE_ITEM	3

#define OBJECT_TYPE_PORTAL	50

#define MAX_SCENE_LINE 1024


void CPlayScene::_ParseSection_TEXTURES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 5) return; // skip invalid lines

	int texID = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);
	int R = atoi(tokens[2].c_str());
	int G = atoi(tokens[3].c_str());
	int B = atoi(tokens[4].c_str());

	CTextures::GetInstance()->Add(texID, path.c_str(), D3DCOLOR_XRGB(R, G, B));
}

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

	LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
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
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

void CPlayScene::_ParseSection_ANIMATION_SETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return; // skip invalid lines - an animation set must at least id and one animation id

	int ani_set_id = atoi(tokens[0].c_str());

	LPANIMATION_SET s = new CAnimationSet();

	CAnimations *animations = CAnimations::GetInstance();

	for (int i = 1; i < tokens.size(); i++)
	{
		int ani_id = atoi(tokens[i].c_str());

		LPANIMATION ani = animations->Get(ani_id);
		s->push_back(ani);
	}

	CAnimationSets::GetInstance()->Add(ani_set_id, s);
}

/*
	Parse a line in section [OBJECTS]
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());

	int ani_set_id = atoi(tokens[3].c_str());

	CAnimationSets * animation_sets = CAnimationSets::GetInstance();

	CGameObject *obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_SIMON:
		if (player != NULL)
		{
			DebugOut(L"[ERROR] SIMON object was created before!\n");
			return;
		}
		obj = new CSimon();
		player = (CSimon*)obj;
		objects.push_back(obj);
		DebugOut(L"[INFO] Player object created!\n");
		break;
	case OBJECT_TYPE_GROUND: 
		obj = new Brick();
		objects.push_back(obj);
		break;
	case OBJECT_TYPE_CANDLE: 
	{
		int iditem = atof(tokens[4].c_str());
		obj = new  Candle();
		obj->idItem = iditem;
		Candles.push_back(obj);
		break;
	}
	case OBJECT_TYPE_PORTAL:
	{
		float r = atof(tokens[4].c_str());
		float b = atof(tokens[5].c_str());
		int scene_id = atoi(tokens[6].c_str());
		obj = new CPortal(x, y, r, b, scene_id);
		objects.push_back(obj);
	}
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);
	LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

	obj->SetAnimationSet(ani_set);
	
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[TEXTURES]") { section = SCENE_SECTION_TEXTURES; continue; }
		if (line == "[SPRITES]") {
			section = SCENE_SECTION_SPRITES; continue;
		}
		if (line == "[ANIMATIONS]") {
			section = SCENE_SECTION_ANIMATIONS; continue;
		}
		if (line == "[ANIMATION_SETS]") {
			section = SCENE_SECTION_ANIMATION_SETS; continue;
		}
		if (line == "[OBJECTS]") {
			section = SCENE_SECTION_OBJECTS; continue;
		}
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
		case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		case SCENE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		}
	}

	f.close();

	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));

	tilemaps->Add(2000, L"TileMap\\Scene1.png", L"TileMap\\Scene1_map.txt");

	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (size_t i = 0; i < objects.size(); i++) // simon và ground update
	{
		objects[i]->Update(dt, &coObjects);
	}

	if ((player->GetState() == SIMON_STAND_HIT && player->animation_set->at(SIMON_STAND_HIT)->GetCurrentFrame() == 2) || (player->GetState() == SIMON_SIT_HIT && player->animation_set->at(SIMON_SIT_HIT)->GetCurrentFrame() == 2))
	{
		if (player->GetWeapon()->isHittingSubWeapon) // simon đang thực hiên động tác đánh
		{
			player->GetWeapon()->isSubWeaponExist = true;//subweapon đc update và render
			if (player->GetState() == SIMON_SIT_HIT)
				player->GetWeapon()->SetPosSubWeapon(D3DXVECTOR3(player->x, player->y, 0), false);
			else
				player->GetWeapon()->SetPosSubWeapon(D3DXVECTOR3(player->x, player->y, 0), true);
			
		}
		else
		{
			player->GetWhip()->WhipCollideWithCandle(&Candles);
		}

	}

	

	if (player->GetWeapon()->isSubWeaponExist)
	{
		player->GetWeapon()->SubWeaponCollideWithCandle(&Candles);
	}
	
	for (size_t i = 0; i < Candles.size(); i++)
	{
		Candles[i]->Update(dt);
	}
	

	for (size_t i = 0; i < Candles.size(); i++)//kt nến có bị đánh trúng k
	{
		LPGAMEOBJECT obj = Candles[i];
		//float x, y;
		
		if (dynamic_cast<Candle*>(obj) && obj->isDone)
		{
			Candle* candle = dynamic_cast<Candle*>(obj);
			listItem.push_back(candle->GetItem());
			
			vector<LPGAMEOBJECT>::iterator it;
			it = Candles.begin();
			it += i;
			Candles.erase(it);
		}
	}

	for (size_t i = 0; i < listItem.size(); i++)
	{
		listItem[i]->Update(dt, &coObjects);
	}

	player->CollisionWithItem(&listItem); // simon nhặt item


	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return;

	// Update camera to follow mario
	float cx, cy;
	player->GetPosition(cx, cy);

	CGame *game = CGame::GetInstance();
	cx += game->GetScreenWidth() / 2;
	cy -= game->GetScreenHeight() / 2;

	

	if (player->x > (SCREEN_WIDTH / 2) && player->x + (SCREEN_WIDTH / 2) < 1536)
	{
		cx = player->x - (SCREEN_WIDTH / 2);
		CGame::GetInstance()->SetCamPos(cx, 0.0f /*cy*/);
	}
}

void CPlayScene::Render()
{
	tilemaps->Get(2000)->Draw();
	for (size_t i = 0; i < Candles.size(); i++)
		Candles[i]->Render();

	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();

	for (int i = 0; i < listItem.size(); i++)
		listItem[i]->Render();
}

/*
	Unload current scene
*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	CSimon *simon = ((CPlayScene*)scence)->GetPlayer();
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_SPACE:
		simon->Jump();
		break;
	case DIK_A: 
		if (CGame::GetInstance()->IsKeyDown(DIK_UP))
			simon->HitWeapon();
		else 
			simon->Hit();
		break;
	}
}

void CPlayScenceKeyHandler::KeyState(BYTE *states)
{
	CGame *game = CGame::GetInstance();
	CSimon *simon = ((CPlayScene*)scence)->GetPlayer();

	if (simon->GetState() == SIMON_SHOCK && !(simon->animation_set->at(SIMON_SHOCK)->IsRenderOver(600)))
		return;

	if (!(simon->isGrounded))
		return;

	if ((simon->GetState() == SIMON_STAND_HIT && !(simon->animation_set->at(SIMON_STAND_HIT)->IsRenderOver(300))) || (simon->GetState() == SIMON_SIT_HIT && !simon->animation_set->at(SIMON_SIT_HIT)->IsRenderOver(300)))
		return;
		
	if (simon->isHittingWhip && (simon->animation_set->at(SIMON_STAND_HIT)->IsRenderOver(300) || simon->animation_set->at(SIMON_SIT_HIT)->IsRenderOver(300)))
	{
		simon->isHittingWhip = false;
		simon->GetWeapon()->isHittingSubWeapon = false;
		return;
	}

	if (game->IsKeyDown(DIK_DOWN))
	{
		simon->SetState(SIMON_SIT);
		if (game->IsKeyDown(DIK_RIGHT))
			simon->SetNx(1);
		else if (game->IsKeyDown(DIK_LEFT))
			simon->SetNx(-1);
	}
	else if (game->IsKeyDown(DIK_RIGHT))
	{
		simon->WalkRight();
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		simon->WalkLeft();
	}

	else
	{
		if (simon->isGrounded && !simon->isHittingWhip)
		{
			simon->SetState(SIMON_IDLE);
		}
	}
}