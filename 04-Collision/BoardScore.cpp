#include "BoardScore.h"
#include "Boss.h"
void BoardScore::DrawNumber(int x, int y, string stringNumb)
{
	for (int i = 0; i < stringNumb.size(); i++)
	{
		if (stringNumb[i] == ' ')
			continue;
		int numb;
		for (int j = 0; j < 10; j++)
		{
			numb = 48 + j;
			if (stringNumb[i] == numb)
			{
				number = CSprites::GetInstance()->Get(450 + j);
				break;
			}
		}
		number->Draw(0, x + (i * 15), y);//0 0 là x và y
	}
}

void BoardScore::DrawSubWeapon()
{
	if(idSubWeapon == ITEM_KNIFE)
		CSprites::GetInstance()->Get(ITEM_KNIFE_SPRITE)->Draw(0, posX + 310, 38);
	if (idSubWeapon == ITEM_AXE)
		CSprites::GetInstance()->Get(ITEM_AXE_SPRITE)->Draw(0, posX + 310, 30);
	if(idSubWeapon == ITEM_BOOMERANG)
		CSprites::GetInstance()->Get(ITEM_BOOMERANG_SPRITE)->Draw(0, posX + 310, 30);
	if(idSubWeapon == ITEM_HOLYWATER)
		CSprites::GetInstance()->Get(ITEM_HOLY_SPRITE)->Draw(0, posX + 310, 30);
	if(idSubWeapon == ITEM_CLOCK)
		CSprites::GetInstance()->Get(ITEM_CLOCK_SPRITE)->Draw(0, posX + 310, 30);
}

void BoardScore::DrawParameter()
{
	DrawNumber(posX + 295, 14, to_string(time));//timer
	DrawNumber(posX + 103, 14, to_string(score));//score
	DrawNumber(posX + 393, 33, to_string(heart));//heart
	DrawNumber(posX + 465, 14, to_string(1));//stage
	DrawNumber(posX + 395, 52, to_string(life));//life
}

void BoardScore::Update(DWORD dt, int camX, int camY, LPGAMEOBJECT _simon, LPGAMEOBJECT _boss)
{
	posX = camX;
	posY = camY;
	
	Simon * simon = dynamic_cast<Simon*>(_simon);
	
	time = simon->timeLife;
	healthSimon = simon->health;
	if (_boss != NULL)
	{
		Boss* boss = dynamic_cast<Boss*>(_boss);
		healthBoss = boss->hp;
	}
	
	life = simon->life;
	heart = simon->heart;
	idSubWeapon = simon->currentSubweapon;
	healthSimonLost = HP_SIMON_AND_BOSS - healthSimon;
	if (healthSimon < 0)
		healthSimon = 0;
	healthBossLost = HP_SIMON_AND_BOSS - healthBoss;
	if (healthSimonLost > HP_SIMON_AND_BOSS)
		healthSimonLost = 0;
}

void BoardScore::Render()
{
	DrawBoard();
	DrawHealth();
	DrawParameter();
	DrawSubWeapon();
}

void BoardScore::DrawHealth()
{
	for (int i = 0; i < healthSimon; i++) {
		healthbar.at(0)->Draw(0, 108 + i * 9 + posX, 33);
	}
	for (int i = 0; i < healthSimonLost; i++) {
		healthbar.at(1)->Draw(0, 99 + (16 - i) * 9 + posX, 33);
	}

	for (int i = 0; i < healthBoss; i++) {
		healthbar.at(2)->Draw(0, 108 + i * 9 + posX, 51);
	}
	for (int i = 0; i < healthBossLost; i++) {
		healthbar.at(1)->Draw(0, 99 + (16 - i) * 9 + posX, 51);
	}
}

void BoardScore::DrawBoard()
{
	CSprites::GetInstance()->Get(BOARD)->Draw(0, posX, posY);
}

BoardScore::BoardScore()
{
	healthbar.push_back(CSprites::GetInstance()->Get(400));
	healthbar.push_back(CSprites::GetInstance()->Get(401));
	healthbar.push_back(CSprites::GetInstance()->Get(402));
	time = LIFE_TIME;
}


BoardScore::~BoardScore()
{
}
