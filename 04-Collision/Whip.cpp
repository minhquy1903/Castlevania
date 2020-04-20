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
	//RenderBoundingBox();
	
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
	top = y + 15;
	bottom = top + 15;
	if (nx < 0)
	{
		left = x + 50;
	}
	else if (nx > 0)
	{
		left = x + 135;
	}

	right = left + 55;
}


Whip::Whip()
{
	SetAnimationSet(CAnimationSets::GetInstance()->Get(2));
}


Whip::~Whip()
{
}
