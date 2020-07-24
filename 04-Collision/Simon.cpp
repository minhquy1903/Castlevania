#include <algorithm>
#include "Utils.h"

#include "Bat.h"
#include "Game.h"
#include "Portal.h"
#include "Brick.h"
#include "Simon.h"
#include "Item.h"
#include "Stair.h"
#include "Knight.h"
#include "Ghost.h"
#include "Bridge.h"
#include "Axe.h"
#include "HolyWater.h"
#include "Raven.h"
Simon::Simon()
{
	untouchable = 0;
	whip = new Whip();
	weapon.push_back(new Knife());
	subWeaponIsON = false;
	isOnStair = false;
	health = SIMON_HP;
	life = SIMON_LIFE;
	heart = 0;
	currentSubweapon = -1;
	isFlicker = false;
	alpha = RGB_255;
	timeLife = TIME_LIFE;
	pairStair = 0;
	whipLvl = 0;
	second = 1;
}

void Simon::WalkLeft()
{
	if (isGrounded)
	{
		nx = -1;
		SetState(SIMON_WALKING);
	}

}

void Simon::WalkRight()
{
	if (isGrounded)
	{
		nx = 1;
		SetState(SIMON_WALKING);
	}

}

void Simon::Jump()
{
	if (GetState() == SIMON_STAND_HIT || GetState() == SIMON_SIT_HIT || GetState() == SIMON_SHOCK || isOnStair)
		return;
	if (isGrounded && !(state == SIMON_SIT)) // đang trên mặt đất và đang không ngồi thì mới nhảy đc
	{
		SetState(SIMON_JUMP);
	}

}

void Simon::Hit()
{
	whip->SetNx(nx);

	if (isOnStair)
	{
		if (directionOnStair == 1)
		{
			SetState(SIMON_STAIR_UP_HIT);
		}
		else
			SetState(SIMON_STAIR_DOWN_HIT);
		return;
	}

	if ((GetState() == SIMON_IDLE || GetState() == SIMON_JUMP || GetState() == SIMON_WALKING))
	{
		if (isGrounded)
		{
			SetState(SIMON_STAND_HIT);
			vx = 0;
		}
		else
			SetState(SIMON_STAND_HIT);
	}
	else if (GetState() == SIMON_SIT)
		SetState(SIMON_SIT_HIT);

}

void Simon::UseSubweapon()
{
	int x = 1;
	if (GetState() == SIMON_SHOCK)
		return;
	if (currentSubweapon == -1)
	{
		normalHit = true;
		Hit();
		return;
	}
	switch (currentSubweapon)
	{
	case ITEM_KNIFE:
		if (!subWeaponIsON || heart < 1)
		{
			normalHit = true;
			Hit();
			return;
		}
		for (int i = 0; i < weapon.size(); i++)
		{
			if (!weapon[i]->isSubWeaponExist) // subweapon k con ton tai
			{
				weapon[i]->SetNx(nx);
				weapon[i]->isHittingSubWeapon = true;
				weapon[i]->SetDirectionSubWeapon(nx);
				weapon[i]->active = true;
				heart--;
				x++;
			}
			if(x == 1 && weapon[weapon.size() - 1]->isSubWeaponExist)
				normalHit = true;
			if (weapon[i]->isHittingSubWeapon)
			break;
			
				
		}
		
		Hit();
		break;
	case ITEM_AXE:
		if (!subWeaponIsON || heart < 1)
		{
			normalHit = true;
			Hit();
			return;
		}

		for (int i = 0; i < weapon.size(); i++)
		{
			if (!weapon[i]->isSubWeaponExist)
			{
				Hit();
				heart--;
				weapon[i]->SetNx(nx);
				weapon[i]->vy = -VY_AXE;
				weapon[i]->isHittingSubWeapon = true;
				weapon[i]->SetDirectionSubWeapon(nx);
			}
			if (weapon[i]->isHittingSubWeapon)
				break;
		}
		break;
	case ITEM_BOOMERANG:
		if (!subWeaponIsON || heart < 1)
		{
			normalHit = true;
			Hit();
			return;
		}

		for (int i = 0; i < weapon.size(); i++)
		{
			if (!weapon[i]->isSubWeaponExist)
			{
				Hit();
				heart--;
				weapon[i]->SetNx(nx);
				weapon[i]->isHittingSubWeapon = true;
				weapon[i]->SetDirectionSubWeapon(nx);
			}
			if (weapon[i]->isHittingSubWeapon)
				break;
		}
		break;
	case ITEM_HOLYWATER:
		if (!subWeaponIsON || heart < 1)
		{
			normalHit = true;
			Hit();
			return;
		}

		for (int i = 0; i < weapon.size(); i++)
		{
			if (!weapon[i]->isSubWeaponExist)
			{
				Hit();
				heart--;
				weapon[i]->SetNx(nx);
				weapon[i]->vy = -VY_HOLYWATER;
				weapon[i]->isHittingSubWeapon = true;
				weapon[i]->SetDirectionSubWeapon(nx);
			}
			if (weapon[i]->isHittingSubWeapon)
				break;
		}
		break;
	case ITEM_CLOCK:
		if (!subWeaponIsON || heart < 5)
			return;
		heart -= 5;
		clockOn = true;
		timeClock = GetTickCount();
	}
}

