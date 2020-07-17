#include "Raven.h"

void Raven::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	right = x + RAVEN_BBOX;
	top = y;
	bottom = y + RAVEN_BBOX;
}

void Raven::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, LPGAMEOBJECT simon)
{
	CGameObject::Update(dt);

}

void Raven::Render()
{
	this->animation_set->at(1)->Render(nx, x, y);
}

void Raven::SetState(int state)
{
}

Raven::Raven()
{
	state = RAVEN_IDLE;
	hp = HEALTH;
	dame = DAME;
	vx = SPEED_RAVEN;
	vy = SPEED_RAVEN;
}

Raven::~Raven()
{

}
