#pragma once
#include "GameObject.h"
#include "Item.h"
#define NOMAL_TORCH 0
#define BREAK_TORCH 1

class Torch : public CGameObject
{
	Item * item;
	int idItem;
public:
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt ,vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void SetState(int state);
	void DropItem();
	bool GetRenderFire() { return renderFireDone; }
	Item* GetItem() { return item; }
	Torch();
	Torch(int idItem);
	~Torch();
};

