#pragma once
#include "GameObject.h"



class Whip : public CGameObject
{
	
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	void Render();
	void Render(int currentID = -1);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	bool WhipColision(float l_b, float t_b, float r_b, float b_b);
	Whip();
	~Whip();
};

