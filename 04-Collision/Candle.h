#pragma once
#include "Item.h"
#include "GameObject.h"

#define CANDLE_BBOX_WIDTH	16
#define CANDLE_BBOX_HEIGHT	32

class Candle : public CGameObject
{
	Item * item;
	int idItem;
	bool isBreak;
public:
	Candle();
	Candle(int iditem);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void DropItem();
	void SetIsBreak(bool isBreak) { this->isBreak = isBreak; }
	bool GetIsBreak() { return isBreak; }
	Item* GetItem() { return item; }
	~Candle();
};

