#pragma once
#include"SubWeapon.h"

#define KNIFE_ANI 0
#define KNIFE_ANIMATION_SET 5
#define VX_KNIFE 0.32f

#define SCREEN_WIDTH 530
#define SCREEN_HEIGHT 500
class Knife :public SubWeapon
{
	
public:

	Knife();
	~Knife();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	void Render();
	void SetDirectionSubWeapon(int nx);
	bool CheckExistKnife(float a);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};
