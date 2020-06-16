#pragma once
#include "Game.h"
#include "Scene.h"
#include "GameObject.h"
#include "Simon.h"
#include "TileMap.h"
#include "BoardScore.h"
#include "Enemy.h"

class CPlayScene : public CScene
{
protected:
	Simon *player;					// A play scene has to have player, right? 
	TileMap *tilemap; 
	BoardScore * boardscore;
	vector<LPGAMEOBJECT> bricks;
	vector<LPGAMEOBJECT> secretObj;
	vector<LPGAMEOBJECT> listItem;
	vector<LPGAMEOBJECT> portal;
	vector<LPGAMEOBJECT> stairs;
	vector<LPENEMY> enemies;
	
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
	Simon * GetPlayer() { return player; }

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

