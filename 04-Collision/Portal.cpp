#include "Portal.h"


CPortal::CPortal(float x, float y, float width, float height, int scene_id, int xNextPortal, int yNextPortal)
{
	this->scene_id = scene_id;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->xNextPortal = xNextPortal;
	this->yNextPortal = yNextPortal;
}

void CPortal::Render()
{
	//RenderBoundingBox();
}

void CPortal::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}