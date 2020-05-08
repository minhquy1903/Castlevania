#pragma once
#include "GameObject.h"
#include "Whip.h"
#include "SubWeapon.h"
#include "Knife.h"

#define SIMON_WALKING_SPEED		0.15f 
#define SIMON_WALKING_UP		0.15f
#define SIMON_JUMP_SPEED_Y		0.6f
#define MARIO_JUMP_DEFLECT_SPEED 0.2f
#define GRAVITY					0.002f

#define SIMON_IDLE				0
#define SIMON_WALKING			1
#define SIMON_SIT				2
#define SIMON_JUMP				3
#define SIMON_STAND_HIT			4
#define SIMON_SIT_HIT			5
#define SIMON_SHOCK				6
#define SIMON_STAIR_UP			7
#define SIMON_STAND_ON_STAIR	11
#define SIMON_STAIR_DOWN		8
#define SIMON_STAIR_UP_HIT		9
#define SIMON_STAIR_DOWN_HIT	10


#define SIMON_BOX_WIDTH  30
#define SIMON_BOX_HEIGHT 64
#define SIMON_UNTOUCHABLE_TIME 5000

class CSimon : public CGameObject
{
	int untouchable;
	int ani;
	bool subWeaponIsON;
	int nxStair;
	int nyStair;
	DWORD untouchable_start;
	Whip *whip;
	SubWeapon * weapon;

public: 
	CSimon();
	void SetAnimation(int ani) { this->ani = ani; }
	bool isTouchStairTop;
	bool isTouchStairBottom;
	bool isOnStair;
	bool isGrounded;
	void WalkLeft();
	void WalkRight();
	void Jump();
	void Hit();
	void HitWeapon();
	void GoUpStair();
	void StandOnStair();
	void GoDownStair();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void SetState(int state);
	void CollideWithItem(vector<LPGAMEOBJECT> *listItems = NULL);
	void CollodeWhitBirck(vector<LPGAMEOBJECT> *coObjects = NULL);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	bool CollideWithPortal(vector<LPGAMEOBJECT> *portal);
	void SimonTouchStair(vector<LPGAMEOBJECT> *stair = NULL);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	Whip* GetWhip() { return whip; }
	SubWeapon * GetWeapon() { return weapon; }
	
};