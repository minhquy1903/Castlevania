#include "HolyWater.h"
#include "Brick.h"

void HolyWater::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (animation_set->at(STATE_FIRE)->GetCurrentFrame() == 5 && state == STATE_FIRE)
	{
		isSubWeaponExist = false;
		active = false;
		state = STATE_NORMAL;
		return;
	}

	CGameObject::Update(dt);
	if(state == STATE_NORMAL)
		vy += GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	// turn off collision when die 

	CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	
	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
			x += dx;
			y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;

		/*if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;*/

		// Collision logic with Goombas
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<Brick*>(e->obj)) // if e->obj is Goomba 
			{
				if (e->ny != 0 || e->nx != 0)
				{
					vy = 0;
					vx = 0;
					state = STATE_FIRE;
					animation_set->at(STATE_FIRE)->SetCurrentFrame();
				}
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

}

void HolyWater::Render()
{
	if (isSubWeaponExist)
		animation_set->at(state)->Render(nx, x, y);
}

void HolyWater::SetDirectionSubWeapon(int nx)
{
	vx = VX_HOLYWATER * nx;
}



void HolyWater::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	right = x + HOLYWATER_BBOX;
	top = y;
	bottom = y + HOLYWATER_BBOX;
}

HolyWater::HolyWater()
{
	SetAnimationSet(CAnimationSets::GetInstance()->Get(HOLYWATER_ANIMATION_SETS));
	isSubWeaponExist = false;
	isHittingSubWeapon = false;
	vx = VX_HOLYWATER;
	state = STATE_NORMAL;
}
