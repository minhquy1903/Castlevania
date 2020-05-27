#include "Zombie.h"



void Zombie::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	right = x + 32;
	top = y;
	bottom = 64;
}

void Zombie::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

}

void Zombie::Render()
{
	animation_set->at(state)->Render(nx, x, y);
}

void Zombie::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ZOMBIE_WALK:

		break;
	default:
		break;
	}
}

Zombie::Zombie()
{
}


Zombie::~Zombie()
{
}
