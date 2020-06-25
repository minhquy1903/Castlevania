#pragma once
#include"GameObject.h"

#define KNIFE 0
class SubWeapon :public CGameObject
{
	int id;
public:
	DWORD timeExist;
	float posX; // vị trí simon lúc thực hiện ném dao
	bool isHittingSubWeapon;
	bool isSubWeaponExist;
	bool active;
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	void Render();
	virtual void SetPosSubWeapon(D3DXVECTOR3 pos, bool isStanding);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void SetDirectionSubWeapon(int nx) = 0;
	virtual void TimeStart() = 0;
	void SubWeaponCollideWithSecretObj(vector<LPGAMEOBJECT>* coObjects);
	int GetIDSubWeapon() { return id; }
	int SetIDSubWeapon(int _id) { id = _id; }
	SubWeapon();
	SubWeapon(int state);
	~SubWeapon();
};

