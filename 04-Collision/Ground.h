#pragma once
#include "GameObject.h"

#define GROUND_ID		  10
#define GROUND_ANI		  11	
#define BRICK_BBOX_WIDTH  64
#define BRICK_BBOX_HEIGHT 32

class CGround : public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};