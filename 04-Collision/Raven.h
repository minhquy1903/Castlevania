#pragma once
#include "Enemy.h"

#define RAVEN_BBOX	32

#define RAVEN_IDLE	0
#define SPEED_RAVEN 0.13
#define HEALTH	1
#define DAME	3

#define RAVEN_IDLE	0
#define RAVEN_FLY	1
#define RAVEN_DEAD	2

#define RANGE_ACTIVE	230
#define RANGE_STOP		150
#define TIME_STOP1		75
#define TIME_STOP2		190
class Raven : public Enemy
{
public:
	bool active;
	int stop;
public:
	Raven();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL, LPGAMEOBJECT simon = NULL);
	void Render();
	void SetState(int state);
	void ChasingSimon(int x, int y);
	~Raven();
};

