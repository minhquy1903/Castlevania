#pragma once
#include "GameObject.h"

#define GHOST_SPEED 0.085f
#define VY_GHOST	0.022f;

class Ghost : public CGameObject
{
	
public:
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void SetState(int state);
	void ChasingSimon(int x, int y);
	int GetHP() { return hp; }
	void SetHP(int HP) { hp = HP; }
	Ghost();
	~Ghost();
};

