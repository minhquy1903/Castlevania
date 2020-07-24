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
#include "Ghost.h"
#include "Bridge.h"
#include "Fleaman.h"
#include "Skeleton.h"
#include "Raven.h"
#include "Zombie.h"
using namespace std;

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_RESOURCE	0
#define SCENE_SECTION_OBJECTS	6
#define SCENE_SECTION_TILEMAP 7
#define OBJECT_TYPE_SIMON	0
#define OBJECT_TYPE_BRICK	1
#define OBJECT_TYPE_SECRETOBJ	2
#define OBJECT_TYPE_ITEM	3
#define OBJECT_TYPE_STAIR	4
#define OBJECT_TYPE_ENEMY	5
#define OBJECT_TYPE_BRIDGE	6
#define OBJECT_TYPE_PORTAL	50
#define MAX_SCENE_LINE		1024

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_TEXTURES 2
#define SCENE_SECTION_SPRITES 3
#define SCENE_SECTION_ANIMATIONS 4
#define SCENE_SECTION_ANIMATION_SETS	5
#define MAX_SCENE_LINE 1024
CPlayScene::CPlayScene(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	key_handler = new CPlayScenceKeyHandler(this);
}


/*
	Load scene resources from scene file (textures, sprites, animations and objects)
	See scene1.txt, scene2.txt for detail format specification
*/

bool ignoreRender = false;

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
		if (line == "[TEXTURES]")
		{
			section = SCENE_SECTION_TEXTURES;
			continue;
		}
		if (line == "[SPRITES]")
		{
			section = SCENE_SECTION_SPRITES;
			continue;
		}
		if (line == "[ANIMATIONS]")
		{
			section = SCENE_SECTION_ANIMATIONS;
			continue;
		}
		if (line == "[ANIMATION_SETS]")
		{
			section = SCENE_SECTION_ANIMATION_SETS;
			continue;
		}

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
		case SCENE_SECTION_TEXTURES:
			_ParseSection_TEXTURES(line);
			break;
		case SCENE_SECTION_SPRITES:
			_ParseSection_SPRITES(line);
			break;
		case SCENE_SECTION_ANIMATIONS:
			_ParseSection_ANIMATIONS(line);
			break;
		case SCENE_SECTION_ANIMATION_SETS:
			_ParseSection_ANIMATION_SETS(line);
			break;
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

	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
	CGameObject* obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_SIMON:
		if (player != NULL)
		{
			player->SetAnimationSet(ani_set);
			player->NewWhip();
			player->whip->state = player->whipLvl;
			return;
			DebugOut(L"[ERROR] SIMON object was created before!\n");
			break;
		}
		else
		{
			obj = new Simon();
			player = (Simon*)obj;
			player->SetAnimationSet(ani_set);
			player->SetPosition(x, y);
			return;
			DebugOut(L"[INFO] Player object created!\n");
			
		}
		break;
	case OBJECT_TYPE_BRICK:
	{
		int nWidth = atoi(tokens[4].c_str());
		int nHeight = atoi(tokens[5].c_str());
		obj = new Brick(nWidth, nHeight);
	}
		
		break;
	case OBJECT_TYPE_SECRETOBJ:
	{
		int iditem = atof(tokens[4].c_str());
		int typeObj = atof(tokens[5].c_str());
		if (typeObj == 0)
			obj = new Torch(iditem);
		else
			obj = new Candle(iditem);
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
		else if (typeEnemy == 2)
		{
			obj = new Ghost();
		}
		else if (typeEnemy == 3)
		{
			obj = new Fleaman();
		}
		else if (typeEnemy == 4)
		{
			int nx = atoi(tokens[5].c_str());
			obj = new Skeleton(nx);
			Skeleton* skeleton = dynamic_cast<Skeleton*>(obj);
			skeleton->GetBone()->SetPosition(x, y);
			allObject.push_back(skeleton->GetBone());
		}
		else if (typeEnemy == 5)
		{
			obj = new Raven();
		}
		else if (typeEnemy == 6)
		{

			int nx = atoi(tokens[5].c_str());
			obj = new Zombie(nx);
		}
			
		break;
	}
	case OBJECT_TYPE_STAIR:
	{
		int DirectionX = atof(tokens[4].c_str()); // chiều X cầu thang
		int typeStair = atof(tokens[5].c_str());// loại cầu thang đi lên hay xuống
		int Pair = atof(tokens[6].c_str());// cặp cầu thang <cùng cặp mới tương tác với nhau>
		obj = new Stair(x, y, DirectionX, typeStair, Pair);
		break;
	}
	case OBJECT_TYPE_BRIDGE:
	{
		obj = new Bridge();
		break;
	}

	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}
	obj->SetAnimationSet(ani_set);
	obj->SetPosition(x, y);
	allObject.push_back(obj);
	
}


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

	CAnimations* animations = CAnimations::GetInstance();

	for (int i = 1; i < tokens.size(); i++)
	{
		int ani_id = atoi(tokens[i].c_str());

		LPANIMATION ani = animations->Get(ani_id);
		s->push_back(ani);
	}

	CAnimationSets::GetInstance()->Add(ani_set_id, s);
}

