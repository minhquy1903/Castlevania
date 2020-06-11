#include "Torch.h"
#include "Whip.h"
#include "Utils.h"
#include "Knife.h"
void Torch::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + 32;
	bottom = top + 64;
}

void Torch::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)	
{
	if (state == BREAK_TORCH && animation_set->at(state)->IsRenderOver(400)) 
	{
		DropItem();
		renderFireDone = true;
	}
}

void Torch::Render()
{
	//RenderBoundingBox();
	animation_set->at(state)->Render(0, x, y);
}

void Torch::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BREAK_TORCH:
		animation_set->at(state)->StartRenderAnimation();
		break;
	}
}

void Torch::DropItem()
{
	item = new Item();
	item->SetPosition(x, y);
	item->SetState(idItem);
}

Torch::Torch()
{
	
}

Torch::Torch(int idItem)
{
	state = NOMAL_TORCH;
	this->idItem = idItem;
}


Torch::~Torch()
{
}
