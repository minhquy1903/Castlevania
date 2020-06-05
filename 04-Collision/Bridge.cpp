#include "Bridge.h"
#include "Brick.h"


void Bridge::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	right = x + BRIDGE_BBOX_WIDTH;
	top = y;
	bottom = y + BRIDGE_BBOX_HEIGHT;
}

void Bridge::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);


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
		x += min_tx * dx + nx * 0.1f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.1f;

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<Brick*>(e->obj))
			{
				if (nx != 0)
				{
					this->nx *= -1;
					vx *= -1;
				}
			}
			
		}
	}
}

void Bridge::Render()
{
	animation_set->at(0)->Render(0, x, y);
	//RenderBoundingBox();
}

Bridge::Bridge()
{
	vx = BRIDGE_SPEED;
	vy = 0;
}


Bridge::~Bridge()
{
}
