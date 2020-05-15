#include "Stair.h"
#include "Textures.h"
#include "Game.h"



void Stair::Render()
{
	RenderBoundingBox();
}

void Stair::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPDIRECT3DTEXTURE9 bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	CGame::GetInstance()->Draw(nx, l, t, bbox, rect.left, rect.top, rect.right, rect.bottom, 120);
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
}


Stair::Stair()
{
}


Stair::~Stair()
{
}
