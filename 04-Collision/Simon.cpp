#include <algorithm>
#include "Utils.h"

#include "Bat.h"
#include "Game.h"
#include "Portal.h"
#include "Brick.h"
#include "Simon.h"
#include "Item.h"
#include "Stair.h"

CSimon::CSimon()
{
	untouchable = 0;
	whip = new Whip();
	weapon = new Knife();
	subWeaponIsON = false;
	isTouchStairTop = false;
	isOnStair = false;
	health = 16;
	life = 3; 
	heart = 0;
	currentSubweapon = -1;
}

void CSimon::WalkLeft()
{
	if (isGrounded)
	{
	nx = -1;
	SetState(SIMON_WALKING);
	}

}

void CSimon::WalkRight()
{
	if (isGrounded)
	{
	nx = 1;
	SetState(SIMON_WALKING);
	}
	
}

void CSimon::Jump()
{
	if (GetState() == SIMON_STAND_HIT || GetState() == SIMON_SIT_HIT || GetState() == SIMON_SHOCK)
		return;
	if (isGrounded && !(state == SIMON_SIT)) // đang trên mặt đất và đang không ngồi thì mới nhảy đc
	{
		SetState(SIMON_JUMP);
	}
	
}

void CSimon::Hit()
{
	whip->SetNx(nx);
	if (GetState() == SIMON_SHOCK)
		return;
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

void CSimon::UseSubweapon()
{
	if (GetState() == SIMON_SHOCK)
		return;
	
	switch (typeSubWeapon)
	{
	case (ITEM_KNIFE || ITEM_BOOMERANG):
		if (!subWeaponIsON || heart < 1)
		{
			Hit();
			return;
		}
		if (weapon->isSubWeaponExist)
			return;
		Hit();
		heart--;
		weapon->SetNx(nx);
		weapon->isHittingSubWeapon = true;
		weapon->SetDirectionSubWeapon(nx);
		break;
	}	
}

void CSimon::GoUpStair()
{
	if (nyStair == -1)
		nx = nxStair;
	else
		nx = -nxStair;
	SetState(SIMON_STAIR_UP);
}

void CSimon::StandOnStair()
{
	SetState(SIMON_STAND_ON_STAIR);
}


void CSimon::GoDownStair()
{
	if (nyStair == -1)
		nx = -nxStair;
	else
		nx = nxStair;
	SetState(SIMON_STAIR_DOWN);
}

void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);

	// Simple fall down
	
	//whip
	if (ani != SIMON_SIT_HIT)
	{
		whip->SetPosition(x - 90, y);
	}
	else
	{
		whip->SetPosition(x - 90, y + 15);
	}
	//
	if (weapon->isSubWeaponExist && subWeaponIsON)
	{
		weapon->Update(dt);
	}
	
	if (isOnStair)
	{
		x += dx;
		y += dy;
	}
	else
	{
		vy += GRAVITY * dt;
		CollodeWhitBirck(coObjects);
		
	}
		
}

void CSimon::Render()
{
	animation_set->at(ani)->Render(nx, x, y);
	if ((ani == SIMON_STAND_HIT || ani == SIMON_SIT_HIT) && !weapon->isHittingSubWeapon || (weapon->isHittingSubWeapon && !subWeaponIsON))
	{
		whip->Render(animation_set->at(ani)->GetCurrentFrame());
	}
	//RenderBoundingBox();
	if (subWeaponIsON)
		weapon->Render();
	
	

	//RenderBoundingBox();
}

void CSimon::SetState(int state)
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
		isGrounded = false;
		ani = SIMON_JUMP;
		vy = -SIMON_JUMP_SPEED_Y;
		break;
	case SIMON_SIT:
		vx = 0;
		ani = SIMON_SIT;
		break;
	case SIMON_IDLE:
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
		animation_set->at(ani)->StartRenderAnimation();
		ani = SIMON_STAIR_UP;
		if(nx == 1)
			vx = SIMON_GO_STAIR_SPEED;
		else
			vx = -SIMON_GO_STAIR_SPEED;
		vy = -SIMON_GO_STAIR_SPEED;
		break;
	case SIMON_STAIR_DOWN:
		animation_set->at(ani)->StartRenderAnimation();
		ani = SIMON_STAIR_DOWN;
		if (nx == 1)
			vx = SIMON_GO_STAIR_SPEED;
		else
			vx = -SIMON_GO_STAIR_SPEED;
		vy = SIMON_GO_STAIR_SPEED;
		break;
	case SIMON_STAND_ON_STAIR:
		if(nx == 1)
			ani = SIMON_STAIR_UP;
		else
			ani = SIMON_STAIR_DOWN;
		animation_set->at(ani)->SetCurrentFrame();
		vx = 0;
		vy = 0;
		break;
	}
}

