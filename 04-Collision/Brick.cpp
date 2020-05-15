#include "Brick.h"

Brick::Brick()
{
	
}

void Brick::Render()
{
	animation_set->at(0)->Render(0, x, y);
	//RenderBoundingBox();
}

void Brick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}