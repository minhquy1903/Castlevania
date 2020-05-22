#include "SubWeapon.h"
#include "Torch.h"
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


void SubWeapon::SubWeaponCollideWithSecretObj(vector<LPGAMEOBJECT>* coObjects)
{
	for (int i = 0; i < coObjects->size(); i++)
	{
		LPGAMEOBJECT obj = coObjects->at(i);

		if (AABBCollision(obj))
		{
			if (dynamic_cast<Torch*>(obj))
			{
				Torch * torch = dynamic_cast<Torch*>(obj);
				isSubWeaponExist = false;
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
