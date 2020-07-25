#pragma once
#include "Enemy.h"

#define BOSS_BBOX_WIDTH		64
#define	BOSS_BBOX_HEIGHT	46
#define RANGE_BOSS_ACTIVE	96
#define BOSS_SLEEP	0
#define BOSS_WAKEUP 1
#define DEAD 2
#define BOSS_TIME 900

#define HP_BOSS 16
#define BOSS_DAME 2
#define MAX_DISTANCE 900
#define RAND_MIN 80
#define SCREEN_BOX_LEFT -32
#define SCREEN_BOX_RIGHT 420
#define SCREEN_BOX_UP 100
#define SCREEN_BOX_DOWN 380
#define MAX_DISTANCE_RIGHT_LEFT 150
#define MAX_DISTANCE_UP_DOWN 100
#define VX 0.12
#define VY 0.05
#define VY_DOWN 0.09
#define ADD_X 13
#define VX_CLOSE 0.12
#define TIME_ATTACK_STOP 1500

class Boss : public Enemy
{
public:
	bool checkactive, 
		 target, 
		 checkstop, 
		 fly;
	DWORD time, timeDelay;
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL, LPGAMEOBJECT simon = NULL);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void SetState(int state);
	Boss();
	void ChasingSimon(double x, double y);
};

