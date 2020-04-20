#include "Knife.h"
#include "Utils.h"


Knife::Knife()
{
	SetAnimationSet(CAnimationSets::GetInstance()->Get(KNIFE_ANIMATION_SET));
	isSubWeaponExist = false;
	isHittingSubWeapon = false;
	vx = 0.5f;
}


Knife::~Knife()
{
}

void Knife::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	if (CheckPosKnife(POSX))
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
	if (isSubWeaponExist && !CheckPosKnife(POSX))
		this->animation_set->at(0)->Render(nx, x, y);
}




void Knife::SetPosSubWeapon(D3DXVECTOR3 pos, bool isstanding)
{
	SubWeapon::SetPosSubWeapon(D3DXVECTOR3(pos.x, pos.y, 0), isstanding);
	POSX = pos.x;
}

bool Knife::CheckPosKnife(float a)
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
	if (!isDone)
	{
		left = x;
		top = y;
		right = left + 34;
		bottom = top + 18;
	}
}
