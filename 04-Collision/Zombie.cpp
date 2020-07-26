#include "Zombie.h"
#include "Utils.h"



void Zombie::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	right = x + 32;
	top = y;
	bottom = y + 64;
}

void Zombie::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, LPGAMEOBJECT simon)
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
	vy += GRAVITY * dt;

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

		if (ny != 0)
			vy = 0;
	}

	// clean up collision events
	for (int i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
}

void Zombie::Render()
{
	animation_set->at(state)->Render(nx, x, y);
}

void Zombie::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ZOMBIE_WALK:

		break;
	default:
		break;
	}
}

Zombie::Zombie(int nx)
{
	active = true;
	vy = VY_ZOMBIE;
	hp = HEALTH;
	dame = DAME;
	state = 0;
	this->nx = nx;
	vx = VX_ZOMBIE * this->nx;
}

Zombie::Zombie()
{
	
}


Zombie::~Zombie()
{
}
