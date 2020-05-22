#include "Boomerang.h"



void Boomerang::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	if (CheckExistBoomerang(posX))
	{
		isSubWeaponExist = false;

		return;
	}
	CGameObject::Update(dt);
	x += dx;
}

void Boomerang::Render()
{
	animation_set->at(ANIMATION_BOOMERANG)->Render(nx, x, y);
}

void Boomerang::SetDirectionSubWeapon(int nx)
{
	if (nx > 0)
		vx = VX_BOOMERANG;
	else
		vx = -VX_BOOMERANG;
}

bool Boomerang::CheckExistBoomerang(float a)
{
	return true;
}

void Boomerang::TimeStart()
{
}

void Boomerang::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
}

Boomerang::Boomerang()
{
}


Boomerang::~Boomerang()
{
}
