#pragma once
#include "GameObject.h"

class StairTop : public CGameObject 
{

public:
	void Render();
	void RenderBoundingBox();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	StairTop(int direction, int x, int y);
	StairTop();
	~StairTop();
};

