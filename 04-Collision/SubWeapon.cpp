#include "SubWeapon.h"
#include "Torch.h"
#include "Candle.h"


void SubWeapon::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	CGameObject::Update(dt);
	x += dx;
}

void SubWeapon::SubWeaponCollideWithSimon(LPGAMEOBJECT simon)
{
}

void SubWeapon::Render()
{
	
}

void SubWeapon::SetPosSubWeapon(D3DXVECTOR3 pos, bool isStanding, int nx)
{
	if (isStanding)
		pos.y += 5;
	else
		pos.y += 35;
	if (nx == 1)
		pos.x += 60;
	else
		pos.x -= 20;
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
				active = false;
				torch->SetState(BREAK_TORCH);
			}
			else if (dynamic_cast<Candle*>(obj))
			{
				isSubWeaponExist = false;
				active = false;
				
				Candle *candle = dynamic_cast<Candle*>(obj);
				candle->isDead = true;
				candle->SetIsBreak(true);
			}
		}
	}
}

void SubWeapon::SubWeaponCollideWithEnemy(vector<LPENEMY>* coObjects)
{
	for (int i = 0; i < coObjects->size(); i++)
	{
		LPENEMY obj = coObjects->at(i);

		if (AABBCollision(obj))
		{
			obj->hp -= DAME_SUBWEAPON;
		}
	}
}

SubWeapon::SubWeapon()
{
	isHittingSubWeapon = false;
	isSubWeaponExist = false;
	active = false;
}

SubWeapon::SubWeapon(int state)
{
	
	//SetAnimationSet(CAnimationSets::GetInstance()->Get(5));
}


SubWeapon::~SubWeapon()
{
}