void Simon::GoUpStair()
{
	if (pairStair == 1)
		nx = 1;
	else
		nx = -1;
	SetState(SIMON_STAIR_UP);
}

void Simon::StandOnStair()
{
	SetState(SIMON_STAND_ON_STAIR);
}


void Simon::GoDownStair()
{
	if (pairStair == 1)
		nx = -1;
	else
		nx = 1;
	SetState(SIMON_STAIR_DOWN);
}

void Simon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	

	if (health <= 0 && !isDead)
	{
		SetState(SIMON_DEAD);
		isDead = true;
		isOnStair = false;
		alpha = 255;
		return;
	}

	if (isDead && animation_set->at(SIMON_DEAD)->IsRenderOver(TIME_SIMON_DIE))
	{
		revival = true;
	}
	// Calculate dx, dy 
	CGameObject::Update(dt);
	TimeLife();

	KeepSimonIntoScreen();
	// Simple fall down

	//whip
	if (ani != SIMON_SIT_HIT)
	{
		whip->SetPosition(x - SIMON_BOX_WIDTH * 2, y);
	}
	else
	{
		whip->SetPosition(x - SIMON_BOX_WIDTH * 2, y + SIMON_BOX_WIDTH / 3);
	}
	//
	
	//simon hurt
	if (!isDead)
		if (GetTickCount() - recoveryTime < TIME_HURT)
		{
			isFlicker = true;
			alpha = rand() % 255 + 150;
		}
		else
		{
			isFlicker = false;
			alpha = 255;
		}
	//
	if (isOnStair)
	{
		x += dx;
		y += dy;
	}
	else
	{
		vy +=SIMON_GRAVITY * dt;
	}
}


void Simon::Render()
{
	if (invisibility)
	{
		alpha = 100;
		if (GetTickCount() - invisibilityTime > INVISIBILYTY_TIME)
		{
			alpha = RGB_255;
			invisibility = false;
		}

	}
	animation_set->at(ani)->Render(nx, x, y, alpha);
	
	for (int i = 0; i < weapon.size(); i++)
	{
		if (weapon[i]->active || normalHit)
		{
			if ((ani == SIMON_STAND_HIT ||
				ani == SIMON_SIT_HIT ||
				ani == SIMON_STAIR_DOWN_HIT ||
				ani == SIMON_STAIR_UP_HIT) &&
				!weapon[i]->isHittingSubWeapon ||
				(weapon[i]->isHittingSubWeapon && !subWeaponIsON))
			{
				whip->Render(animation_set->at(ani)->GetCurrentFrame());
			}
			weapon[i]->active = false;
		}
	}
	//RenderBoundingBox();
	if (subWeaponIsON)
		for (int i = 0; i < weapon.size(); i++)
		{
			weapon[i]->Render();
		}
}