bool CSimon::AutoWalk(int toX)
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


void CSimon::CollideWithItem(vector<LPGAMEOBJECT> *listItems)
{
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
					whip->SetState(WHIP_LVL_2);
				else if (whip->GetState() == WHIP_LVL_2)
					whip->SetState(WHIP_LVL_3);
			}
			else if (e->GetState() == ITEM_HEART)
			{
				heart += 5;
			}
			else if (e->GetState() == ITEM_KNIFE)
			{
				typeSubWeapon = ITEM_KNIFE;
				subWeaponIsON = true;
				weapon = new Knife();
				currentSubweapon = 0;
			}
			else if (e->GetState() == ITEM_BOOMERANG)
			{
				typeSubWeapon = ITEM_BOOMERANG;
				subWeaponIsON = true;
				weapon = new Boomerang();
				currentSubweapon = 1;
			}
			vector<LPGAMEOBJECT>::iterator it;
			it = listItems->begin();
			listItems->erase(it);
		}
	}
}

void CSimon::CollodeWhitBirck(vector<LPGAMEOBJECT>* coObjects)
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
			x += dx;
			y += dy;
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

			if (dynamic_cast<Brick *>(e->obj)) // if e->obj is Goomba 
			{
				if (e->ny != 0)
				{
					/*isGrounded = true;*/
					if (e->ny == -1)
					{
						isGrounded = true;
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

int CSimon::CollideWithPortal(vector<LPGAMEOBJECT>* portal)
{
	if (portal->size() == 0)
		return false;
	LPGAMEOBJECT obj = portal->at(0);
	CPortal* e = dynamic_cast<CPortal*>(obj);
	if (AABBCollision(obj))
	{
		SetPosition(e->GetXNextPortal(), e->GetYNextPortal());
		return e->GetSceneID();
	}
	return 0;
}

void CSimon::SimonTouchStair(vector<LPGAMEOBJECT>* stair)
{
	for (int i = 0; i < stair->size(); i++)
	{
		LPGAMEOBJECT obj = stair->at(i);
		
		if (AABBCollision(obj))
		{
			Stair *e = dynamic_cast<Stair*>(obj);
			nxStair = obj->nx;
			nyStair = obj->ny;
			float left_a, top_a, right_a, bottom_a;
			GetBoundingBox(left_a, top_a, right_a, bottom_a);
			if (left_a < e->GetMidStair() && right_a > e->GetMidStair() && top_a < e->y && bottom_a > e->y)
				isOnStair = false;
			if (nyStair == 1)
			{
				isTouchStairTop = true;
				posXStair = 348;
			}
			else
			{
				posXStair = e->GetMidStair() - 1;
				isTouchStairBottom = true;
			}

			if (isTouchStairBottom || isTouchStairTop)
				return;
		}
		else
		{
			if(obj->ny == 1)
				isTouchStairTop = false;
			else
				isTouchStairBottom = false;
		}
	}
}

void CSimon::CollideWithEnemy(vector<LPGAMEOBJECT>* enemy)
{
	for (int i = 0; i < enemy->size(); i++)
	{
		LPGAMEOBJECT obj = enemy->at(i);
		if (AABBCollision(obj))
		{
			if (dynamic_cast<Bat*>(obj))
			{
				Bat *bat = dynamic_cast<Bat*>(obj);
				if (!bat->GetIsWakeUp())
				{
					bat->SetISWakeUp(true);
				}
				else
				{
					health--;
				}
			}
		}
	}
}

void CSimon::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x + 15;
	top = y; 
	right = x + SIMON_BOX_WIDTH;
	bottom = y + SIMON_BOX_HEIGHT;
}

