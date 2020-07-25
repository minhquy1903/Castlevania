#pragma once
#include "Sprites.h"
#define HIT_EFFIECT	6
class HitEffect;
typedef HitEffect* LPHITEFFECT;
class HitEffect
{
public:
	DWORD time;
	int x;
	int y;
public:
	void Render();
	bool EffectTime();
	HitEffect(int x, int y);
	~HitEffect() {}
};

