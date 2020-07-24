#include "Boss.h"

void Boss::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, LPGAMEOBJECT simon)
{
	if (hp <= 0 && state != DEAD)
	{

		state = DEAD;
		vx = 0;
		vy = 0;
		animation_set->at(state)->StartRenderAnimation();
	}

	if (state == DEAD && animation_set->at(state)->IsRenderOver(400))
	{
		isDead = true;
		renderFireDone = true;
	}

	if (hp <= 0)
		return;
}

void Boss::Render()
{
	animation_set->at(state)->Render(nx, x, y);
}

void Boss::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	right = x + BOSS_BBOX_WIDTH;
	top = y;
	bottom = y + BOSS_BBOX_HEIGHT;
}

void Boss::ChasingSimon(double x, double y)
{

}
