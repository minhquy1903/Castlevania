#include "Knight.h"
#include "Utils.h"
#include "Brick.h"

void Knight::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	right = x + 32;
	top = y;
	bottom = y + 64;
}

void Knight::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (hp <= 0)
	{
		SetState(KNIGHT_DEAD);
		isDead = true;
	}
	if (GetTickCount() - timeDelay >= 260)
		SetState(KNIGHT_WALK);

	
	CGameObject::Update(dt);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	
	coEvents.clear();


	/*int turning = rand() % 100;
	if (turning == 1)
		nx = -nx;*/

	CalcPotentialCollisions(coObjects, coEvents);
	DebugOut(L"size: %d \n", coEvents.size());
	
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
		//nx = -nx;
	}
	else
	{
		
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		y += min_ty * dy + ny * 0.6f;
		x += min_tx * dx + nx * 0.4f;

		/*if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;*/
	}
	
	

	if (coEvents.size() == 1 || coEvents.size() > 3)
	{
		if (isTurning == false)
		{
			nx = -nx;
			isTurning = true;
		}
	}
	if (coEvents.size() > 1 && coEvents.size() < 4)
	{
		isTurning = false;
	}
	// clean up collision events
	for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Knight::Render()
{
	animation_set->at(ani)->Render(nx, x, y);
}

void Knight::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KNIGHT_IS_HIT:
		vx = 0;
		ani = KNIGHT_WALK;
		animation_set->at(ani)->SetCurrentFrame();
		timeDelay = GetTickCount();
		break;
	case KNIGHT_WALK:
		ani = KNIGHT_WALK;
		if (nx == 1)
			vx = 0.1;
		else
			vx = -0.1;
		break;
	case KNIGHT_DEAD:

		break;
	default:
		break;
	}
}

Knight::Knight()
{
	vx = 0.7f;
	nx = 1;
	vy = 0.1f;
	hp = 3;
	dame = 2;
	isTurning = false;
}


Knight::~Knight()
{
}
