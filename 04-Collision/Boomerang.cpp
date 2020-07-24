#include "Boomerang.h"



void Boomerang::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	if (CheckPosBoomerang(posX))
	{
		isSubWeaponExist = false;
		active = false;
		return;
	}
	CGameObject::Update(dt);
	x += dx;
	if (nx > 0)
		vx -= GRAVITY_PULL
	else 
		vx += GRAVITY_PULL
}

void Boomerang::Render()
{
	if (isSubWeaponExist)
		this->animation_set->at(0)->Render(nx, x, y);
}

void Boomerang::SetDirectionSubWeapon(int nx)
{
	if (nx > 0)
		vx = BOOMERANG_SPEED;
	else
		vx = -BOOMERANG_SPEED;
}

bool Boomerang::CheckPosBoomerang(float a)
{
	if (vx > 0)
	{
		if (x - a >= ((SCREEN_WIDTH / 2) + 140))
			return true;
	}
	else if (vx < 0)
	{
		if (a - x >= ((SCREEN_WIDTH / 2) + 140))
			return true;
	}
	return false;
}

void Boomerang::SubWeaponCollideWithSimon(LPGAMEOBJECT simon)
{
	if (AABBCollision(simon))
	{
		active = false;
		isSubWeaponExist = false;
	}
}



void Boomerang::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + BBOX_32;
	bottom = top + BBOX_32;
}

Boomerang::Boomerang()
{
	SetAnimationSet(CAnimationSets::GetInstance()->Get(BOOMERANG_ANIMATION_SETS));
	isSubWeaponExist = false;
	isHittingSubWeapon = false;
	vx = BOOMERANG_SPEED;
}


Boomerang::~Boomerang()
{
}
