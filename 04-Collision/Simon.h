#pragma once
#include "GameObject.h"
#include "Whip.h"
#include "SubWeapon.h"
#include "Knife.h"
#include "Boomerang.h"
#include "Enemy.h"

#define SIMON_WALKING_SPEED		0.15f 
#define SIMON_GO_STAIR_SPEED	0.078f
#define SIMON_JUMP_SPEED_Y		0.56f
#define SIMON_HURT_SPEED_Y		0.36f
#define MARIO_JUMP_DEFLECT_SPEED 0.2f
#define SIMON_GRAVITY			0.002f

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
#define SIMON_STAND_ON_STAIR	13
#define SIMON_DEAD				12

#define SIMON_BOX_WIDTH  45
#define SIMON_BOX_HEIGHT 61
#define SIMON_UNTOUCHABLE_TIME 5000
#define TIME_SIMON_DIE			2500
#define SIMON_LIFE		3
#define SIMON_HP		16
#define RGB_255			255
#define TIME_LIFE		300
#define TIME_HURT		2500

#define BIG_HEART		5
#define SMALL_HEART		1
#define INVISIBILYTY_TIME	4000

#define POS_RIGHT	1460
#define POS_LEFT	-10
#define A_MINUTE	60
class Simon : public CGameObject
{
public:
	int typeSubWeapon;
	int untouchable;
	int directionOnStair;
	bool subWeaponIsON;
	int timeLife;
	int second;
	int posXStair;
	int health;
	int life;
	int heart;
	int currentSubweapon;
	int alpha;
	bool isFlicker;
	bool isOnBridge;
	bool revival;
	bool isDead;
	int currentScene;
	int nxStairTop;
	int nxStairBottom;
	int pairStair;
	int xCam;
	bool isDouble;
	bool isTriple;
	bool normalHit;
	bool isTouchStairTop;
	bool isTouchStairBottom;
	bool checkTouchStairBottom;
	bool checkTouchStairTop;
	int whipLvl;
	bool invisibility;
	bool clockOn;
	DWORD timeClock;
	DWORD invisibilityTime;
	DWORD untouchable_start;
	DWORD recoveryTime;
	Whip* whip;
	vector<SubWeapon*> weapon;

public:
	Simon();
	void SetAnimation(int ani) { this->ani = ani; }
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
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();
	void SetState(int state);
	bool AutoWalk(int toX);
	void CollideWithItem(vector<LPGAMEOBJECT>* listItems = NULL);
	void CollodeWhitBirck(vector<LPGAMEOBJECT>* coObjects = NULL);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	int CollideWithPortal(vector<LPGAMEOBJECT>* portal);
	void SimonTouchStair(vector<LPGAMEOBJECT>* stair = NULL);
	void CollideWithEnemy(vector<LPENEMY>* enemy = NULL);
	void ResetSubweapon();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	int GetPosXStair() { return posXStair; }
	void KeepSimonIntoScreen();
	void TimeLife();
	void NewWhip() { whip = NULL; whip = new Whip(); }
	Whip* GetWhip() { return whip; }
	vector<SubWeapon*> GetWeapon() { return weapon; }

};