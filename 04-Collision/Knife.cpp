#include "Knife.h"
#include "Utils.h"


Knife::Knife()
{
	SetAnimationSet(CAnimationSets::GetInstance()->Get(KNIFE_ANIMATION_SET));
	isSubWeaponExist = false;
	isHittingSubWeapon = false;
	vx = VX_KNIFE;
}


Knife::~Knife()
{
}

void Knife::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	if (CheckExistKnife(posX))
	{
		isSubWeaponExist = false;
		
		return;
	}
	CGameObject::Update(dt);
	x += dx;
}

void Knife::Render()
{
	if (isSubWeaponExist && !CheckExistKnife(posX))
		this->animation_set->at(KNIFE_ANI)->Render(nx, x, y);
}

void Knife::SetDirectionSubWeapon(int nx)
{
	if (nx > 0)
		vx = VX_KNIFE;
	else
		vx = -VX_KNIFE;
}

bool Knife::CheckExistKnife(float a)
{
	if (vx > 0)
	{
		if (x - a >= ((SCREEN_WIDTH/2)+ 100))
			return true;
	}
	else if (vx < 0)
	{
		if (a - x >= ((SCREEN_WIDTH/2) + 100))
			return true;
	}
	
	return false;
}

void Knife::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
		left = x;
		top = y;
		right = left + 34;
		bottom = top + 18;
}
