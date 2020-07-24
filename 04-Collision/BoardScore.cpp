#include "BoardScore.h"



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
	if(idSubWeapon == 2)
		CSprites::GetInstance()->Get(202)->Draw(0, posX + 310, 38);
	if (idSubWeapon == 4)
	{
		CSprites::GetInstance()->Get(204)->Draw(0, posX + 310, 38);
	}
}

void BoardScore::DrawParameter()
{
	DrawNumber(posX + 295, 14, to_string(time));//timer
	DrawNumber(posX + 103, 14, to_string(score));//score
	DrawNumber(posX + 393, 33, to_string(heart));//heart
	DrawNumber(posX + 465, 14, to_string(1));//stage
	DrawNumber(posX + 395, 52, to_string(life));//life
}

void BoardScore::Update(DWORD dt, int camX, int camY, LPGAMEOBJECT _simon, LPGAMEOBJECT boss)
{
	posX = camX;
	posY = camY;
	
	Simon * simon = dynamic_cast<Simon*>(_simon);
	time = simon->timeLife;
	healthSimon = simon->health;
	life = simon->life;
	heart = simon->heart;
	idSubWeapon = simon->currentSubweapon;
	healthSimonLost = HP_SIMON_AND_BOSS - healthSimon;
	if (healthSimon < 0)
		healthSimon = 0;
	healthBoss = HP_SIMON_AND_BOSS;
	healthBossLost = 0;
	if (healthSimonLost > HP_SIMON_AND_BOSS)
		healthSimonLost = HP_SIMON_AND_BOSS;
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
		healthbar.at(1)->Draw(0, posX, posY);
	}
}

void BoardScore::DrawBoard()
{
	CSprites::GetInstance()->Get(351)->Draw(0, posX, posY);
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
