#include "StairTop.h"
#include "Textures.h"
#include "Game.h"


void StairTop::Render()
{

}

void StairTop::RenderBoundingBox()
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

void StairTop::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{

}

StairTop::StairTop(int direction, int x, int y)
{
	nx = direction;
	this->x = x;
	this->y = y;
}

StairTop::StairTop()
{
}


StairTop::~StairTop()
{
}
