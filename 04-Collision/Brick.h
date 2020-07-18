#pragma once
#include "GameObject.h"

#define GROUND_ID		  1
#define BRICK_BBOX_WIDTH  32
#define BRICK_BBOX_HEIGHT 32

class Brick : public CGameObject
{
	int nWidth;
	int nHeight;
public:
	Brick();
	Brick(int nw, int nh);
	void Render();
	void GetBoundingBox(float &l, float &t, float &r, float &b);
};