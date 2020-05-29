#include "Stair.h"
#include "Textures.h"
#include "Game.h"



void Stair::Render()
{
	//RenderBoundingBox();
}



void Stair::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y + 30;
	right = x + 48;
	bottom = y + 32;
}

Stair::Stair(int x, int y, int directionX, int directionY)
{
	nx = directionX;
	ny = directionY;
	this->x = x;
	this->y = y;
	midStairX = (x * 2 + 48) / 2;
}


Stair::Stair()
{
}


Stair::~Stair()
{
}
