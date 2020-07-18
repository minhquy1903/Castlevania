#include "Raven.h"

void Raven::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	right = x + RAVEN_BBOX;
	top = y;
	bottom = y + RAVEN_BBOX;
}

void Raven::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, LPGAMEOBJECT simon)
{
	if (hp <= 0 && state != RAVEN_DEAD)
	{
		state = RAVEN_DEAD;
		vx = 0;
		vy = 0;
		animation_set->at(state)->StartRenderAnimation();
	}

	if (state == RAVEN_DEAD && animation_set->at(state)->IsRenderOver(400))
	{
		isDead = true;
		renderFireDone = true;
	}

	if (hp <= 0)
		return;

	if (abs(simon->x - x) < RANGE_ACTIVE)
		state = RAVEN_FLY;
	if (state == RAVEN_IDLE)
		return;
	CGameObject::Update(dt);
	x += dx;
	y += dy;

	ChasingSimon(simon->x, simon->y);
}

void Raven::Render()
{
	this->animation_set->at(state)->Render(nx, x, y);
}

void Raven::SetState(int state)
{
	
}

void Raven::ChasingSimon(int xS, int yS)
{
	if (y < yS)
	{
		if (x > xS)
		{
			nx = -1;
			vx = -SPEED_RAVEN;
			if (abs(x - xS) < RANGE_STOP)
			{
				vx = 0;
				vy = 0;
				stop++;
				if (stop < TIME_STOP1)
					return;
				vx = -SPEED_RAVEN;
				vy = SPEED_RAVEN;
			}
			if (abs(x - xS) < RANGE_STOP / 2)
			{
				vx = 0;
				vy = 0;
				stop++;
				if (stop < TIME_STOP2)
					return;
				vx = -SPEED_RAVEN;
				vy = SPEED_RAVEN;
			}
		}
		else
		{
			nx = 1;
			vx = SPEED_RAVEN;
			if (abs(x - xS) < RANGE_STOP)
			{
				vx = 0;
				vy = 0;
				stop++;
				if (stop < TIME_STOP1)
					return;
				vx = SPEED_RAVEN;
				vy = SPEED_RAVEN;
			}
			if (abs(x - xS) < RANGE_STOP / 2)
			{
				vx = 0;
				vy = 0;
				stop++;
				if (stop < TIME_STOP2)
					return;
				vx = SPEED_RAVEN;
				vy = SPEED_RAVEN;
			}
		}
	}
	else
	{
		vx = 0;
		vy = -SPEED_RAVEN;
	}
	
	
		
}

Raven::Raven()
{
	state = RAVEN_IDLE;
	hp = HEALTH;
	dame = DAME;
	vx = SPEED_RAVEN;
	vy = SPEED_RAVEN;
	nx = -1;
	stop = 0;
}

Raven::~Raven()
{

}
