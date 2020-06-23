#include "Skeleton.h"
#include "Utils.h"
#include "Brick.h"

void Skeleton::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, LPGAMEOBJECT simon)
{
	if (abs(simon->x - x) < AREA_ACTIVE)
		active = true;

	if (!active)
		return;
	if (hp <= 0 && isDead == false)
	{
		isDead = true;
		SetState(DEAD);
	}

	if (state == DEAD && animation_set->at(ani)->IsRenderOver(400))
	{
		renderFireDone = true;
	}

	if (isDead)
		return;

	if (bone->y > SIZE_BONE)
	{
		bone->x = x + SKELETON_BBOX_WIDTH / 2;
		bone->y = y;
		bone->vy = BONE_SPEED_Y;
		if (simon->x > x)
			bone->vx = BONE_SPEED_X;
		else
			bone->vx = -BONE_SPEED_X;
	}

	vy += GRAVITY * dt;

	CGameObject::Update(dt);
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

		/*if (nx != 0)
			vx = 0;*/
		if (ny != 0)
			vy = 0;
		isGrounded = true;
		if (nx != 0)
			this->vx *= -1;

	}

	if (active)
		ChasingSimon(simon->x, simon->y);

	if (coEvents.size() == 0)
	{
		SetState(JUMP);
	}
	else
		state = WALK;
	// clean up collision events
	for (int i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
}

void Skeleton::Render()
{
	animation_set->at(ani)->Render(nx, x, y);
	//bone->Render();
	//RenderBoundingBox();
}

void Skeleton::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	right = x + SKELETON_BBOX_WIDTH;
	top = y;
	bottom = y + SKELETON_BBOX_HEIGHT;
}

void Skeleton::ChasingSimon(double xs, double ys)
{
	if (state == JUMP)
		return;
	if (xs > x && abs(xs - x) > AREA_TURNING1)
	{
		nx = 1;
		vx = SKELETON_SPEED_X;
	}
	else if (xs > x && abs(xs - x) < AREA_TURNING2)
	{
		nx = 1;
		vx = -SKELETON_SPEED_X;
	}
	else if (xs < x && abs(xs - x) > AREA_TURNING3)
	{
		nx = -1;
		vx = -SKELETON_SPEED_X;
	}
	else if (xs < x && abs(xs - x) < AREA_TURNING4)
	{
		nx = -1;
		vx = SKELETON_SPEED_X;
	}
}

void Skeleton::SetState(int state)
{
	this->state = state;

	switch (state)
	{
	case JUMP:
		if (isGrounded)
		{
			vy = -0.53;
			isGrounded = false;
		}
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

Skeleton::Skeleton()
{
	ani = ANI_SKELETON;
	isDead = false;
	hp = SKELETON_HP;
	bone = new Bone();
	active = false;
	bone->x = x;
	bone->y = y;
	dame = DAME;
}


Skeleton::~Skeleton()
{
}
