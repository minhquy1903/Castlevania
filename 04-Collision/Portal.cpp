#include "Portal.h"


CPortal::CPortal(float x, float y, float r, float b, int scene_id)
{
	this->scene_id = scene_id;
	this->x = x;
	this->y = y;
	width = r - x + 1;
	height = b - y + 1;
}

void CPortal::Render()
{
	RenderBoundingBox();
}

void CPortal::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}