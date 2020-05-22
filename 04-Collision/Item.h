#pragma once
#include "GameObject.h"
#define ITEM_UPGRADE_WHIP	0
#define ITEM_HEART			1
#define ITEM_KNIFE			2
#define ITEM_BOOMERANG		3

#define TIME_FLICKER		1500
#define LIFE_TIME			3000

class Item : public CGameObject
{
	DWORD lifeTimeStart;
	DWORD lifeTime;
	DWORD timeFlicker;//chớp
	bool isTimeOut;
	bool isFlicker;
public:
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	bool GetTimeOut() { return isTimeOut; }
	void Render();
	Item();
	~Item();
};

