#pragma once
#include"SubWeapon.h"

#define knife_ani 0
#define KNIFE_ANIMATION_SET 5

#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 480
class Knife :public SubWeapon
{
	float POSX;
public:

	Knife();
	~Knife();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	void Render();
	//void Render(int currentID = -1);
	
	void SetPosSubWeapon(D3DXVECTOR3 pos, bool isstanding);
	bool CheckPosKnife(float a);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};
