#pragma once
#include "Enemy.h"

#define FLEAMAN_BBOX_WIDTH 32
#define FLEAMAN_BBOX_HEIGHT 32

#define IDLE 0
#define JUMP 1
#define DEAD 2
#define GRAVITY 0.002f

class Fleaman : public Enemy
{
public:
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL, LPGAMEOBJECT simon = NULL);
	void Render();
	void SetState(int state);
	void ChasingSimon(int x, int y);
	int GetHP() { return hp; }
	void SetHP(int HP) { hp = HP; }
	Fleaman();
	~Fleaman();
};

