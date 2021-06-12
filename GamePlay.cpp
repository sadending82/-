#include "header.h"


static Card card[10] = { 0 }; /*일시적으로 사용할 뿐 나중에는 헤더파일에서 가져오는 걸로 합니다.*/

static CImage bgImg;
static CImage charIdle1;
static CImage charIdle2;
static CImage charAttack1;
static CImage charAttack2;
static CImage charAttack3;
static CImage charAttack4;
static CImage charAttack5;
static CImage charAttack6;
static CImage charAttack7;
static CImage AttackCardImg;
static CImage DeffenceCardImg;

static int selected = -1;
static BOOL isSelected = FALSE;
static BOOL isCardMove = FALSE;
static int MoveCard = 0;

static int timer = 0;

static void SetImg();
void DrawPlayer(HDC hDC, Player* player);

void DisplayGame(HDC hDC, Player* player)
{
	/*이미지 설정*/
	SetImg();


	/*배경화면 그리기*/
	int bgw = bgImg.GetWidth();
	int bgh = bgImg.GetHeight();
	bgImg.Draw(hDC, 0, 0, WindowWidth, WindowHeight, 0, 0, bgw, bgh);

	/*캐릭터 그리기*/

	/*카드 설정(현재는 아무것도 없음)*/
	

	if (player->isCharacterActive == TRUE)
	{
		DrawPlayer(hDC, player);
	}
	
}

void SetCard(Player* player)
{ // 임시로 막 넣었음.
	Card tmpCard;

	tmpCard.is_Active = TRUE;
	tmpCard.is_enhanced = FALSE;
	tmpCard.occupation = Card_Occu_ALL;
	tmpCard.type = Card_Type_Attack;
	tmpCard.number = 0;

	player->deck.card[0] = tmpCard;
	player->deck.card[1] = tmpCard;
	player->deck.card[2] = tmpCard;
	player->deck.card[3] = tmpCard;
	player->deck.card[4] = tmpCard;

	tmpCard.is_Active = TRUE;
	tmpCard.is_enhanced = FALSE;
	tmpCard.occupation = Card_Occu_ALL;
	tmpCard.type = Card_Type_Deffence;
	tmpCard.number = 0;

	player->deck.card[5] = tmpCard;
	player->deck.card[6] = tmpCard;
	player->deck.card[7] = tmpCard;
	player->deck.card[8] = tmpCard;
	player->deck.card[9] = tmpCard;
}

