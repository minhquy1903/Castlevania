#pragma once
#include "Enemy.h"

#define BONE_SPEED_X	0.15
#define BONE_SPEED_Y	-0.42
#define GRAVITY			0.001
#define BONE_BBOX_WIDTH_HEIGHT	24
#define DAME_BONE		3
class Bone : public Enemy
{
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL, LPGAMEOBJECT simon = NULL);
	void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	Bone();
	~Bone();
};

