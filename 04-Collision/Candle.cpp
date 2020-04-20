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
	if (state == BREAK_CANDLE && animation_set->at(state)->RenderOver(400)) 
	{
		DropItem();
		isDone = true;
	}
}

void Candle::Render()
{
	if (isDone)
		return;
		
	animation_set->at(state)->Render(0, x, y);
}

void Candle::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BREAK_CANDLE:
		animation_set->at(state)->StartAni();
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
	isDone = false;
	state = NOMAL_CANDLE;
}


Candle::~Candle()
{
}
