#include "SubWeapon.h"
#include "Candle.h"


void SubWeapon::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	CGameObject::Update(dt);
	x += dx;
}

void SubWeapon::Render()
{
	
}

void SubWeapon::SetPosSubWeapon(D3DXVECTOR3 pos, bool isStanding)
{
	if (isStanding)
		pos.y += 10;
	else
		pos.y += 35;
	SetPosition(pos.x, pos.y);
	posX = pos.x;
}




void SubWeapon::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
}


void SubWeapon::SubWeaponCollideWithCandle(vector<LPGAMEOBJECT>* coObjects)
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
			isSubWeaponExist = false;
			candle->SetState(BREAK_CANDLE);
		}
	}
}

SubWeapon::SubWeapon()
{
	isHittingSubWeapon = false;
}

SubWeapon::SubWeapon(int state)
{
	
	//SetAnimationSet(CAnimationSets::GetInstance()->Get(5));
}


SubWeapon::~SubWeapon()
{
}
