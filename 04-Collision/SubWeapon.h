#pragma once
#include"GameObject.h"

#define KNIFE 0
class SubWeapon :public CGameObject
{
public:
	bool isHittingSubWeapon;
	bool isSubWeaponExist;
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	void Render();
	virtual void SetPosSubWeapon(D3DXVECTOR3 pos, bool isstanding);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void SetDirectionKnife(int nx);
	void SubWeaponCollideWithCandle(vector<LPGAMEOBJECT>* coObjects);
	SubWeapon();
	SubWeapon(int state);
	~SubWeapon();
};

