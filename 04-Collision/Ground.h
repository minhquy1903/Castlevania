#pragma once
#include "GameObject.h"

#define GROUND_ID		  1
#define BRICK_BBOX_WIDTH  64
#define BRICK_BBOX_HEIGHT 32

class CGround : public CGameObject
{
public:
	CGround();
	void Render();
	void GetBoundingBox(float &l, float &t, float &r, float &b);
};