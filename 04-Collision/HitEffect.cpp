#include "HitEffect.h"
#include "Animation.h"

void HitEffect::Render()
{
	CAnimationSets::GetInstance()->Get(6)->at(0)->Render(0, x, y);
}

bool HitEffect::EffectTime()
{
	if (GetTickCount() - time > 700)
		return true;
	return false;
}

HitEffect::HitEffect(int x, int y)
{
	time = GetTickCount();
	this->x = x;
	this->y = y;
}
