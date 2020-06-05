#pragma once
#include "GameObject.h"

#define BRIDGE_BBOX_WIDTH	64
#define BRIDGE_BBOX_HEIGHT	16
#define BRIDGE_SPEED		0.06f
class Bridge : public CGameObject
{
public:
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	Bridge();
	~Bridge();
};

