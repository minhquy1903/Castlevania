#pragma once
#include"GameObject.h"

#define KNIFE 0
class SubWeapon :public CGameObject
{
public:
	float posX; // vị trí simon lúc thực hiện ném dao
	bool isHittingSubWeapon;
	bool isSubWeaponExist;
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	void Render();
	virtual void SetPosSubWeapon(D3DXVECTOR3 pos, bool isStanding);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void SetDirectionSubWeapon(int nx) = 0;
	void SubWeaponCollideWithCandle(vector<LPGAMEOBJECT>* coObjects);
	SubWeapon();
	SubWeapon(int state);
	~SubWeapon();
};

