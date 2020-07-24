#include "Item.h"
#include "Utils.h"


void Item::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (!isTimeOut)
	{
		switch (state)
		{
		case ITEM_UPGRADE_WHIP:
			left = x;
			top = y;
			right = left + BBOX_32;
			bottom = top + BBOX_32;
			break;
		case ITEM_HEART:
			left = x;
			top = y;
			right = left + HEART_BBOX;
			bottom = top + HEART_BBOX;
			break;
		case ITEM_KNIFE:
			left = x;
			top = y;
			right = left + KNIFE_BBOX_WIDTH;
			bottom = top + KNIFE_BBOX_HEIGHT;
			break;
		case ITEM_BOOMERANG:
			left = x;
			top = y;
			right = left + BBOX_32;
			bottom = top + BBOX_32;
			break;
		case ITEM_AXE:
			left = x;
			top = y;
			right = left + BBOX_32;
			bottom = top + BBOX_32;
			break;
		case ITEM_DOUBLE:
			left = x;
			top = y;
			right = left + BBOX_32;
			bottom = top + BBOX_32;
			break;
		case ITEM_TRIPLE:
			left = x;
			top = y;
			right = left + BBOX_32;
			bottom = top + BBOX_32;
			break;
		case ITEM_HOLYWATER:
			left = x;
			top = y;
			right = left + BBOX_32;
			bottom = top + BBOX_32;
			break;
		case ITEM_CLOCK:
			left = x;
			top = y;
			right = left + BBOX_32;
			bottom = top + BBOX_32;
			break;
		case ITEM_INVISIBILITY:
			left = x;
			top = y;
			right = left + BBOX_32;
			bottom = top + BBOX_32;
			break;
		case ITEM_SMALLHEART:
			left = x;
			top = y;
			right = left + HEART_BBOX / 2;
			bottom = top + HEART_BBOX / 2;
			break;
		}
	}
}

void Item::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	int timenow = GetTickCount();
	if (timenow - lifeTimeStart > TIME_FLICKER)
		isFlicker = true;
	if (timenow - lifeTimeStart > LIFE_TIME)
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

		y += min_ty * dy + ny * 0.4f;

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
	RenderBoundingBox();
	animation_set->at(state)->Render(0, x, y, alpha);
}


Item::Item()
{
	SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATIONSET_ITEM));
	lifeTimeStart = GetTickCount();
	isTimeOut = false;
	isFlicker = false;
	vy = VY_ITEM;
}


Item::~Item()
{
}
