#pragma once
#include "GameObject.h"
#include "Whip.h"
#include "SubWeapon.h"
#include "Knife.h"
#include "Boomerang.h"

#define SIMON_WALKING_SPEED		0.15f 
#define SIMON_GO_STAIR_SPEED	0.078f
#define SIMON_JUMP_SPEED_Y		0.56f
#define SIMON_HURT_SPEED_Y		0.43f
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
#define SIMON_STAIR_DOWN		8
#define SIMON_STAIR_UP_HIT		9
#define SIMON_STAIR_DOWN_HIT	10
#define SIMON_HURT				11
#define SIMON_STAND_ON_STAIR	12

#define SIMON_BOX_WIDTH  45
#define SIMON_BOX_HEIGHT 63
#define SIMON_UNTOUCHABLE_TIME 5000

class CSimon : public CGameObject
{
	int typeSubWeapon;
	int untouchable;
	int directionOnStair;
	bool subWeaponIsON;
	int nxStair;
	int nyStair;
	int posXStair;
	int health;
	int life;
	int heart;
	int currentSubweapon;
	int alpha;
	bool isFlicker;
	bool isOnBridge;
	DWORD untouchable_start;
	DWORD recoveryTime;
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
	void UseSubweapon();
	void GoUpStair();
	void StandOnStair();
	void GoDownStair();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void SetState(int state);
	bool AutoWalk(int toX);
	void CollideWithItem(vector<LPGAMEOBJECT> *listItems = NULL);
	void CollodeWhitBirck(vector<LPGAMEOBJECT> *coObjects = NULL);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	int CollideWithPortal(vector<LPGAMEOBJECT> *portal);
	void SimonTouchStair(vector<LPGAMEOBJECT> *stair = NULL);
	void CollideWithEnemy(vector<LPGAMEOBJECT> *enemy = NULL);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	int GetHealth() { return health; }
	int GetHeart() { return heart; }
	int GetLife() { return life; }
	int GetPosXStair() { return posXStair; }
	int GetCurrentSubweapon() { return currentSubweapon; }
	Whip* GetWhip() { return whip; }
	SubWeapon * GetWeapon() { return weapon; }
	
};