#pragma once
#include "Enemy.h"

#define ZOMBIE_WALK 0
#define	DEAD		1

#define GRAVITY	0.002
#define	VX_ZOMBIE	0.1
#define VY_ZOMBIE	0.1
#define HEALTH		1
#define DAME		1

class Zombie : public Enemy
{
public:
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL, LPGAMEOBJECT simon = NULL);
	void Render();
	void SetState(int state);
	Zombie(int nx);
	Zombie();
	~Zombie();
};

