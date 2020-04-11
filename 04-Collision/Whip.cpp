#include "Whip.h"



void Whip::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	
}

void Whip::Render()
{
}

void Whip::Render(int currentID)
{
	if (currentID >= 0)
		animations[0]->RenderWhip(currentID, nx, x, y);
}

void Whip::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{

}

Whip::Whip()
{
	AddAnimation(200);
}


Whip::~Whip()
{
}
