#include "Bat.h"



void Bat::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (state == BAT_SLEEP)
	{
		left = x - 210;
		right = x + 210;
		top = y + 60;
		bottom = y + 120;
	}
	else
	{
		left = x;
		right = x + BAT_BBOX_WIDTH;
		top = y;
		bottom = y + BAT_BBOX_HEIGHT;
	}
}

void Bat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, LPGAMEOBJECT simon)
{
	if (hp <= 0)
		isDead = true;
	if (isWakeUp)
	{
		CGameObject::Update(dt);
		state = BAT_FLY;
		x += dx;
		r += dy;
		if (r < RANGE)
			y += dy;

	}
}

void Bat::Render()
{
	animation_set->at(state)->Render(nx, x, y);
	RenderBoundingBox();
}


Bat::Bat()
{
	state = BAT_SLEEP;
	isWakeUp = false;
	hp = HEALTH;
	vy = BAT_SPEED;
	r = 0;
	dame = DAME;
	vx = SPEED_BAT;
	vy = SPEED_BAT;
}


Bat::~Bat()
{
}
