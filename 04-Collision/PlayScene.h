#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Simon.h"
#include "Brick.h"
#include "Whip.h"
#include "Candle.h"
#include "Item.h"
#include "TileMap.h"
#include "BoardScore.h"

class CPlayScene : public CScene
{
protected:
	CSimon *player;					// A play scene has to have player, right? 
	TileMap *tilemap; 
	BoardScore * boardscore;
	vector<LPGAMEOBJECT> bricks;
	vector<LPGAMEOBJECT> Candles;
	vector<LPGAMEOBJECT> listItem;
	vector<LPGAMEOBJECT> portal;
	vector<LPGAMEOBJECT> stairs;
	
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_TILEMAP(string line);

public:
	CPlayScene(int id, LPCWSTR filePath);
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	virtual void SetPlayer(CSimon* player) { this->player = player; }
	CSimon * GetPlayer() { return player; }

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