void Simon::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case SIMON_WALKING:
		if (nx == 1)
			vx = SIMON_WALKING_SPEED;
		else
			vx = -SIMON_WALKING_SPEED;
		ani = SIMON_WALKING;
		break;
	case SIMON_JUMP:
		if (isGrounded)
		{
			if (vx != SIMON_WALKING_SPEED && vx != -SIMON_WALKING_SPEED)
				vx = 0;
			isGrounded = false;
			vy = -SIMON_JUMP_SPEED_Y;

		}
		ani = SIMON_JUMP;
		break;
	case SIMON_SIT:
		if (!isOnBridge)
			vx = 0;
		ani = SIMON_SIT;
		break;
	case SIMON_IDLE:
		if (!isOnBridge)
			vx = 0;
		ani = SIMON_IDLE;
		break;
	case SIMON_SHOCK:
		vx = 0;
		ani = SIMON_SHOCK;
		animation_set->at(state)->StartRenderAnimation();
		break;
	case SIMON_SIT_HIT:
		vx = 0;
		ani = SIMON_SIT_HIT;
		animation_set->at(ani)->SetCurrentFrame();
		animation_set->at(ani)->StartRenderAnimation();
		break;
	case SIMON_STAND_HIT:
		ani = SIMON_STAND_HIT;
		animation_set->at(ani)->SetCurrentFrame();
		animation_set->at(ani)->StartRenderAnimation();
		break;
	case SIMON_STAIR_UP:
		directionOnStair = 1;
		animation_set->at(ani)->StartRenderAnimation();
		ani = SIMON_STAIR_UP;
		if (nx == 1)
			vx = SIMON_GO_STAIR_SPEED;
		else
			vx = -SIMON_GO_STAIR_SPEED;
		vy = -SIMON_GO_STAIR_SPEED;
		break;
	case SIMON_STAIR_DOWN:
		directionOnStair = -1;
		animation_set->at(ani)->StartRenderAnimation();
		ani = SIMON_STAIR_DOWN;
		if (nx == 1)
			vx = SIMON_GO_STAIR_SPEED;
		else
			vx = -SIMON_GO_STAIR_SPEED;
		vy = SIMON_GO_STAIR_SPEED;
		break;
	case SIMON_STAND_ON_STAIR:
		if (directionOnStair == 1)
			ani = SIMON_STAIR_UP;
		else
			ani = SIMON_STAIR_DOWN;
		animation_set->at(ani)->SetCurrentFrame();
		vx = 0;
		vy = 0;
		break;
	case SIMON_HURT:
		isGrounded = false;
		ani = SIMON_HURT;
		if (nx == 1)
			vx = -SIMON_WALKING_SPEED;
		else
			vx = SIMON_WALKING_SPEED;

		vy = -SIMON_HURT_SPEED_Y;
		animation_set->at(ani)->StartRenderAnimation();
		break;
	case SIMON_STAIR_DOWN_HIT:
		ani = SIMON_STAIR_DOWN_HIT;
		animation_set->at(ani)->SetCurrentFrame();
		animation_set->at(ani)->StartRenderAnimation();
		vx = 0;
		vy = 0;
		break;
	case SIMON_STAIR_UP_HIT:
		ani = SIMON_STAIR_UP_HIT;
		animation_set->at(ani)->SetCurrentFrame();
		animation_set->at(ani)->StartRenderAnimation();
		vx = 0;
		vy = 0;
		break;
	case SIMON_DEAD:
		ani = SIMON_DEAD;
		vx = 0;
		animation_set->at(ani)->StartRenderAnimation();
		break;
	}
}

bool Simon::AutoWalk(int toX)
{

	if (toX - (x + 30) > 2)
	{
		nx = 1;
		SetState(SIMON_WALKING);
		return false;
	}
	else if (toX - (x + 30) < -2)
	{
		nx = -1;
		SetState(SIMON_WALKING);
		return false;
	}
	else
		x = toX - 30;//sử lí if else cho topstair
	if (toX - (x + 30) == 0)
		return true;

	return false;
}


