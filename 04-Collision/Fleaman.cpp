#include "Fleaman.h"
#include "Simon.h"
#include "Utils.h"
#include "Brick.h"
void Fleaman::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	right = x + FLEAMAN_BBOX_WIDTH;
	top = y;
	bottom = y + FLEAMAN_BBOX_HEIGHT;
}

void Fleaman::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, LPGAMEOBJECT simon)
{
	if (hp <= 0 && state != DEAD)
	{
		SetState(DEAD);
		vx = 0;
		vy = 0;
	}
	
	if (state == DEAD && animation_set->at(ani)->IsRenderOver(400))
	{
		isDead = true;
		renderFireDone = true;
	}

	if (hp <= 0)
		return;

	vy += GRAVITY * dt;
	
	if (abs(x - simon->x) < AREA_ACTIVE)
		active = true;
	if (!active)
		return;

	Enemy::Update(dt);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{

		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;
		
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<Brick*>(e->obj)) // if e->obj is Goomba 
			{
				if (e->ny != 0)
				{
					/*isGrounded = true;*/
					if (e->ny == -1)
					{
						isGrounded = true;
						vy = 0;
					}
					else
						y += dy;
				}
			}
		}
	}
		
		
	if (simon->x - x < 150 || firstJump)
	{
		if (!firstJump)
		{
			vx = FLEAMAN_SPEED;
			SetState(JUMP_HIGH);
			firstJump = true;
		}
		else
			ChasingSimon(simon->x, simon->y);
			
	}
	
	// clean up collision events
	for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];
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
	case JUMP_HIGH:
		vy = FLEAMAN_SPPED_Y_HIGH;
		isGrounded = false;
		break;
	case JUMP_LOW:
		vy = FLEAMAN_SPEED_Y_LOW;
		isGrounded = false;
		break;
	case DEAD:
		ani = ANI_DEAD;
		vx = 0;
		vy = 0;
		animation_set->at(ani)->StartRenderAnimation();
		break;
	default:
		break;
	}
}

void Fleaman::ChasingSimon(double xs, double ys)
{
	if (x < xs && abs(xs - x) > AREA_TURNING)
	{
		vx = FLEAMAN_SPEED;
		nx = 1;
		
	}
	else if (x > xs && (abs(xs - x) > AREA_TURNING))
	{
		vx = -FLEAMAN_SPEED;
		nx = -1;
	}

	if ((rand() % JUMP_RATE_MAX < JUMP_RATE))
	{
		if (!isGrounded)
			return;
		if (rand() % 4 == 3)
			SetState(JUMP_HIGH);
		else
			SetState(JUMP_LOW);
		
	}
}

Fleaman::Fleaman()
{
	firstJump = false;
	isGrounded = true;
	hp = FLEAMAN_HP;
	dame = FLEAMAN_DAME;
}


Fleaman::~Fleaman()
{
}
