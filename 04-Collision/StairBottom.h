#pragma once
#include "GameObject.h"

class StairBottom : public CGameObject
{
public:
	void Render();
	void RenderBoundingBox();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	StairBottom(int direction, int x, int y);
	StairBottom();
	~StairBottom();
};

