#include "header.h"


static void SetCard();
static Card card[5] = { 0 }; /*일시적으로 사용할 뿐 나중에는 헤더파일에서 가져오는 걸로 합니다.*/

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

void DisplayGame(HDC hDC)
{
	/*이미지 설정*/
	SetImg();


	/*배경화면 그리기*/
	int bgw = bgImg.GetWidth();
	int bgh = bgImg.GetHeight();
	bgImg.Draw(hDC, 0, 0, WindowWidth, WindowHeight, 0, 0, 1600, 900);

	/*캐릭터 그리기*/

	/*카드 설정(현재는 아무것도 없음)*/
	SetCard();

	
	
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