void SetImg()
{
	if (bgImg.IsNull())
	{
		bgImg.Load(L"bgImg_stage1.jpg");
	}
	if (charIdle1.IsNull())
	{
		charIdle1.Load(L"RcharIdle1.png");
	}
	if (charIdle2.IsNull())
	{
		charIdle2.Load(L"RcharIdle2.png");
	}
	if (charAttack1.IsNull())
	{
		charAttack1.Load(L"RcharAttack1.png");
	}
	if (charAttack2.IsNull())
	{
		charAttack2.Load(L"RcharAttack2.png");
	}
	if (charAttack3.IsNull())
	{
		charAttack3.Load(L"RcharAttack3.png");
	}
	if (charAttack4.IsNull())
	{
		charAttack4.Load(L"RcharAttack4.png");
	}
	if (charAttack5.IsNull())
	{
		charAttack5.Load(L"RcharAttack5.png");
	}
	if (charAttack6.IsNull())
	{
		charAttack6.Load(L"RcharAttack6.png");
	}
	if (charAttack7.IsNull())
	{
		charAttack7.Load(L"RcharAttack7.png");
	}
	if (AttackCardImg.IsNull())
	{
		AttackCardImg.Load(L"공격카드.png");
	}
	if (DeffenceCardImg.IsNull())
	{
		DeffenceCardImg.Load(L"방어카드.png");
	}
	
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
			charIdle1.Draw(hDC, player->x, 400, pw*2, ph*2, 0, 0, pw, ph);
			timer++;
			if (timer >= 10)
			{
				player->animation_num++;
			}
		}
			break;
		case 1:
		{
			int pw = charIdle1.GetWidth();
			int ph = charIdle1.GetHeight();
			charIdle1.Draw(hDC, player->x, 400 - 2, pw * 2, ph * 2 + 2, 0, 0, pw, ph);
			timer++;
			if (timer >= 20)
			{
				player->animation_num++;
			}
		}
			break;
		case 2: 
		{
			int pw = charIdle1.GetWidth();
			int ph = charIdle1.GetHeight();
			charIdle1.Draw(hDC, player->x, 400 - 4, pw * 2, ph * 2 + 4, 0, 0, pw, ph);
			timer++;
			if (timer >= 30)
			{
				player->animation_num++;
			} 
		}
			break;
		case 3:
		{
			int pw = charIdle1.GetWidth();
			int ph = charIdle1.GetHeight();
			charIdle1.Draw(hDC, player->x, 400 - 2, pw * 2, ph * 2 + 2, 0, 0, pw, ph);
			timer++;
			if (timer >= 40)
			{
				player->animation_num++;
			}
		}
			break;
		case 4:
		{
			int pw = charIdle1.GetWidth();
			int ph = charIdle1.GetHeight();
			charIdle1.Draw(hDC, player->x, 400, pw * 2, ph * 2, 0, 0, pw, ph);
			timer++; 
			if (timer >= 50)
			{
				player->animation_num = 0;
				timer = 0;
			}
		}
			break;
		default:
			break;
		}
	}
	else if (player->animation_state == State_Attack)
	{
		switch (player->animation_num)
		{
		case 0:
		{
			int pw = charIdle1.GetWidth();
			int ph = charIdle1.GetHeight();
			charIdle1.Draw(hDC, player->x, 550, pw, ph, 0, 0, pw, ph);
			timer++;
			if (timer >= 10)
			{
				player->animation_num++;
			}
		}
		break;
		case 1:
		{
			int pw = charAttack1.GetWidth();
			int ph = charAttack1.GetHeight();
			charAttack1.Draw(hDC, player->x, 550, pw, ph, 0, 0, pw, ph);
			timer++;
			if (timer >= 20)
			{
				player->animation_num++;
			}

		}
		break;
		case 2:
		{
			int pw = charAttack2.GetWidth();
			int ph = charAttack2.GetHeight();
			charAttack2.Draw(hDC, player->x, 550, pw, ph, 0, 0, pw, ph);
			timer++;
			if (timer >= 30)
			{
				player->animation_num++;
			}
		}
		break;
		case 3:
		{
			int pw = charAttack3.GetWidth();
			int ph = charAttack3.GetHeight();
			charAttack3.Draw(hDC, player->x, 550, pw, ph, 0, 0, pw, ph);
			timer++;
			if (timer >= 40)
			{
				player->animation_num++;
			}
		}
		case 4:
		{
			int pw = charAttack4.GetWidth();
			int ph = charAttack4.GetHeight();
			charAttack4.Draw(hDC, player->x, 550, pw, ph, 0, 0, pw, ph);
			timer++;
			if (timer >= 50)
			{
				player->animation_num++;
			}
		}
		case 5:
		{
			int pw = charAttack5.GetWidth();
			int ph = charAttack5.GetHeight();
			charAttack5.Draw(hDC, player->x, 550, pw, ph, 0, 0, pw, ph);
			timer++;
			if (timer >= 60)
			{
				player->animation_num++;
			}
		}
		case 6:
		{
			int pw = charAttack6.GetWidth();
			int ph = charAttack6.GetHeight();
			charAttack6.Draw(hDC, player->x, 550, pw, ph, 0, 0, pw, ph);
			timer++;
			if (timer >= 70)
			{
				player->animation_num++;
			}
		}
		case 7:
		{
			int pw = charAttack7.GetWidth();
			int ph = charAttack7.GetHeight();
			charAttack7.Draw(hDC, player->x, 550, pw, ph, 0, 0, pw, ph);
			timer++;
			if (timer >= 80)
			{
				player->animation_state = State_Idle;
				player->animation_num = 0;
			}
		}
		break;
		}
	}
	else if (player->animation_state == State_Deffence)
	{
		
	}
	else if (player->animation_state == State_Attacked)
	{

	}
}

static BOOL is_in_rect(int x, int y, RECT rect)
{
	if (x > rect.left && x<rect.right && y>rect.top && y < rect.bottom)
		return TRUE;
	else
		return FALSE;
}

void GP_LBUTTONDOWN(HWND hWnd, int x, int y, Player* player)
{

}

void AnimToXy(int x, int y)
{

}

void CheckState()
{

}