void CPlayScene::_ParseSection_TILEMAP(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 13) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	wstring filePath_texture = ToWSTR(tokens[1]);
	wstring filePath_data = ToWSTR(tokens[2]);
	int num_row_on_texture = atoi(tokens[3].c_str());
	int num_col_on_textture = atoi(tokens[4].c_str());
	int num_row_on_tilemap = atoi(tokens[5].c_str());
	int num_col_on_tilemap = atoi(tokens[6].c_str());
	int tileset_width = atoi(tokens[7].c_str());
	int tileset_height = atoi(tokens[8].c_str());
	int xCam = atoi(tokens[9].c_str());
	int yCam = atoi(tokens[10].c_str());
	int widthGrid = atoi(tokens[11].c_str());
	int heightGrid = atoi(tokens[12].c_str());
	boardscore = new BoardScore();
	grid = new Grid();
	//1590	500
	CGame::GetInstance()->SetCamPos(xCam, yCam);
	grid->Resize(widthGrid, heightGrid);
	grid->PushGrid(allObject);
	tilemap = new TileMap(ID, filePath_texture.c_str(), filePath_data.c_str(), num_row_on_texture, num_col_on_textture, num_row_on_tilemap, num_col_on_tilemap, tileset_width, tileset_height);
}

void CPlayScene::SimonRevival()
{
	ignoreRender = true;
	if (player->life == 0)
	{
		player = NULL;
		CGame::GetInstance()->SetCamPos(0, 0.0f);
		CGame::GetInstance()->SwitchScene(1);
		grid->PushGrid(allObject);
		return;
	}
	int currentLife = player->life;
	player = NULL;
	CGame::GetInstance()->SetCamPos(0, 0.0f);
	CGame::GetInstance()->SwitchScene(id);
	grid->PushGrid(allObject);
	player->life = currentLife - 1;
}

void CPlayScene::GetObjectGrid()
{
	ObjectInScreen.clear();
	//allObject.clear();
	portal.clear();
	bricks.clear();
	secretObj.clear();
	enemies.clear();
	stairs.clear();
	grid->GetGrid(ObjectInScreen);
}

