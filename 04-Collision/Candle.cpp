#include "Candle.h"



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
		Done = true;
}

void Candle::Render()
{
	if (Done)
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

Candle::Candle()
{
	Done = false;
	state = NOMAL_CANDLE;
}


Candle::~Candle()
{
}
