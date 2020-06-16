#pragma once
#include "GameObject.h"

#define WIDTH_BBOX_STAIR	32

class Stair : public CGameObject
{
public:
	int pair;
	int midStairX;
	int typeStair;
public:
	void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	Stair(int x, int y, int directionX,int typeStair, int pair);
	int GetMidStair() { return midStairX; }
	Stair();
	~Stair();
};