void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 
	GetObjectGrid();
	int sizeVector = ObjectInScreen.size();
	for (size_t i = 0; i < sizeVector; i++)
	{
		LPGAMEOBJECT obj = ObjectInScreen[i];
		if (dynamic_cast<CPortal*>(obj))
			portal.push_back(obj);
		else if (dynamic_cast<Brick*>(obj))
			bricks.push_back(obj);
		else if (dynamic_cast<Candle*>(obj) || dynamic_cast<Torch*>(obj))
			secretObj.push_back(obj);
		else if (dynamic_cast<Enemy*>(obj))
		{
			LPENEMY enemy = (LPENEMY)obj;
			enemies.push_back(enemy);
		}
		else if (dynamic_cast<Stair*>(obj))
			stairs.push_back(obj);
	}

	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 1; i < bricks.size(); i++)
	{
		coObjects.push_back(bricks[i]);
	}
	coObjects.push_back(player);

	for (size_t i = 1; i < bricks.size(); i++)
	{
		bricks[i]->Update(dt, &bricks);
	}

	player->Update(dt);

	for (int i = 0; i < player->weapon.size(); i++)
	{
		if (player->weapon[i]->isSubWeaponExist && player->subWeaponIsON)
		{
			player->weapon[i]->Update(dt, &bricks);
		}
	}

	player->CollodeWhitBirck(&bricks);

	player->SimonTouchStair(&stairs);// simon chạm cầu thang

	if ((player->GetState() == SIMON_STAND_HIT && player->animation_set->at(SIMON_STAND_HIT)->GetCurrentFrame() == 2) ||
		(player->GetState() == SIMON_SIT_HIT && player->animation_set->at(SIMON_SIT_HIT)->GetCurrentFrame() == 2) ||
		player->GetState() == SIMON_STAIR_UP_HIT && player->animation_set->at(SIMON_STAIR_UP_HIT)->GetCurrentFrame() == 2 ||
		player->GetState() == SIMON_STAIR_DOWN_HIT && player->animation_set->at(SIMON_STAIR_DOWN_HIT)->GetCurrentFrame() == 2)
	{
		for (int i = 0; i < player->weapon.size(); i++)
		{
			if (player->weapon[i]->isHittingSubWeapon) // simon đang thực hiên động tác đánh
			{
				player->weapon[i]->isSubWeaponExist = true;//subweapon đc update và render
				if (player->GetState() == SIMON_SIT_HIT)
					player->weapon[i]->SetPosSubWeapon(D3DXVECTOR3(player->x, player->y, 0), false, player->nx);
				else
					player->weapon[i]->SetPosSubWeapon(D3DXVECTOR3(player->x, player->y, 0), true, player->nx);

			}
			else
			{
				player->GetWhip()->Update(dt);//update whip
				player->GetWhip()->CollideWithSecretObj(&secretObj);
				player->GetWhip()->CollideWithSecretEnemies(&enemies);
			}
		}
	}

	for (int i = 0; i < player->weapon.size(); i++)
	{
		if (player->weapon[i]->isSubWeaponExist) //kiểm tra subweapon va chạm với torch va candle
		{
			player->weapon[i]->SubWeaponCollideWithSecretObj(&secretObj);
			player->weapon[i]->SubWeaponCollideWithEnemy(&enemies);
			player->weapon[i]->SubWeaponCollideWithSimon(player);
		}
	}
	


	for (size_t i = 0; i < secretObj.size(); i++)
	{
		LPGAMEOBJECT obj = secretObj[i];
		secretObj[i]->Update(dt);
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
		}
		else if (dynamic_cast<Candle*>(obj))
		{
			Candle* candle = dynamic_cast<Candle*>(obj);
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

	if (GetTickCount() - player->timeClock > TIME_CLOCK)// xử lí clock
	{
		player->clockOn = false;
	}
	if (player->clockOn)
		Enemy::clockOn = true;
	else
		Enemy::clockOn = false;

	for (int i = 0; i < enemies.size(); i++)//quái update
	{
		enemies[i]->Update(dt, &bricks, player);
		if (enemies[i]->renderFireDone)
		{
			enemies[i]->DropItem();
			listItem.push_back(enemies[i]->GetItem());
		}
	}

	player->CollideWithEnemy(&enemies);//simon va chạm với quoái

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
			listItem[i]->Update(dt, &bricks);
	}

	player->CollideWithItem(&listItem); //kiểm tra simon nhặt item

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return;

	// Update camera to follow mario
	float cx, cy;
	player->GetPosition(cx, cy);

	CGame* game = CGame::GetInstance();
	cx += game->GetScreenWidth() / 2;
	cy -= game->GetScreenHeight() / 2;



	if (player->x > (SCREEN_WIDTH / 2) && player->x + (SCREEN_WIDTH / 2) < tilemap->GetWidthTileMap())
	{
		cx = player->x - (SCREEN_WIDTH / 2);
		CGame::GetInstance()->SetCamPos(cx, 0.0f);
	}
	//DebugOut(L"tileWidth: %d\n", tilemap->GetWidthTileMap());

	boardscore->Update(dt, CGame::GetInstance()->GetCamPosX(), 0, player);

	grid->ResetGrid(allObject);

	
	if (int idScene = player->CollideWithPortal(&portal)) //kiểm tra simon đi vào cổng
	{
		//portal.at(0).idscene();
		CGame::GetInstance()->SetCamPos(0, 0.0f);
		CGame::GetInstance()->SwitchScene(idScene, player);
		ignoreRender = true;
	}
	if (player->revival)
	{
		SimonRevival();
	}
}

void CPlayScene::Render()
{
	if (ignoreRender)
	{
		ignoreRender = false;
		return;
	}
	tilemap->Draw();
	boardscore->Render();
	for (int i = 0; i < bricks.size(); i++)
		bricks[i]->Render();
	for (size_t i = 0; i < secretObj.size(); i++)
		secretObj[i]->Render();
	for (int i = 0; i < listItem.size(); i++)
		listItem[i]->Render();
	for (int i = 0; i < enemies.size(); i++)
		enemies[i]->Render();
	for (int i = 0; i < portal.size(); i++)
		portal[i]->Render();
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
	for (int i = 0; i < allObject.size(); i++)
		delete allObject[i];
	/*for (int i = 0; i < listItem.size(); i++)
		delete listItem[i];*/
	for (auto item : listItem)
		delete item;

	CTextures::GetInstance()->Clear();
	CSprites::GetInstance()->Clear();
	CAnimations::GetInstance()->Clear();

	listItem.clear();
	allObject.clear();
	//player = NULL;

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}


