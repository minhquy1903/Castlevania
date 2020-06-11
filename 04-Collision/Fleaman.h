#pragma once
#include "Enemy.h"

#define FLEAMAN_BBOX_WIDTH		32
#define FLEAMAN_BBOX_HEIGHT		32
#define FLEAMAN_

#define JUMP_HIGH				0
#define JUMP_LOW				1
#define DEAD					2
#define ANI_DEAD				1

#define FLEAMAN_SPPED_Y_HIGH	-0.63f
#define FLEAMAN_SPEED_Y_LOW		-0.2f
#define FLEAMAN_SPEED			0.2f
#define GRAVITY					0.002f
#define FLEAMAN_HP				1
#define FLEAMAN_DAME			3

#define AREA_TURNING			150
#define JUMP_RATE				2000
#define JUMP_RATE_MAX			10000
#define AREA_ACTIVE				150


class Fleaman : public Enemy
{
	bool firstJump,
		 isGround;
	
public:
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL, LPGAMEOBJECT simon = NULL);
	void Render();
	void SetState(int state);
	void ChasingSimon(double x, double y);
	
	Fleaman();
	~Fleaman();
};

