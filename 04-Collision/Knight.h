#pragma once
#include "GameObject.h"

class Knight : public CGameObject
{
	bool isTurning;
public:
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void SetState(int state);
	Knight();
	~Knight();
};

