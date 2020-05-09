#include "Candle.h"
#include "Whip.h"
#include "Utils.h"
#include "Knife.h"
void Candle::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + 32;
	bottom = top + 64;
}

void Candle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)	
{
	if (state == BREAK_CANDLE && animation_set->at(state)->IsRenderOver(400)) 
	{
		DropItem();
		renderFireDone = true;
	}
}

void Candle::Render()
{
	if (renderFireDone)
		return;
	//RenderBoundingBox();
	animation_set->at(state)->Render(0, x, y);
}

void Candle::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BREAK_CANDLE:
		animation_set->at(state)->StartRenderAnimation();
		break;
	}
}

void Candle::DropItem()
{
	item = new Item();
	item->SetPosition(x, y);
	item->SetState(idItem);
}

Candle::Candle()
{
	
}

Candle::Candle(int idItem)
{
	renderFireDone = false;
	state = NOMAL_CANDLE;
	this->idItem = idItem;
}


Candle::~Candle()
{
}
