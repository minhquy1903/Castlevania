#include "Whip.h"
#include "Candle.h"
#include "Utils.h"

void Whip::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

}

void Whip::Render()
{

}

void Whip::Render(int currentID)
{
	if (currentID >= 0)
	{
	animation_set->at(state)->RenderWhip(currentID, nx, x, y);
	CurrentFrame = currentID;
	}
	RenderBoundingBox();
	
}

void Whip::WhipCollideWithCandle(vector<LPGAMEOBJECT>* coObjects)
{
	for (int i = 0; i < coObjects->size(); i++)
	{
		LPGAMEOBJECT obj = coObjects->at(i);
		Candle * candle = dynamic_cast<Candle*>(obj);

		float left_a, top_a, right_a, bottom_a, left_b, top_b, right_b, bottom_b;
		GetBoundingBox(left_a, top_a, right_a, bottom_a);
		candle->GetBoundingBox(left_b, top_b, right_b, bottom_b);
		if (AABBCollision(left_a, top_a, right_a, bottom_a, left_b, top_b, right_b, bottom_b))
		{
			candle->SetState(BREAK_CANDLE);
		}	
	}
}



void Whip::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (nx == -1)
	{
		if (state == WHIP_LVL_3)
			left = x + 20;
		else
			left = x + 50;
		top = y + 15;
		right = x + 105;
		bottom = top + 15;
	}
	else
	{
		left = x + 135;
		top = y + 15;
		if (state == WHIP_LVL_3)
			right = x + 220;
		else
			right = x + 190;
		bottom = top + 15;
	}
}


Whip::Whip()
{
	SetAnimationSet(CAnimationSets::GetInstance()->Get(2));
}


Whip::~Whip()
{
}
