#pragma once
#include "Enemy.h"

#define	KNIGHT_IS_HIT	1
#define KNIGHT_WALK		0
#define KNIGHT_DEAD		2

#define KNIGHT_ANI		0

#define KNIGHT_WALK_SPEED 0.1f
#define KNIGHT_BBOX_WIDTH	32
#define KNIGHT_BBOX_HEIGHT	64
#define DELAY_TIME			260
#define HEALTH				3
#define DAME				2
#define VY					0.1f

class Knight : public Enemy
{
	bool isTurning;
	DWORD timeDelay;
public:
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL, LPGAMEOBJECT simon = NULL);
	void Render();
	void SetState(int state);
	int GetHP() { return hp; }
	void SetHP(int HP) { hp = HP; }
	Knight();
	~Knight();
};

