#include "header.h"


static void SetCard();
static Card card[5] = { 0 }; /*�Ͻ������� ����� �� ���߿��� ������Ͽ��� �������� �ɷ� �մϴ�.*/

static CImage bgImg;
static CImage charIdle1;
static CImage charIdle2;
static CImage charAttack1;
static CImage charAttack2;
static CImage charAttack3;
static CImage cardImg;

static int selected = -1;

static void SetImg();
static void SetCard();
void DrawPlayer(HDC hDC, Player* player);

void DisplayGame(HDC hDC, Player* player)
{
	/*�̹��� ����*/
	SetImg();


	/*���ȭ�� �׸���*/
	int bgw = bgImg.GetWidth();
	int bgh = bgImg.GetHeight();
	bgImg.Draw(hDC, 0, 0, WindowWidth, WindowHeight, 0, 0, bgw, bgh);

	/*ĳ���� �׸���*/

	/*ī�� ����(����� �ƹ��͵� ����)*/
	SetCard();

	DrawPlayer(hDC, player);
	
}

void SetImg()
{
	if (bgImg.IsNull())
	{
		bgImg.Load(L"bgImg_stage1.jpg");
	}
	if (charIdle1.IsNull())
	{
		charIdle1.Load(L"charIdle1.png");
	}
	if (charIdle2.IsNull())
	{
		charIdle2.Load(L"charIdle2.png");
	}
	if (charAttack1.IsNull())
	{
		charAttack1.Load(L"charAttack1.png");
	}
	if (charAttack2.IsNull())
	{
		charAttack2.Load(L"charAttack2.png");
	}
	if (charAttack3.IsNull())
	{
		charAttack3.Load(L"charAttack3.png");
	}
	if (cardImg.IsNull())
	{
		cardImg.Load(L"charIdle1.png");
	}
	
}

void SetCard()
{


}

void DrawPlayer(HDC hDC, Player* player)
{
	if (player->animation_state == State_Idle)
	{
		switch (player->animation_num)
		{
		case 0:
		{
			int pw = charIdle1.GetWidth();
			int ph = charIdle1.GetHeight();
			charIdle1.Draw(hDC, player->x, 600, pw, ph, 0, 0, pw, ph);
		}
			break;
		case 1:
		{
			int pw = charIdle1.GetWidth();
			int ph = charIdle1.GetHeight();
			charIdle1.Draw(hDC, player->x, 600, pw + 2, ph + 2, 0, 0, pw, ph);
		}
			break;
		case 2:
		{
			int pw = charIdle1.GetWidth();
			int ph = charIdle1.GetHeight();
			charIdle1.Draw(hDC, player->x, 600, pw + 4, ph + 4, 0, 0, pw, ph);
		}
			break;
		case 3:
		{
			int pw = charIdle1.GetWidth();
			int ph = charIdle1.GetHeight();
			charIdle1.Draw(hDC, player->x, 600, pw + 2, ph + 2, 0, 0, pw, ph);
		}
			break;
		case 4:
		{
			int pw = charIdle1.GetWidth();
			int ph = charIdle1.GetHeight();
			charIdle1.Draw(hDC, player->x, 600, pw + 0, ph + 0, 0, 0, pw, ph);
		}
			break;
		default:
			break;
		}
	}
	else if (player->animation_state == State_Attack)
	{

	}
	else if (player->animation_state == State_Deffence)
	{

	}
}

