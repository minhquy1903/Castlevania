#include "Axe.h"

void Axe::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	if (y > 450 && isSubWeaponExist)
	{
		isSubWeaponExist = false;
		return;
	}
	CGameObject::Update(dt);
	x += dx;
	y += dy;
	vy += GRAVITY * dt;
}

void Axe::Render()
{
	if(isSubWeaponExist)
		animation_set->at(0)->Render(nx, x, y);
}

void Axe::SetDirectionSubWeapon(int nx)
{
	vx = VX_AXE * nx;
}
void Axe::TimeStart()
{
}
void Axe::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + AXE_BBOX_WIDTH_WIDTH;
	bottom = y + AXE_BBOX_WIDTH_WIDTH;
}
Axe::Axe()
{
	SetAnimationSet(CAnimationSets::GetInstance()->Get(AXE_ANIMATION_SET));
	
}


Axe::~Axe()
{
}
