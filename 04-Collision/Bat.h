#pragma once
#include "GameObject.h"

#define BAT_SLEEP	0
#define BAT_FLY		1
#define SPEED_BAT	0.18f	
#define GRAVITY		-0.002f

class Bat : public CGameObject
{
	bool isWakeUp;
	double r;
public:
	Bat();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	bool GetIsWakeUp() { return isWakeUp; }
	void SetISWakeUp(bool iswakeup) { isWakeUp = iswakeup; }
	int GetHP() { return hp; }
	void SetHP(int HP) { hp = HP; }
	
	~Bat();
};

