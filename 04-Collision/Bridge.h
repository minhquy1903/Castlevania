#pragma once
#include "GameObject.h"

class Bridge : public CGameObject
{
public:
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	Bridge();
	~Bridge();
};

