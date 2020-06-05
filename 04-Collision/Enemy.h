#pragma once
#include "GameObject.h"

class Enemy;
typedef Enemy * LPENEMY;

class Enemy : public CGameObject
{
public:
	int score;
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL, LPGAMEOBJECT simon = NULL);
	void Render() = 0;
	void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	Enemy();
	~Enemy();
};



