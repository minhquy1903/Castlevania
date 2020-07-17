#include "Stair.h"
#include "Textures.h"
#include "Game.h"



void Stair::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (typeStair == 1)
	{
		left = x;
		top = y;
		right = x + WIDTH_BBOX_STAIR;
		bottom = y + 3;//3
	}
	else
	{
		left = x;
		top = y - 2;//2
		right = x + WIDTH_BBOX_STAIR;
		bottom = y;
	}
	
}

Stair::Stair(int x, int y, int directionX, int typeStair, int pair)
{
	nx = directionX;
	this->typeStair = typeStair;
	this->x = x;
	this->y = y;
	this->pair = pair;
	midStairX = (x * 2 + WIDTH_BBOX_STAIR) / 2;
}



void Stair::Render()
{
	RenderBoundingBox();
}



Stair::Stair()
{
}


Stair::~Stair()
{
}
