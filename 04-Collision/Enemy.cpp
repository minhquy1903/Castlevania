#include "Enemy.h"



void Enemy::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, LPGAMEOBJECT simon)
{
	CGameObject::Update(dt);

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

Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}
