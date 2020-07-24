#pragma once
#include "Enemy.h"

#define BOSS_BBOX_WIDTH		64
#define	BOSS_BBOX_HEIGHT	46
#define DEAD	2
#define BOSS_SLEEP	0
#define BOSS_WAKEUP	1
class Boss : public Enemy
{
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL, LPGAMEOBJECT simon = NULL);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void ChasingSimon(double x, double y);
};

