#include "Ghost.h"
#include "Simon.h"


void Ghost::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	right = x + 32;
	top = y;
	bottom = y + 32;
}

void Ghost::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, LPGAMEOBJECT simon)
{
	ChasingSimon(simon->x, simon->y);
	CGameObject::Update(dt);
	x += dx;
	y += dy;
	if (hp <= 0)
		isDead = true;
}


void Ghost::Render()
{
	animation_set->at(0)->Render(nx, x, y);
}

void Ghost::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	//case IDLE:

	default:
		break;
	}
}

void Ghost::ChasingSimon(int xS, int yS)
{
	if (x < xS)
	{
		if (abs(xS - x) > 40)
		{
			vx = GHOST_SPEED;
			nx = 1;
		}
	}
	else if (x > xS)
	{
		if ((abs(xS - x) > 40))
		{
			vx = -GHOST_SPEED;
			nx = -1;
		}
	}


	if (yS - 20 > y)
		vy = VY_GHOST
	else if (yS + 20 < y)
		vy = -VY_GHOST;
}

Ghost::Ghost()
{
	dame = 3;
	hp = 3;
}


Ghost::~Ghost()
{
}
