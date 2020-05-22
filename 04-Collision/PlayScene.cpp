#include <iostream>
#include <fstream>
#include "PlayScene.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Stair.h"
#include "Candle.h"
#include "Brick.h"
#include "Torch.h"
#include "Item.h"
#include "Portal.h"
#include "Bat.h"
#include "Knight.h"
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
#define SCENE_SECTION_OBJECTS	6
#define SCENE_SECTION_TILEMAP 7
#define OBJECT_TYPE_SIMON	0
#define OBJECT_TYPE_BRICK	1
#define OBJECT_TYPE_SECRETOBJ	2
#define OBJECT_TYPE_ITEM	3
#define OBJECT_TYPE_STAIR	4
#define OBJECT_TYPE_ENEMY	5
#define OBJECT_TYPE_PORTAL	50

#define MAX_SCENE_LINE 1024

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

		if (line == "[OBJECTS]")
		{
			section = SCENE_SECTION_OBJECTS;
			continue;
		}
		if (line == "[TILEMAP]")
		{
			section = SCENE_SECTION_TILEMAP;
			continue;
		}
		if (line[0] == '[')
		{
			section = SCENE_SECTION_UNKNOWN;
			continue;
		}
		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_OBJECTS:
			_ParseSection_OBJECTS(line);
			break;
		case SCENE_SECTION_TILEMAP:
			_ParseSection_TILEMAP(line);
			break;
		}
	}
	f.close();

	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));

	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
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
			//player->SetPosition(x, y);
			return;
		}
		obj = new CSimon();
		player = (CSimon*)obj;
		DebugOut(L"[INFO] Player object created!\n");
		break;
	case OBJECT_TYPE_BRICK: 
		obj = new Brick();
		bricks.push_back(obj);
		break;
	case OBJECT_TYPE_SECRETOBJ: 
	{
		int iditem = atof(tokens[4].c_str());
		int typeObj = atof(tokens[5].c_str());
		if (typeObj == 0)
			obj = new Torch(iditem);
		else
			obj = new Candle(iditem);
		secretObj.push_back(obj);
		break;
	}
	case OBJECT_TYPE_PORTAL:
	{
		float width = atof(tokens[4].c_str());
		float height = atof(tokens[5].c_str());
		int scene_id = atoi(tokens[6].c_str());
		int xNext = atoi(tokens[7].c_str());
		int yNext = atoi(tokens[8].c_str());
		obj = new CPortal(x, y, width, height, scene_id, xNext, yNext);
		portal.push_back(obj);
		break;
	}
	case OBJECT_TYPE_ENEMY:
	{
		int typeEnemy = atof(tokens[4].c_str());
		if (typeEnemy == 0)
		{
			obj = new Bat();
		}
		else if (typeEnemy == 1)
		{
			obj = new Knight();
		}
		enemys.push_back(obj);
		break;
	}
	case OBJECT_TYPE_STAIR:
	{
		int DirectionX = atof(tokens[4].c_str());
		int DirectionY = atof(tokens[5].c_str());
		
		obj = new Stair(x,y,DirectionX, DirectionY);
		stairs.push_back(obj);
		break;
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

void CPlayScene::_ParseSection_TILEMAP(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 7) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	wstring filePath_texture = ToWSTR(tokens[1]);
	wstring filePath_data = ToWSTR(tokens[2]);
	int num_row_on_texture = atoi(tokens[3].c_str());
	int num_col_on_textture = atoi(tokens[4].c_str());
	int num_row_on_tilemap = atoi(tokens[5].c_str());
	int num_col_on_tilemap = atoi(tokens[6].c_str());
	int tileset_width = atoi(tokens[7].c_str());
	int tileset_height = atoi(tokens[8].c_str());
	boardscore = new BoardScore();
	tilemap = new TileMap(ID, filePath_texture.c_str(), filePath_data.c_str(), num_row_on_texture, num_col_on_textture, num_row_on_tilemap, num_col_on_tilemap, tileset_width, tileset_height);
}


