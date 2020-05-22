#pragma once
#include "Item.h"
#include "GameObject.h"
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

