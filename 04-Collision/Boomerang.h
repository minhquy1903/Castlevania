#pragma once
#include "SubWeapon.h"
#define ANIMATION_BOOMERANG 9
#define VX_BOOMERANG 0.5f
class Boomerang : public SubWeapon
{
	
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	void Render();
	void SetDirectionSubWeapon(int nx);
	bool CheckExistBoomerang(float a);
	void TimeStart();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	Boomerang();
	~Boomerang();
};

