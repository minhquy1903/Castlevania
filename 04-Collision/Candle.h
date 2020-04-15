#pragma once
#include "GameObject.h"

#define NOMAL_CANDLE 0
#define BREAK_CANDLE 1

class Candle : public CGameObject
{
	bool Done;
public:
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void SetState(int state);
	Candle();
	~Candle();
};

