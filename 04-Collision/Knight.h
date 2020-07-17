#pragma once
#include "Enemy.h"

#define	KNIGHT_IS_HIT	2
#define WALK		0
#define DEAD		1

#define KNIGHT_ANI		0

#define KNIGHT_WALK_SPEED 0.09f
#define KNIGHT_BBOX_WIDTH	32
#define KNIGHT_BBOX_HEIGHT	64
#define DELAY_TIME			260
#define HEALTH				3
#define DAME				2
#define VY					0.1f
#define GRAVITY				0.002
class Knight : public Enemy
{
	bool isTurning;
	DWORD timeDelay;
public:
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL, LPGAMEOBJECT simon = NULL);
	void Render();
	void SetState(int state);
	Knight();
	~Knight();
};

