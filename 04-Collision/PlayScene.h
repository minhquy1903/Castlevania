#pragma once
#include "Game.h"
#include "Scene.h"
#include "GameObject.h"
#include "Simon.h"
#include "TileMap.h"
#include "BoardScore.h"
#include "Enemy.h"
#include "Grid.h"
#include "Boss.h"

class CPlayScene : public CScene
{
protected:
	Simon *player;					// A play scene has to have player, right? 
	TileMap *tilemap; 
	BoardScore * boardscore;
	Grid* grid;
	Boss* boss;
	vector<LPGAMEOBJECT> bricks;
	vector<LPGAMEOBJECT> secretObj;
	vector<LPGAMEOBJECT> listItem;
	vector<LPGAMEOBJECT> portal;
	vector<LPGAMEOBJECT> stairs;
	vector<LPGAMEOBJECT> allObject;
	vector<LPENEMY> enemies;
	vector<LPGAMEOBJECT> ObjectInScreen;
	
	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_TILEMAP(string line);

public:

	CPlayScene(int id, LPCWSTR filePath);
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	void SimonRevival();
	virtual void SetPlayer(Simon* player) { this->player = player; }
	void GetObjectGrid();
	Simon * GetPlayer() { return player; }
	~CPlayScene() {};
	//friend class CPlayScenceKeyHandler;
};

class CPlayScenceKeyHandler : public CScenceKeyHandler
{
public:
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode) {};
	CPlayScenceKeyHandler(CScene *s) :CScenceKeyHandler(s) {};
};