void Simon::CollideWithItem(vector<LPGAMEOBJECT>* listItems)
{
	if (isDead)
		return;
	if (listItems->size() == 0)
		return;
	for (int i = 0; i < listItems->size(); i++)
	{
		LPGAMEOBJECT obj = listItems->at(i);
		Item* e = dynamic_cast<Item*>(obj);
		if (AABBCollision(obj))
		{
			if (e->GetState() == ITEM_UPGRADE_WHIP)
			{
				SetState(SIMON_SHOCK);
				if (whip->GetState() == WHIP_LVL_1)
				{
					whip->SetState(WHIP_LVL_2);
					whipLvl = WHIP_LVL_2;
				}

				else if (whip->GetState() == WHIP_LVL_2)
				{
					whip->SetState(WHIP_LVL_3);
					whipLvl = WHIP_LVL_3;
				}
			}
			else if (e->GetState() == ITEM_HEART)
			{
				heart += BIG_HEART;
			}
			else if (e->GetState() == ITEM_KNIFE)
			{
				ResetSubweapon();
				SubWeapon* e = new Knife();
				typeSubWeapon = ITEM_KNIFE;
				subWeaponIsON = true;
				weapon.push_back(e);
				if (isDouble)
				{
					SubWeapon* e1 = new Knife();
					weapon.push_back(e1);
				}
				else if (isTriple)
				{
					SubWeapon* e1 = new Knife();
					SubWeapon* e2 = new Knife();
					weapon.push_back(e1);
					weapon.push_back(e2);
				}
				currentSubweapon = ITEM_KNIFE;
			}
			else if (e->GetState() == ITEM_BOOMERANG)
			{
				ResetSubweapon();
				typeSubWeapon = ITEM_BOOMERANG;
				subWeaponIsON = true;
				SubWeapon* e = new Boomerang();
				weapon.push_back(e);
				currentSubweapon = ITEM_BOOMERANG;
			}
			else if (e->state == ITEM_AXE)
			{
				ResetSubweapon();
				SubWeapon* e = new Axe();
				typeSubWeapon = ITEM_KNIFE;
				subWeaponIsON = true;
				weapon.push_back(e);
				if (isDouble)
				{
					SubWeapon* e1 = new Axe();
					weapon.push_back(e1);
				}
				else if (isTriple)
				{
					SubWeapon* e1 = new Axe();
					SubWeapon* e2 = new Axe();
					weapon.push_back(e1);
					weapon.push_back(e2);
				}
				currentSubweapon = ITEM_AXE;
			}
			else if (e->state == ITEM_DOUBLE)
			{
				if (isTriple)
					return;
				ResetSubweapon();
				if (currentSubweapon == ITEM_KNIFE)
				{
					SubWeapon* e1 = new Knife();
					SubWeapon* e2 = new Knife();
					weapon.push_back(e1);
					weapon.push_back(e2);
				}
				else if (currentSubweapon == ITEM_AXE)
				{
					SubWeapon* e1 = new Axe();
					SubWeapon* e2 = new Axe();
					weapon.push_back(e1);
					weapon.push_back(e2);
				}
				isDouble = true;
			}
			else if (e->state == ITEM_TRIPLE)
			{
				ResetSubweapon();
				if (currentSubweapon == ITEM_KNIFE)
				{
					SubWeapon* e1 = new Knife();
					SubWeapon* e2 = new Knife();
					SubWeapon* e3 = new Knife();
					weapon.push_back(e1);
					weapon.push_back(e2);
					weapon.push_back(e3);
				}
				else if (currentSubweapon == ITEM_AXE)
				{
					SubWeapon* e1 = new Axe();
					SubWeapon* e2 = new Axe();
					SubWeapon* e3 = new Axe();
					weapon.push_back(e1);
					weapon.push_back(e2);
					weapon.push_back(e3);
				}
				isDouble = false;
				isTriple = true;

			}
			else if (e->state == ITEM_HOLYWATER)
			{
				ResetSubweapon();
				SubWeapon* e = new HolyWater();
				typeSubWeapon = ITEM_HOLYWATER;
				subWeaponIsON = true;
				currentSubweapon = ITEM_HOLYWATER;
				weapon.push_back(e);
				if (isDouble)
				{
					SubWeapon* e1 = new HolyWater();
					weapon.push_back(e1);
				}
				else if (isTriple)
				{
					SubWeapon* e1 = new HolyWater();
					SubWeapon* e2 = new HolyWater();
					weapon.push_back(e1);
					weapon.push_back(e2);
				}
			}
			else if (e->state == ITEM_CLOCK)
			{
				ResetSubweapon();
				typeSubWeapon = ITEM_CLOCK;
				SubWeapon* e1 = new HolyWater();
				subWeaponIsON = true;
				weapon.push_back(e1);
				currentSubweapon = ITEM_CLOCK;
			}
			else if (e->state == ITEM_INVISIBILITY)
			{
				invisibility = true;
				invisibilityTime = GetTickCount();
			}
			else if (e->state == ITEM_SMALLHEART)
			{
			heart += SMALL_HEART;
			}
			vector<LPGAMEOBJECT>::iterator it;
			it = listItems->begin();
			listItems->erase(it);
		}
	}
}


void Simon::ResetSubweapon()
{
	int sizeWeapon = weapon.size();
	for (int i = 0; i < sizeWeapon; i++)
	{
		weapon.pop_back();
	}
	weapon.clear();
}

