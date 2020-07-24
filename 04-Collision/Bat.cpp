#include "Bat.h"



void Bat::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	right = x + BAT_BBOX_WIDTH;
	top = y;
	bottom = y + BAT_BBOX_HEIGHT;
}

void Bat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, LPGAMEOBJECT simon)
{
	if (hp <= 0 && state != DEAD)
	{
		
		state = DEAD;
		vx = 0;
		vy = 0;
		animation_set->at(state)->StartRenderAnimation();
	}

	if (state == DEAD && animation_set->at(state)->IsRenderOver(400))
	{
		isDead = true;
		renderFireDone = true;
	}

	if (hp <= 0)
		return;
	if (abs(x - simon->x) < 210 && abs(y - simon->y) < 80)
		isWakeUp = true;

	if (isWakeUp)
	{
		Enemy::Update(dt);
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
	//RenderBoundingBox();
}


Bat::Bat()
{
	state = BAT_SLEEP;
	isWakeUp = false;
	hp = HEALTH;
	r = 0;
	dame = DAME;
	vx = SPEED_BAT;
	vy = SPEED_BAT;
}


Bat::~Bat()
{
}
