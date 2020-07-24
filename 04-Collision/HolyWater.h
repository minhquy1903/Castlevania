#pragma once
#include "SubWeapon.h"
#define GRAVITY	0.002f
#define HOLYWATER_BBOX	32
#define VX_HOLYWATER	0.17
#define VY_HOLYWATER	0.42
#define HOLYWATER_ANIMATION_SETS	18
#define STATE_NORMAL	0
#define STATE_FIRE	1
class HolyWater : public SubWeapon
{
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	void Render();
	void SetDirectionSubWeapon(int nx);
	//bool CheckExistKnife(float a);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	HolyWater();
	~HolyWater() {};
};

