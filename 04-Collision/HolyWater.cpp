#include "HolyWater.h"

void HolyWater::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	if (y > 450 && isSubWeaponExist)
	{
		isSubWeaponExist = false;
		active = false;
		return;
	}
	CGameObject::Update(dt);
	x += dx;
	y += dy;
	vy += GRAVITY * dt;
}

void HolyWater::Render()
{
	animation_set->at(state)->Render(nx, x, y);
}

void HolyWater::SetDirectionSubWeapon(int nx)
{
	vx = VX_HOLYWATER * nx;
}

void HolyWater::TimeStart()
{
}

void HolyWater::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	right = x + HOLYWATER_BBOX;
	top = y;
	bottom = y + HOLYWATER_BBOX;
}
