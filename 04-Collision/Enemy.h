#pragma once
#include "GameObject.h"
#include "Item.h"

class Enemy;
typedef Enemy * LPENEMY;

class Enemy : public CGameObject
{

public:
	int score;
	int hp;
	int dame;
	Item*item;
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL, LPGAMEOBJECT simon = NULL);
	void Render() = 0;
	void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	void DropItem();
	Item* GetItem() { return item; }
	int GetHP() { return hp; }
	void SetHP(int HP) { hp = HP; }
	Enemy();
	~Enemy();
};



