#pragma once
#include "Enemy.h"

#define BAT_SLEEP	0
#define BAT_FLY		1
#define DEAD		2
#define SPEED_BAT	0.18f	
#define GRAVITY		-0.002f

#define BAT_BBOX_WIDTH	32
#define BAT_BBOX_HEIGHT 32
#define RANGE			80
#define DAME			2
#define HEALTH			1
#define BAT_SPEED		0.6f

class Bat : public Enemy
{
	bool isWakeUp;
	double r;
public:
	Bat();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL, LPGAMEOBJECT simon = NULL);
	void Render();
	bool GetIsWakeUp() { return isWakeUp; }
	void SetISWakeUp(bool iswakeup) { isWakeUp = iswakeup; }
	
	~Bat();
};

