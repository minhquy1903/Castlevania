#include "Brick.h"

Brick::Brick()
{
}

Brick::Brick(int nw, int nh)
{
	nWidth = nw;
	nHeight = nh;
}

void Brick::Render()
{
	animation_set->at(0)->Render(0, x, y, 0);
	RenderBoundingBox();
}

void Brick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH * nWidth;
	b = y + BRICK_BBOX_HEIGHT * nHeight;
}