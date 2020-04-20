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
	if (CheckPosKnife(posX))
	{
		isSubWeaponExist = false;
		
		return;
	}
	CGameObject::Update(dt);
	x += dx;

	//DebugOut(L"x: %d\n", POSX);
}

void Knife::Render()
{
	if (isSubWeaponExist && !CheckPosKnife(posX))
		this->animation_set->at(KNIFE_ANI)->Render(nx, x, y);
}

void Knife::SetDirectionSubWeapon(int nx)
{
	if (nx > 0)
		vx = VX_KNIFE;
	else
		vx = -VX_KNIFE;
}

bool Knife::CheckPosKnife(float a)
{
	if (vx > 0)
	{
		if (x - a >= ((SCREEN_WIDTH/2)+ 70))
			return true;
	}
	else if (vx < 0)
	{
		if (a - x >= ((SCREEN_WIDTH/2) + 70))
			return true;
	}
	
	return false;
}

void Knife::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (!isDone)
	{
		left = x;
		top = y;
		right = left + 34;
		bottom = top + 18;
	}
}
