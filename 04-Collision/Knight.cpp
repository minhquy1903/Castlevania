#include "Knight.h"
#include "Utils.h"
#include "Brick.h"

void Knight::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	right = x + KNIGHT_BBOX_WIDTH;
	top = y;
	bottom = y + KNIGHT_BBOX_HEIGHT;
}

void Knight::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, LPGAMEOBJECT simon)
{
	if (hp <= 0 && state != DEAD)
	{
		
		SetState(DEAD);
	}

	if (ani == DEAD && animation_set->at(DEAD)->IsRenderOver(400))
	{
		isDead = true;
		renderFireDone = true;
	}

	if (state == DEAD)
		return;

	if (GetTickCount() - timeDelay >= DELAY_TIME)
		SetState(WALK);
	
	
	Enemy::Update(dt);
	vy += GRAVITY * dt;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	
	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);
	
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
		//nx = -nx;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);


		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (ny == -1.0f)
		{
			vy = 0;
		}

		if (nx == 1 || nx == -1)
		{

			this->nx *= -1;
			this->vx *= -1;
		}
	}

	if (coEvents.size() == 1)
	{
		if (isTurning == false)
		{
			nx = -nx;
			vx *= nx;
			isTurning = true;
		}
	}
	DebugOut(L"SIZE: %d\n", coEvents.size());
	if (coEvents.size() > 1)
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
		animation_set->at(ani)->SetCurrentFrame();
		timeDelay = GetTickCount();
		break;
	case WALK:
		ani = WALK;
		vx = KNIGHT_WALK_SPEED * nx;
		break;
	case DEAD:
		ani = DEAD;
		vx = 0;
		vy = 0;
		animation_set->at(ani)->StartRenderAnimation();
		break;
	default:
		break;
	}
}

Knight::Knight()
{
	vx = KNIGHT_WALK_SPEED;
	vy = VY;
	hp = HEALTH;
	dame = DAME;
	isTurning = false;
}


Knight::~Knight()
{
}
