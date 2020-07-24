#pragma once
#include "Sprites.h"
#include "Simon.h"
#include "GameObject.h"
#include <string>

#define LIFE_TIME 300
#define HP_SIMON_AND_BOSS	16
#define A_MINUTE	60
class BoardScore
{
	vector<LPSPRITE> healthbar;
	LPSPRITE number;
	LPSPRITE subweapon;
	int idSubWeapon;
	int healthSimon, healthSimonLost, healthBoss, healthBossLost;
	int posX;
	int posY;
	int score;
	int heart;
	int life;
	int time;
	void DrawHealth();
	void DrawBoard();
	void DrawNumber(int x, int y, string a);
	void DrawSubWeapon();
	void DrawParameter();
public:
	void Update(DWORD dt, int camX, int camY, LPGAMEOBJECT simon, LPGAMEOBJECT boss = NULL);
	void Render();
	
	BoardScore();
	~BoardScore();
};

