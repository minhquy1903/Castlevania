#pragma once
#include "GameObject.h"
#define ITEM_UPGRADE_WHIP	0
#define ITEM_HEART			1
#define ITEM_KNIFE			2
class Item : public CGameObject
{
	DWORD lifeTimeStart;
	DWORD lifeTime;
	DWORD timeFlicker;
	bool isFlicker;
public:
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	Item();
	~Item();
};

