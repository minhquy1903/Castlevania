#include "Whip.h"
#include "Torch.h"
#include "Utils.h"
#include "Candle.h"

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

void Whip::WhipCollideWithSecretObj(vector<LPGAMEOBJECT>* coObjects)
{
	for (int i = 0; i < coObjects->size(); i++)
	{
		LPGAMEOBJECT obj = coObjects->at(i);
		if (AABBCollision(obj))
		{
			if (dynamic_cast<Torch*>(obj))
			{
				Torch *torch = dynamic_cast<Torch*>(obj);
				torch->SetState(BREAK_TORCH);
			}
			else if (dynamic_cast<Candle*>(obj))
			{
				Candle *candle = dynamic_cast<Candle*>(obj);
				candle->SetIsBreak(true);
			}
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
