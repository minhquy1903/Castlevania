#pragma once
#include "GameObject.h"

#define WHIP_LVL_1 0
#define WHIP_LVL_2 1
#define WHIP_LVL_3 2

class Whip : public CGameObject
{
	bool isHit;
	
public:
	int CurrentFrame;
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();
	void SetHit(int ishit) { isHit = ishit; }
	bool GetHit() { return isHit; }
	void Render(int currentID = -1);
	void WhipCollideWithCandle(vector<LPGAMEOBJECT>* coObjects);
	
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	Whip();
	~Whip();
};

