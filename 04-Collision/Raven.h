#pragma once
#include "Enemy.h"

#define RAVEN_BBOX	32

#define RAVEN_IDLE	0
#define SPEED_RAVEN 0.1
#define HEALTH	1
#define DAME	3

class Raven : public Enemy
{
public:
	Raven();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL, LPGAMEOBJECT simon = NULL);
	void Render();
	void SetState(int state);
	
	~Raven();
};

