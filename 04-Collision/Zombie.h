#pragma once
#include "GameObject.h"

#define ZOMBIE_WALK 0


class Zombie :
	public CGameObject
{
	int hp;
public:
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void SetState(int state);
	int GetHP() { return hp; }
	void SetHP(int HP) { hp = HP; }
	Zombie();
	~Zombie();
};

