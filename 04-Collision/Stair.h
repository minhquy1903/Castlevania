#pragma once
#include "GameObject.h"

class Stair : public CGameObject
{
	int midStairX;
public:
	void Render();
	void RenderBoundingBox();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	Stair(int x, int y, int directionX, int directionY);
	int GetMidStair() { return midStairX; }
	Stair();
	~Stair();
};

