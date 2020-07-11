#pragma once
#include "SubWeapon.h"
#define GRAVITY	0.002f
#define HOLYWATER_BBOX	32
#define VX_HOLYWATER	0.06
class HolyWater : public SubWeapon
{
	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	void Render();
	void SetDirectionSubWeapon(int nx);
	//bool CheckExistKnife(float a);
	void TimeStart();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	HolyWater() {};
	~HolyWater() {};
};