void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	Simon* simon = ((CPlayScene*)scence)->GetPlayer();
	if (simon->isDead)
		return;
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	if (simon->GetState() == SIMON_SHOCK)
		return;
	if ((simon->GetState() == SIMON_STAIR_UP_HIT && !(simon->animation_set->at(SIMON_STAIR_UP_HIT)->IsRenderOver(300))) ||
		(simon->GetState() == SIMON_STAIR_DOWN_HIT && !simon->animation_set->at(SIMON_STAIR_DOWN_HIT)->IsRenderOver(300)))
		return;

	switch (KeyCode)
	{
	case DIK_SPACE:
		simon->Jump();
		break;
	case DIK_A:
		if (CGame::GetInstance()->IsKeyDown(DIK_UP))
			simon->UseSubweapon();
		else
		{
			simon->Hit();
			simon->normalHit = true;
		}
			
		break;
	case DIK_2:
		CGame::GetInstance()->SwitchScene(2, simon);
		simon->SetPosition(80, 300);
		CGame::GetInstance()->SetCamPos(0.0f, 0.0f);
		break;
	case DIK_3:
		CGame::GetInstance()->SwitchScene(3, simon);
		simon->SetPosition(128, 80);
		CGame::GetInstance()->SetCamPos(0.0f, 0.0f);
		break;
	case DIK_4:
		CGame::GetInstance()->SwitchScene(4, simon);
		simon->SetPosition(300, 300);
		CGame::GetInstance()->SetCamPos(0.0f, 0.0f);
		break;
	case DIK_5:
		CGame::GetInstance()->SwitchScene(5, simon);
		simon->SetPosition(80, 0);
		CGame::GetInstance()->SetCamPos(0.0f, 0.0f);
		break;
	case DIK_6:
		CGame::GetInstance()->SwitchScene(6, simon);
		simon->SetPosition(80, 0);
		CGame::GetInstance()->SetCamPos(0.0f, 0.0f);
		break;
	case DIK_H:
		simon->health = 2;
		break;
	case DIK_K:
		simon->life = 0;
		break;
	}
}

void CPlayScenceKeyHandler::KeyState(BYTE* states)
{
	CGame* game = CGame::GetInstance();
	Simon* simon = ((CPlayScene*)scence)->GetPlayer();

	if (simon->isDead)
		return;

	if (simon->GetState() == SIMON_DEAD)
		return;

	if (simon->GetState() == SIMON_HURT && !simon->animation_set->at(SIMON_HURT)->IsRenderOver(400))
		return;

	if (simon->GetState() == SIMON_SHOCK && !(simon->animation_set->at(SIMON_SHOCK)->IsRenderOver(600)))
		return;
	if ((simon->GetState() == SIMON_STAIR_UP && !simon->animation_set->at(SIMON_STAIR_UP)->IsRenderOver(200)) || (simon->GetState() == SIMON_STAIR_DOWN && !simon->animation_set->at(SIMON_STAIR_DOWN)->IsRenderOver(200)))
		return;
	if ((simon->GetState() == SIMON_STAND_HIT && !(simon->animation_set->at(SIMON_STAND_HIT)->IsRenderOver(300))) ||
		(simon->GetState() == SIMON_SIT_HIT && !simon->animation_set->at(SIMON_SIT_HIT)->IsRenderOver(300)))
		return;

	if ((simon->GetState() == SIMON_STAIR_UP_HIT && !(simon->animation_set->at(SIMON_STAIR_UP_HIT)->IsRenderOver(300))) || (simon->GetState() == SIMON_STAIR_DOWN_HIT && !simon->animation_set->at(SIMON_STAIR_DOWN_HIT)->IsRenderOver(300)))
		return;

	for (int i = 0; i < simon->weapon.size(); i++)
	{
		if ((simon->GetState() == SIMON_STAND_HIT && (simon->animation_set->at(SIMON_STAND_HIT)->IsRenderOver(300))) ||
			(simon->GetState() == SIMON_SIT_HIT && simon->animation_set->at(SIMON_SIT_HIT)->IsRenderOver(300)))
		{
			simon->weapon[i]->isHittingSubWeapon = false;
			simon->normalHit = false;
			if (!simon->isGrounded)
				simon->SetState(SIMON_JUMP);
		}
	}
	

	if (simon->isTouchStairTop && game->IsKeyDown(DIK_DOWN) && !simon->isOnStair)
	{
		if (simon->AutoWalk(simon->GetPosXStair()))
		{
			if (simon->nxStairTop == 1)
				simon->pairStair = -1;
			else
				simon->pairStair = 1;

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
			if (simon->nxStairBottom == 1)
				simon->pairStair = 1;
			else
				simon->pairStair = -1;

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
		{
			simon->GoDownStair();
		}
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