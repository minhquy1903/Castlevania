#include "Enemy.h"
#include "Game.h"

bool Enemy::clockOn = false;

void Enemy::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, LPGAMEOBJECT simon)
{
	CGameObject::Update(dt);
	if (clockOn)
	{
		dx = 0;
		dy = 0;
	}
	if (!CheckOutCamera() && active == true)
		isDead = true;
}

void Enemy::Render()
{

}

void Enemy::DropItem()
{
	int iditem = rand() % + 4;
	item = new Item();
	item->SetPosition(x, y);
	item->SetState(iditem);
}

bool Enemy::CheckOutCamera()
{
	CGame* game = CGame::GetInstance();
	return (x >= game->GetCamPosX() + 10 && x < game->GetCamPosX() + (SCREEN_WIDTH - 10) && y >= game->GetCamPosY() && y < game->GetCamPosY() + (SCREEN_HEIGHT));
}

Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}
