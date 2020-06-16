#include "Whip.h"
#include "Torch.h"
#include "Utils.h"
#include "Candle.h"
#include "Bat.h"
#include "Knight.h"
#include "Ghost.h"
#include "Fleaman.h"
#include "Skeleton.h"

void Whip::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == WHIP_LVL_1)
		dame = DAME_WHIP_LVL1;
	else if (state == WHIP_LVL_3 || state == state == WHIP_LVL_2)
		dame = DAME_WHIP_LVL23;
	
	if (GetTickCount() - timeResetHit >= TIME_RESET_HIT)
		isResetHit = true;
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

void Whip::CollideWithSecretObj(vector<LPGAMEOBJECT>* coObjects)
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

void Whip::CollideWithSecretEnemies(vector<LPENEMY>* coObjects)
{
	if (isResetHit == false)
		return;
	for (int i = 0; i < coObjects->size(); i++)
	{
		LPENEMY obj = coObjects->at(i);
		if (AABBCollision(obj))
		{
			if (dynamic_cast<Bat*>(obj))
			{
				Bat *bat = dynamic_cast<Bat*>(obj);
				bat->SetHP(bat->GetHP() - dame);
			}
			else if (dynamic_cast<Knight*>(obj))
			{
				Knight*knight = dynamic_cast<Knight*>(obj);
				knight->SetHP(knight->GetHP() - dame);
				knight->SetState(KNIGHT_IS_HIT);
				//DebugOut(L"hp: %d\n", knight->GetHP());
			}
			else if (dynamic_cast<Ghost*>(obj))
			{
				Ghost * ghost = dynamic_cast<Ghost*>(obj);
				ghost->SetHP(ghost->GetHP() - dame);
			}
			else if (dynamic_cast<Fleaman*>(obj))
			{
				Fleaman * fleaman = dynamic_cast<Fleaman*>(obj);
				fleaman->SetHP(fleaman->GetHP() - dame);
			}
			else if (dynamic_cast<Skeleton*>(obj))
			{
				Skeleton * skeleton = dynamic_cast<Skeleton*>(obj);
				skeleton->SetHP(skeleton->GetHP() - dame);
			}
			timeResetHit = GetTickCount();
			isResetHit = false;
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
	dame = DAME_WHIP_LVL1;
	isResetHit = true;
	SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_WHIP));
}


Whip::~Whip()
{
}
