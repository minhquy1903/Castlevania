#pragma once
#include"SubWeapon.h"

#define KNIFE_ANI 0
#define KNIFE_ANIMATION_SET 5
#define VX_KNIFE 0.1f

#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 480
class Knife :public SubWeapon
{
	
public:

	Knife();
	~Knife();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	void Render();
	void SetDirectionSubWeapon(int nx);
	bool CheckExistKnife(float a);
	void TimeStart();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};
