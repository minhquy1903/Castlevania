#include <algorithm>
#include "Utils.h"

#include "Game.h"

#include "Ground.h"
#include "Simon.h"


CSimon::CSimon()
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(0));
	untouchable = 0;
	whip = new Whip();
}

void CSimon::WalkLeft()
{
	if (isGrounded)
	{
	nx = -1;
	ani = SIMON_WALKING;
	CSimon::SetState(SIMON_WALKING);
	}

}

void CSimon::WalkRight()
{
	if (isGrounded)
	{
	nx = 1;
	ani = SIMON_WALKING;
	CSimon::SetState(SIMON_WALKING);
	}
	
}

void CSimon::Jump()
{
	if (isGrounded && !(state == SIMON_SIT)) 
	{
		isGrounded = false;
		ani = SIMON_JUMP;
		CSimon::SetState(SIMON_JUMP);
	}
	
}

void CSimon::Hit()
{
	whip->SetNx(nx);
	if (isHitting == true)
		return;
	isHitting = true;

	if (state == SIMON_JUMP) 
	{
		CSimon::SetState(SIMON_STAND_HIT);
		ani = SIMON_STAND_HIT;
		animation_set->at(ani)->SetCurrentFrame();
		animation_set->at(ani)->StartAni();
	}
	else if(state == SIMON_SIT)
	{
		CSimon::SetState(SIMON_SIT_HIT);
		ani = SIMON_SIT_HIT;
		animation_set->at(ani)->SetCurrentFrame();
		animation_set->at(ani)->StartAni();
	}
	else
	{
		CSimon::SetState(SIMON_STAND_HIT);
		ani = SIMON_STAND_HIT;
		vx = 0;
		animation_set->at(ani)->SetCurrentFrame();
		animation_set->at(ani)->StartAni();
	}
}

void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{

	// Calculate dx, dy 
	CGameObject::Update(dt);

	// Simple fall down
	vy += GRAVITY*dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	//whip
	if (ani != SIMON_SIT_HIT)
	{
		whip->SetPosition(x - 90, y);
	}
	else
	{
		whip->SetPosition(x - 90, y + 15);
	}
	//
	// turn off collision when die 
	
		CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	if ( GetTickCount() - untouchable_start > SIMON_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	// No collision occured, proceed normally
	if (coEvents.size()==0)
	{
		x += dx; 
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx*dx + nx*0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty*dy + ny*0.4f;
		
		if (nx!=0) vx = 0;
		if (ny!=0) vy = 0;

		// Collision logic with Goombas
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CGround *>(e->obj)) // if e->obj is Goomba 
			{
				if (e->ny < 0)
				{
					isGrounded = true;
				}
			/*	else
					isGrounded = false;*/
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CSimon::Render()
{
	animation_set->at(ani)->Render(nx, x, y);
	if (ani == SIMON_STAND_HIT || ani == SIMON_SIT_HIT)
		whip->Render(animation_set->at(ani)->GetCurrentFrame());

	//RenderBoundingBox();
}

void CSimon::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case SIMON_WALKING:
		if (nx == 1)
			vx = SIMON_WALKING_SPEED;
		else
			vx = -SIMON_WALKING_SPEED;
		break;
	case SIMON_JUMP:
		isGrounded = false;
		vy = -SIMON_JUMP_SPEED_Y;
		break;
	case SIMON_SIT:
		vx = 0;
		ani = SIMON_SIT;
		break;
	case SIMON_IDLE:
		vx = 0;
		ani = SIMON_IDLE;
		break;
	/*case SIMON_SIT_HIT:*/

	}
}

void CSimon::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y; 
	right = x + SIMON_BOX_WIDTH;
	bottom = y + SIMON_BOX_HEIGHT;
}

