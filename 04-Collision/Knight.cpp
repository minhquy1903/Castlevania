#include "Knight.h"
#include "Utils.h"


void Knight::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	right = x + 40;
	top = y;
	bottom = y + 80;
}

void Knight::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	if (nx == 1)
		vx = 0.1;
	else
		vx = -0.1;
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
	animation_set->at(0)->Render(nx, x, y);
}

void Knight::SetState(int state)
{
	
}

Knight::Knight()
{
	vx = 0.7f;
	nx = 1;
	vy = 0.1f;
	isTurning = false;
}


Knight::~Knight()
{
}
