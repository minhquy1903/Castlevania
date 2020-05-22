#include "Bat.h"



void Bat::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (state == BAT_SLEEP)
	{
		left = x - 210;
		right = x + 210;
		top = y;
		bottom = y + 120;
	}
	else
	{
		left = x;
		right = x + 32;
		top = y;
		bottom = y + 32;
	}
}

void Bat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isWakeUp)
	{
		CGameObject::Update(dt);
		state = BAT_FLY;
		x += dx;
		r += dy;
		if (r < 85)
			y += dy;

	}
}

void Bat::Render()
{
	animation_set->at(state)->Render(nx, x, y);
	//RenderBoundingBox();
}


Bat::Bat()
{
	state = BAT_SLEEP;
	isWakeUp = false;
	hp = 1;
	vy = -0.6;
	r = 0;
	vx = SPEED_BAT;
	vy = SPEED_BAT;
}


Bat::~Bat()
{
}
