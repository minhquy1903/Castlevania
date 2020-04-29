#pragma once
#include "GameObject.h"
#include "Whip.h"
#include "SubWeapon.h"
#include "Knife.h"

#define SIMON_WALKING_SPEED		0.15f 
#define SIMON_JUMP_SPEED_Y		0.6f
#define MARIO_JUMP_DEFLECT_SPEED 0.2f
#define GRAVITY			0.002f

#define SIMON_IDLE		    0
#define SIMON_WALKING		1
#define SIMON_SIT			2
#define SIMON_JUMP			3
#define SIMON_STAND_HIT		4
#define SIMON_SIT_HIT		5
#define SIMON_SHOCK			6


#define SIMON_BOX_WIDTH  30
#define SIMON_BOX_HEIGHT 64

#define SIMON_UNTOUCHABLE_TIME 5000

//

class CSimon : public CGameObject
{
	int untouchable;
	int ani;
	bool subWeaponIsON;
	DWORD untouchable_start;
	Whip *whip;
	SubWeapon * weapon;

public: 
	CSimon();
	bool isHittingWhip = false;
	bool isGrounded;
	void WalkLeft();
	void WalkRight();
	void Jump();
	void Hit();
	void HitWeapon();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void SetState(int state);
	void CollisionWithItem(vector<LPGAMEOBJECT> *listItems);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	bool CollisionWithPortal(vector<LPGAMEOBJECT> *portal);
	Whip* GetWhip() { return whip; }
	SubWeapon * GetWeapon() { return weapon; }
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};