void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 
	
	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 1; i < bricks.size(); i++)
	{
		coObjects.push_back(bricks[i]);
	}
	player->Update(dt, &coObjects);
	
	player->SimonTouchStair(&stairs);// simon chạm cầu thang

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
			player->GetWhip()->WhipCollideWithSecretObj(&secretObj);//kt torch vaf candle có bị đánh trúng k
		}
	}

	if (player->GetWeapon()->isSubWeaponExist) //kiểm tra subweapon va chạm với torch va candle
	{
		player->GetWeapon()->SubWeaponCollideWithSecretObj(&secretObj);
	}
	

	for (size_t i = 0; i < secretObj.size(); i++)
	{
		LPGAMEOBJECT obj = secretObj[i];
		if (dynamic_cast<Torch*>(obj))
		{
			Torch* torch = dynamic_cast<Torch*>(obj);
			if (torch->GetRenderFire())
			{
				listItem.push_back(torch->GetItem());
				vector<LPGAMEOBJECT>::iterator it;
				it = secretObj.begin();
				it += i;
				secretObj.erase(it);
			}
			else
				secretObj[i]->Update(dt);
		}
		else if (dynamic_cast<Candle*>(obj))
		{
			Candle * candle = dynamic_cast<Candle*>(obj);
			if (candle->GetIsBreak())
			{
				candle->DropItem();
				listItem.push_back(candle->GetItem());
				vector<LPGAMEOBJECT>::iterator it;
				it = secretObj.begin();
				it += i;
				secretObj.erase(it);
			}
		}
	}

	for (int i = 0; i < enemys.size(); i++)
	{
		enemys[i]->Update(dt,&coObjects);
	}

	player->CollideWithEnemy(&enemys);

	for (size_t i = 0; i < listItem.size(); i++)//update list item
	{
		LPGAMEOBJECT obj = listItem[i];
		Item* e = dynamic_cast<Item*>(obj);
		if (e->GetTimeOut())
		{
			vector<LPGAMEOBJECT>::iterator it;
			it = listItem.begin();
			it += i;
			listItem.erase(it);
		}
		else
			listItem[i]->Update(dt, &coObjects);
	}

	player->CollideWithItem(&listItem); //kiểm tra simon nhặt item

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return;

	// Update camera to follow mario
	float cx, cy;
	player->GetPosition(cx, cy);

	CGame *game = CGame::GetInstance();
	cx += game->GetScreenWidth() / 2;
	cy -= game->GetScreenHeight() / 2;

	if (player->x > (SCREEN_WIDTH / 2) && player->x + (SCREEN_WIDTH / 2) < tilemap->GetWidthTileMap())
	{
		cx = player->x - (SCREEN_WIDTH / 2);
		CGame::GetInstance()->SetCamPos(cx, 0.0f);
	}

	boardscore->Update(dt, CGame::GetInstance()->GetCamPosX(),0,player);

	if (int idScene = player->CollideWithPortal(&portal)) //kiểm tra simon đi vào cổng
	{
		//portal.at(0).idscene();
		CGame::GetInstance()->SwitchScene(idScene, player);
		CGame::GetInstance()->SetCamPos(0.0f, 0.0f);
	}
	
}

void CPlayScene::Render()
{
	boardscore->Render();
	for (int i = 0; i < bricks.size(); i++)
		bricks[i]->Render();
	tilemap->Draw();
	for (size_t i = 0; i < secretObj.size(); i++)
		secretObj[i]->Render();
	for (int i = 0; i < listItem.size(); i++)
		listItem[i]->Render();
	for (int i = 0; i < enemys.size(); i++)
		enemys[i]->Render();
	/*for (int i = 0; i < portal.size(); i++)
		portal[i]->Render();*/
	for (int i = 0; i < stairs.size(); i++)
	{
		stairs[i]->Render();
	}
	player->Render();
}

/*
	Unload current scene
*/
void CPlayScene::Unload()
{
	for (int i = 0; i < bricks.size(); i++)
		delete bricks[i];

	bricks.clear();
	//player = NULL;

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

int i = 1;

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
			simon->UseSubweapon();
		else 
			simon->Hit();
		break;
	case DIK_1:
		CGame::GetInstance()->SwitchScene(++i, simon);
		CGame::GetInstance()->SetCamPos(0.0f, 0.0f);
		break;
	}
}

void CPlayScenceKeyHandler::KeyState(BYTE *states)
{
	CGame *game = CGame::GetInstance();
	CSimon *simon = ((CPlayScene*)scence)->GetPlayer();

	if (simon->GetState() == SIMON_SHOCK && !(simon->animation_set->at(SIMON_SHOCK)->IsRenderOver(600)))
		return;
	if ((simon->GetState() == SIMON_STAIR_UP && !simon->animation_set->at(SIMON_STAIR_UP)->IsRenderOver(200)) || (simon->GetState() == SIMON_STAIR_DOWN && !simon->animation_set->at(SIMON_STAIR_DOWN)->IsRenderOver(200)))
		return;
	if ((simon->GetState() == SIMON_STAND_HIT && !(simon->animation_set->at(SIMON_STAND_HIT)->IsRenderOver(300))) || (simon->GetState() == SIMON_SIT_HIT && !simon->animation_set->at(SIMON_SIT_HIT)->IsRenderOver(300)))
		return;

	if ((simon->GetState() == SIMON_STAND_HIT && (simon->animation_set->at(SIMON_STAND_HIT)->IsRenderOver(300))) || (simon->GetState() == SIMON_SIT_HIT && simon->animation_set->at(SIMON_SIT_HIT)->IsRenderOver(300)))
	{
		simon->GetWeapon()->isHittingSubWeapon = false;
		simon->SetAnimation(SIMON_JUMP);
	}

	if (simon->isTouchStairTop && game->IsKeyDown(DIK_DOWN) && !simon->isOnStair)
	{
		if (simon->AutoWalk(simon->GetPosXStair()))
		{
			simon->isOnStair = true;
			simon->isTouchStairTop = false;
		}
		else
			return;
	}
	else if (simon->isTouchStairBottom && game->IsKeyDown(DIK_UP) && !simon->isOnStair)
	{
		if (simon->AutoWalk(simon->GetPosXStair()))
		{
			simon->isOnStair = true;
			simon->isTouchStairBottom = false;
		}
		else
			return;
	}
	if (simon->isOnStair)
	{
		if (game->IsKeyDown(DIK_UP))
			simon->GoUpStair();
		else if (game->IsKeyDown(DIK_DOWN))
			simon->GoDownStair();
		else
			simon->StandOnStair();
		return;
	}

	if (!simon->isGrounded || simon->isOnStair)
		return;

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
		if (simon->isGrounded)
		{
			simon->SetState(SIMON_IDLE);
		}
	}
}