#pragma once
#include "GameObject.h"
#define ITEM_UPGRADE_WHIP	0
#define ITEM_HEART			1
#define ITEM_KNIFE			2
#define ITEM_BOOMERANG		3
#define ITEM_AXE			4
#define ITEM_HOLYWATER		5
#define ITEM_DOUBLE			6
#define ITEM_TRIPLE			7
#define	ITEM_INVISIBILITY	8
#define ITEM_CLOCK			9
#define ITEM_SMALLHEART		10

#define TIME_FLICKER		1500
#define LIFE_TIME			3000

#define HEART_BBOX			24
#define	KNIFE_BBOX_WIDTH	32
#define KNIFE_BBOX_HEIGHT	16
#define	BBOX_32			32

#define VY_ITEM				0.15f
#define ANIMATIONSET_ITEM	4
#define TIME_CLOCK			2500
class Item : public CGameObject
{
	DWORD lifeTimeStart;
	bool isTimeOut;
	bool isFlicker;
public:
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	bool GetTimeOut() { return isTimeOut; }
	void Render();
	Item();
	~Item();
};

