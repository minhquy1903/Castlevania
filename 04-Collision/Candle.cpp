#include "Candle.h"



Candle::Candle()
{
	
}

Candle::Candle(int iditem)
{
	this->idItem = iditem;
	isBreak = false;
}

void Candle::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	right = x + CANDLE_BBOX_WIDTH;
	top = y;
	bottom = y + CANDLE_BBOX_HEIGHT;
}

void Candle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isBreak)
		DropItem();
}

void Candle::Render()
{
	if (isBreak)
		return;
	animation_set->at(state)->Render(0, x, y);
}

void Candle::DropItem()
{
	item = new Item();
	item->SetPosition(x, y);
	item->SetState(idItem);
}


Candle::~Candle()
{
}
