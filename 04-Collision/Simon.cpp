#include <algorithm>
#include "debug.h"

#include "Game.h"

#include "Ground.h"
#include "Simon.h"


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
	if (state != SIMON_SIT)
	{
		whip->SetPosition(x - 85, y);
	}
	else
	{
		whip->SetPosition(x - 85, y + 15);
	}
	whip->SetNx(nx);
	if (isHitting == true)
		return;
	isHitting = true;

	if (state == SIMON_JUMP) 
	{
		CSimon::SetState(SIMON_STAND_HIT);
		ani = SIMON_STAND_HIT;
		animations[state]->SetCurrentFrame();
		animations[state]->StartAni();
	}
	else if(state == SIMON_SIT)
	{
		CSimon::SetState(SIMON_SIT_HIT);
		ani = SIMON_SIT_HIT;
		animations[state]->SetCurrentFrame();
		animations[state]->StartAni();
	}
	else
	{
		CSimon::SetState(SIMON_STAND_HIT);
		ani = SIMON_STAND_HIT;
		vx = 0;
		animations[state]->SetCurrentFrame();
		animations[state]->StartAni();
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
	//whip
	
	//
	coEvents.clear();

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
	animations[ani]->Render(nx, x, y);
	if (CSimon::GetState() == SIMON_STAND_HIT || CSimon::GetState() == SIMON_SIT_HIT)
		whip->Render(CSimon::animations[CSimon::GetState()]->GetCurrentFrame());
	RenderBoundingBox();
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

