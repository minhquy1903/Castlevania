#include "Bone.h"



void Bone::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, LPGAMEOBJECT simon)
{
	CGameObject::Update(dt);
	x += dx;
	y += dy;
	vy += GRAVITY * dt;
}

void Bone::Render()
{
	animation_set->at(0)->Render(nx, x, y);
}

void Bone::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	right = x + BONE_BBOX_WIDTH_HEIGHT;
	top = y;
	bottom = y + BONE_BBOX_WIDTH_HEIGHT;
}

Bone::Bone()
{
	SetAnimationSet(CAnimationSets::GetInstance()->Get(16));
	vx = BONE_SPEED_X;
	dame = DAME_BONE;
	x = -99;
	y = 0;
}


Bone::~Bone()
{
}
