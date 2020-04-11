#pragma once
#include "GameObject.h"
#include "Whip.h"
#define SIMON_WALKING_SPEED		0.15f 
//0.1f
#define SIMON_JUMP_SPEED_Y		0.6f
#define MARIO_JUMP_DEFLECT_SPEED 0.2f
#define GRAVITY			0.002f

#define SIMON_IDLE		    0
#define SIMON_WALKING		1
#define SIMON_JUMP			2
#define SIMON_SIT			3
#define SIMON_STAND_HIT		4
#define SIMON_SIT_HIT		5


#define SIMON_BOX_WIDTH  30
#define SIMON_BOX_HEIGHT 64

#define SIMON_UNTOUCHABLE_TIME 5000

//
#define SIMON_SPRITE_IDLE  11
#define SIMON_SPRITE_WALK1 12
#define SIMON_SPRITE_WALK2 13
#define SIMON_SPRITE_WALK3 14
#define SIMON_SPRITE_JUMP  15
#define SIMON_SPRITE_SIT   16
#define SIMON_SPRITE_STAND_HIT1  17
#define SIMON_SPRITE_STAND_HIT2  18
#define SIMON_SPRITE_STAND_HIT3  19
#define SIMON_SPRITE_SIT_HIT1  20
#define SIMON_SPRITE_SIT_HIT2  21
#define SIMON_SPRITE_SIT_HIT3  22
//

class CSimon : public CGameObject
{
	int untouchable;
	int ani;
	DWORD untouchable_start;
	Whip *whip;

public: 
	CSimon() : CGameObject()
	{
		untouchable = 0;
		whip = new Whip();
	}
	bool isHitting = false;
	bool isGrounded;
	void WalkLeft();
	void WalkRight();
	void Jump();
	void Hit();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	void Render();
	void SetState(int state);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};