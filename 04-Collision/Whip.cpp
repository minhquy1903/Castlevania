#include "Whip.h"
#include "Candle.h"
#include "Utils.h"

void Whip::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{

	for (UINT i = 0; i < colliable_objects->size(); i++)
	{
		LPGAMEOBJECT obj = colliable_objects->at(i);

		if (dynamic_cast<Candle*>(obj))
		{
			Candle * e = dynamic_cast<Candle*>(obj);

			float left, top, right, bottom;
			e->GetBoundingBox(left, top, right, bottom);

			if (WhipColision(left, top, right, bottom))
			{
				/*if (e->GetState() != break_candle)
					listHit.push_back(CreateHit(e->GetPositionX(), e->GetPositionY() + 10));*/
				e->SetState(BREAK_CANDLE);
				DebugOut(L"Candle bi danh trung!!!\n");
			}

		}
	}
}

void Whip::Render()
{

}

void Whip::Render(int currentID)
{
	if (currentID >= 0)
		animation_set->at(0)->RenderWhip(currentID, nx, x, y);
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

bool Whip::WhipColision(float l_b, float t_b, float r_b, float b_b)
{
	float l_whip, t_whip, r_whip, b_whip;
	GetBoundingBox(l_whip, t_whip, r_whip, b_whip);

	return (CGameObject::AABBCheck(l_whip, t_whip, r_whip, b_whip, l_b, t_b, r_b, b_b));
		
}

Whip::Whip()
{
	SetAnimationSet(CAnimationSets::GetInstance()->Get(2));
}


Whip::~Whip()
{
}
