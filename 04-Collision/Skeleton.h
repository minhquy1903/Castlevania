#pragma once
#include "Enemy.h"
#include "Bone.h"
#define SKELETON_BBOX_WIDTH		32
#define SKELETON_BBOX_HEIGHT	63

#define SKELETON_SPEED_X		0.12f
#define SKEKETON_SPEED_Y		0.4f
#define GRAVITY					0.002f

#define JUMP					0
#define DEAD					1
#define WALK					2

#define ANI_SKELETON			0

#define AREA_ACTIVE				190
#define AREA_TURNING1			180
#define AREA_TURNING2			30
#define AREA_TURNING3			210
#define AREA_TURNING4			60

#define SKELETON_HP				1
#define DAME					3
#define SIZE_BONE				450

class Skeleton : public Enemy
{
	Bone * bone;
	int isGrounded;
	bool active;
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL, LPGAMEOBJECT simon = NULL);
	void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void ChasingSimon(double x, double y);
	void SetState(int state);
	Bone* GetBone() { return bone; }
	Skeleton();
	~Skeleton();
};

