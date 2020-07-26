#include "Boss.h"
#include "Game.h"

void Boss::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, LPGAMEOBJECT simon)
{
	if (hp <= 0 && state != DEAD)
	{

		state = DEAD;
		vx = 0;
		vy = 0;
		animation_set->at(state)->StartRenderAnimation();
	}
 
	if (state == DEAD && animation_set->at(state)->IsRenderOver(BOSS_TIME))
	{
		isDead = true;
		renderFireDone = true;
	}

	if (hp <= 0)
		return;

	Enemy::Update(dt);

	if (simon->x - x >= RANGE_BOSS_ACTIVE && !active)
	{
		state = BOSS_WAKEUP;
		active = true;
	}

	if (active && state != DEAD)
	{

		if (x > simon->x)
			nx = -1;
		else nx = 1;

		if (y > simon->y)
			ny = -1;
		if (y <= simon->y)
			ny = 1;

		if (rand() % RAND_MIN == 1 && (x > CGame::GetInstance()->GetCamPosX() - SCREEN_BOX_LEFT) && (x < CGame::GetInstance()->GetCamPosX() + SCREEN_BOX_RIGHT) && !target)
		{
			if (!fly)
			{
				vx = (float)(nx * abs(simon->x - x)) / MAX_DISTANCE;
				vy = (float)(ny * abs(simon->y - y)) / MAX_DISTANCE;
			}
			//checkstop = false;
		}

		if (/*rand() % 4 < 3 && */abs(simon->x - x) <= 1.0f)
		{
			time = GetTickCount();
			vy = -VY_DOWN;
			if (rand() % 2 == 1)
				vx = VX_CLOSE;
			else
				vx = -VX_CLOSE;
			fly = true;
			checkstop = true;
		}
		if (GetTickCount() - time > TIME_ATTACK_STOP && checkstop)
		{
			vx = vy = 0;
			fly = false;
			target = false;
			checkstop = false;
		}

		if (x <= CGame::GetInstance()->GetCamPosX() - SCREEN_BOX_LEFT)
		{
			//timer1->Start();
			target = true;
			vx = VX_CLOSE;
			vy = -VY_DOWN;
			if (abs(x - simon->x) > MAX_DISTANCE_RIGHT_LEFT)
			{
				target = false;
			}
		}
		else if (x > CGame::GetInstance()->GetCamPosX() + SCREEN_BOX_RIGHT)
		{

			target = true;
			vx = -VX_CLOSE;
			if (rand() % 2 == 1)
				vy = VY;
			else
				vy = -VY;
			if (abs(x - simon->x) > MAX_DISTANCE_RIGHT_LEFT)
			{
				target = false;
			}
		}
		else if (y < CGame::GetInstance()->GetCamPosY() + SCREEN_BOX_UP)
		{
			target = true;
			vy = VY;
			if (abs(y - simon->y) > MAX_DISTANCE_UP_DOWN)
			{

				target = false;
			}
		}
		else if (y > CGame::GetInstance()->GetCamPosY() + SCREEN_BOX_DOWN)
		{
			target = true;
			vy = -VY_DOWN;
			if (abs(y - simon->y) > MAX_DISTANCE_UP_DOWN)
			{

				target = false;
			}
		}
	}

	x += dx;
	y += dy;


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

void Boss::SetState(int state)
{
	
}

Boss::Boss()
{
	hp = HP_BOSS;
	dame = BOSS_DAME;
	state = BOSS_SLEEP;
}

void Boss::ChasingSimon(double x, double y)
{

}
