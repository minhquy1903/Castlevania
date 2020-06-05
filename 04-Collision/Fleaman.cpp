#include "Fleaman.h"
#include "Simon.h"


void Fleaman::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	right = x + FLEAMAN_BBOX_WIDTH;
	top = y;
	bottom = y + FLEAMAN_BBOX_HEIGHT;
}

void Fleaman::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, LPGAMEOBJECT simon)
{
	
	if (simon->x - x > 400)
	{
		vy += GRAVITY * dt;
		ChasingSimon(simon->x, simon->y);
	}
}


void Fleaman::Render()
{
	animation_set->at(ani)->Render(nx, x, y);
}

void Fleaman::SetState(int state)
{
	this->state = state;
	switch (state)
	{
	case IDLE:
		break;
	case JUMP:
		break;
	case DEAD:
		break;
	default:
		break;
	}
}

void Fleaman::ChasingSimon(int sx, int sy)
{
	if (x < sx)
	{
		if (abs(sx - x) > 100)
		{
			vx = 0.16;
			nx = 1;
		}
	}
	else if (x > sx)
	{
		if ((abs(sx - x) > 100))
		{
			vx = -0.16;
			nx = -1;
		}
	}

	if (((rand() % 10000 < 350) && (abs(sx - x) < 120)) && y > 350/*330*/)
	{
		vy = -0.35;
		//jump = false;
	}
}

Fleaman::Fleaman()
{
}


Fleaman::~Fleaman()
{
}
