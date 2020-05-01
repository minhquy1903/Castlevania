#include "StairBottom.h"
#include "Textures.h"
#include "Game.h"



void StairBottom::Render()
{
	RenderBoundingBox();
}

void StairBottom::RenderBoundingBox()
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

void StairBottom::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + 32;
	bottom = y + 32;
}

StairBottom::StairBottom(int direction, int x, int y)
{
	nx = direction;
	this->x = x;
	this->y = y;
}

StairBottom::StairBottom()
{
}


StairBottom::~StairBottom()
{
}
