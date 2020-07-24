#pragma once
#include "SubWeapon.h"
#define BOOMERANG_ANIMATION_SETS 10
#define BOOMERANG_SPEED 0.4
#define GRAVITY_PULL	0.006;
#define SCREEN_WIDTH	530
class Boomerang : public SubWeapon
{
	
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	void Render();
	void SetDirectionSubWeapon(int nx);
	bool CheckPosBoomerang(float a);
	void SubWeaponCollideWithSimon(LPGAMEOBJECT simon);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	Boomerang();
	~Boomerang();
};

