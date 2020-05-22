#include "Item.h"
#include "Utils.h"


void Item::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (!isTimeOut)
	{
		switch (state)
		{
		case ITEM_UPGRADE_WHIP:
			left = x;
			top = y;
			right = left + 32;
			bottom = top + 32;
			break;
		case ITEM_HEART:
			left = x;
			top = y;
			right = left + 24;
			bottom = top + 20;
			break;
		case ITEM_KNIFE:
			left = x;
			top = y;
			right = left + 32;
			bottom = top + 18;
			break;
		case ITEM_BOOMERANG:
			left = x;
			top = y;
			right = left + 30;
			bottom = top + 28;
		}
	}
}

void Item::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	if (GetTickCount() - lifeTimeStart > timeFlicker)
		isFlicker = true;
	if (GetTickCount() - lifeTimeStart > lifeTime)
	{
		isTimeOut = true;
		return;
	}
	
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

		y += min_ty * dy + ny * 0.1f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
	}


	// clean up collision events
	for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Item::Render()
{
	if (this->isTimeOut)
		return;
	int alpha = 255;
	if (isFlicker)
		alpha = rand() % 255 + 100;
	//RenderBoundingBox();
	animation_set->at(state)->Render(0, x, y, alpha);
}


Item::Item()
{
	SetAnimationSet(CAnimationSets::GetInstance()->Get(4));
	lifeTimeStart = GetTickCount();
	isTimeOut = false;
	timeFlicker = TIME_FLICKER;
	lifeTime = LIFE_TIME;
	isFlicker = false;
	vy = 0.15;
}


Item::~Item()
{
}
