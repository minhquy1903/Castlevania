#pragma once
#include "GameObject.h"



class Whip : public CGameObject
{

public:
	void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	void Render();
	void Render(int currentID = -1);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	Whip();
	~Whip();
};