void Simon::CollodeWhitBirck(vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	// turn off collision when die 

	CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount() - untouchable_start > SIMON_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		if (!isOnStair)
		{
			x += dx;
			y += dy;
		}

	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;

		/*if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;*/

		// Collision logic with Goombas
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<Brick*>(e->obj)) // if e->obj is Goomba 
			{
				if (e->ny != 0)
				{
					/*isGrounded = true;*/
					if (e->ny == -1)
					{
						isGrounded = true;
						isOnBridge = false;
						vy = 0;
					}
					else
						y += dy;
				}
			}
			else if (dynamic_cast<Bridge*>(e->obj))
			{
				if (e->ny != 0)
				{
					if (e->ny == -1)
					{
						isOnBridge = true;
						isGrounded = true;
						vx = e->obj->vx;
						vy = 0;
					}
					else
						y += dy;
				}
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

int Simon::CollideWithPortal(vector<LPGAMEOBJECT>* portal)
{
	if (portal->size() == 0)
		return false;
	for (int i = 0; i < portal->size(); i++)
	{
		LPGAMEOBJECT obj = portal->at(i);
		CPortal* e = dynamic_cast<CPortal*>(obj);
		if (AABBCollision(obj))
		{
			SetPosition(e->GetXNextPortal(), e->GetYNextPortal());
			return e->GetSceneID();
		}

	}
	return 0;
}

void Simon::SimonTouchStair(vector<LPGAMEOBJECT>* stair)
{
	int countTop = 0, countBottom = 0;
	for (int i = 0; i < stair->size(); i++)
	{
		LPGAMEOBJECT obj = stair->at(i);
		float left_a, top_a, right_a, bottom_a;
		GetBoundingBox(left_a, top_a, right_a, bottom_a);
		Stair* e = dynamic_cast<Stair*>(obj);

		if (AABBCollision(obj))
		{
			if (e->typeStair == 1) // stair top
			{
				isTouchStairTop = true;
				countTop++;
				nxStairTop = e->nx;
				if (e->pair == pairStair)
				{
					if (isOnStair)
					{
						SetState(SIMON_IDLE);
						isOnStair = false;
						pairStair = 0;
					}
				}
				posXStair = e->midStairX;

			}
			else if (e->typeStair == -1)
			{
				isTouchStairBottom = true;
				countBottom++;
				nxStairBottom = e->nx;
				if (e->pair == pairStair)
					if (isOnStair)
					{
						isOnStair = false;
						SetState(SIMON_IDLE);
						pairStair = 0;
					}
				posXStair = e->midStairX;
			}
		}
		else
		{
			if (e->typeStair == 1 && countTop == 0)
			{
				isTouchStairTop = false;
			}
			else if (e->typeStair == -1 && countBottom == 0)
			{
				isTouchStairBottom = false;
			}
		}
	}

}

void Simon::CollideWithEnemy(vector<LPENEMY>* enemies)
{
	if (isDead)
		return;
	if (enemies->size() == 0)
		return;
	if (invisibility)
		return;
	for (int i = 0; i < enemies->size(); i++)
	{
		LPENEMY obj = enemies->at(i);
		if (!obj->isDead)
			if (AABBCollision(obj))
			{
				if (dynamic_cast<Bat*>(obj))
				{
					Bat* bat = dynamic_cast<Bat*>(obj);
					bat->hp = 0;
				}
				else if (dynamic_cast<Raven*>(obj))
				{
					Raven* raven = dynamic_cast<Raven*>(obj);
					raven->hp = 0;
				}

				if (isFlicker != true)
				{
					if (!isOnStair)
						SetState(SIMON_HURT);
					health -= obj->dame;
					recoveryTime = GetTickCount();
				}

			}
	}
}



void Simon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

	left = x + SIMON_BOX_WIDTH / 3;
	top = y;
	if (state == SIMON_SIT)
		top = y + SIMON_BOX_WIDTH / 3;
	right = x + SIMON_BOX_WIDTH;
	bottom = y + SIMON_BOX_HEIGHT;
}

void Simon::KeepSimonIntoScreen()
{
	if (x < POS_LEFT) //để cài không cho simon đi ngược màn hình
		x = POS_LEFT;
	if (x > POS_RIGHT)
		x = POS_RIGHT;
}

void Simon::TimeLife()
{
	second++;
	if (second == A_MINUTE)
	{
		timeLife--;
		second = 1;
	}
	if (timeLife <= 0)
		isDead = true;
}

