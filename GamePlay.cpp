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
static int CardTimer[50] = { 0 };

static void SetImg();
void DrawPlayer(HDC hDC, Player* player);
void DrawCard(HDC hDC, Player* player);

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
		DrawCard(hDC, player);
	}
	
}

void SetCard(Player* player)
{ // 임시로 막 넣었음.
	Card tmpCard;

	tmpCard.is_Active = TRUE;
	tmpCard.is_enhanced = FALSE;
	tmpCard.is_inhand = FALSE;
	tmpCard.occupation = Card_Occu_ALL;
	tmpCard.type = Card_Type_Attack;
	tmpCard.number = 0;
	tmpCard.left = 900;
	tmpCard.right = 1100;
	tmpCard.top = 470;
	tmpCard.bottom = 730;

	player->deck.card[0] = tmpCard;
	player->deck.card[1] = tmpCard;
	player->deck.card[2] = tmpCard;
	player->deck.card[3] = tmpCard;
	player->deck.card[4] = tmpCard;

	tmpCard.is_Active = TRUE;
	tmpCard.is_enhanced = FALSE;
	tmpCard.is_inhand = FALSE;
	tmpCard.occupation = Card_Occu_ALL;
	tmpCard.type = Card_Type_Deffence;
	tmpCard.number = 0;
	tmpCard.left = 900;
	tmpCard.right = 1100;
	tmpCard.top = 470;
	tmpCard.bottom = 730;

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
			charIdle1.Draw(hDC, player->x, 350, pw*2, ph*2, 0, 0, pw, ph);
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
			charIdle1.Draw(hDC, player->x, 350 - 2, pw * 2, ph * 2 + 2, 0, 0, pw, ph);
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
			charIdle1.Draw(hDC, player->x, 350 - 4, pw * 2, ph * 2 + 4, 0, 0, pw, ph);
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
			charIdle1.Draw(hDC, player->x, 350 - 2, pw * 2, ph * 2 + 2, 0, 0, pw, ph);
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
			charIdle1.Draw(hDC, player->x, 350, pw * 2, ph * 2, 0, 0, pw, ph);
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
			charIdle1.Draw(hDC, player->x, 350, pw, ph, 0, 0, pw, ph);
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
			charAttack1.Draw(hDC, player->x, 350, pw, ph, 0, 0, pw, ph);
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
			charAttack2.Draw(hDC, player->x, 350, pw, ph, 0, 0, pw, ph);
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
			charAttack3.Draw(hDC, player->x, 350, pw, ph, 0, 0, pw, ph);
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
			charAttack4.Draw(hDC, player->x, 350, pw, ph, 0, 0, pw, ph);
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
			charAttack5.Draw(hDC, player->x, 350, pw, ph, 0, 0, pw, ph);
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
			charAttack6.Draw(hDC, player->x, 350, pw, ph, 0, 0, pw, ph);
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
			charAttack7.Draw(hDC, player->x, 350, pw, ph, 0, 0, pw, ph);
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

static void DrawCard(HDC hDC, Player* player)
{
	for (int i = 0; i < 50; ++i)
	{
		if (player->deck.card[i].is_Active)
		{
			if (player->deck.card[i].is_inhand)
			{
				if (player->deck.card[i].type == Card_Type_Attack)
				{
					int pw = AttackCardImg.GetWidth();
					int ph = AttackCardImg.GetHeight();
					AttackCardImg.Draw(hDC, (player->deck.card[i].right + player->deck.card[i].left) / 2, (player->deck.card[i].bottom + player->deck.card[i].top) / 2,
						player->deck.card[i].right - player->deck.card[i].left, player->deck.card[i].bottom - player->deck.card[i].top, 0, 0, pw, ph);
				}
				else if (player->deck.card[i].type == Card_Type_Deffence)
				{
					int pw = DeffenceCardImg.GetWidth();
					int ph = DeffenceCardImg.GetHeight();
					DeffenceCardImg.Draw(hDC, (player->deck.card[i].right + player->deck.card[i].left) / 2, (player->deck.card[i].bottom + player->deck.card[i].top) / 2,
						player->deck.card[i].right - player->deck.card[i].left, player->deck.card[i].bottom - player->deck.card[i].top, 0, 0, pw, ph);
				}
			}
		}
	}
}

static BOOL is_in_rect(int x, int y, RECT rect)
{
	if (x > rect.left && x<rect.right && y>rect.top && y < rect.bottom)
		return TRUE;
	else
		return FALSE;
}

POS GP_LBUTTONDOWN(HWND hWnd, int x, int y, Player* player)
{
	if (!isCardMove)
	{
		SetCard(player);
		player->deck.card[0].is_inhand = TRUE;
		player->deck.card[1].is_inhand = TRUE;
		player->deck.card[2].is_inhand = TRUE;
		player->deck.card[3].is_inhand = TRUE;
		player->deck.card[4].is_inhand = TRUE;
		CardAnimToXy(hWnd, 300, 650, Card_Timer, &(player->deck.card[0]), 0);
		CardAnimToXy(hWnd, 450, 650, Card_Timer, &(player->deck.card[1]), 1);
		CardAnimToXy(hWnd, 600, 650, Card_Timer, &(player->deck.card[2]), 2);
		CardAnimToXy(hWnd, 750, 650, Card_Timer, &(player->deck.card[3]), 3);
		CardAnimToXy(hWnd, 900, 650, Card_Timer, &(player->deck.card[4]), 4);
		POS pos = { 300, 650 };
		return pos;
	}


}

void CardAnimToXy(HWND hWnd, int x, int y, int animNum, Card* card, int cardNum)
{
	if (card->is_inhand == TRUE)
	{
		if (CardTimer[cardNum] >= 50)
		{
			card->left = x - 100;
			card->right = x + 100;
			card->top = y - 130;
			card->bottom = y + 130;
			CardTimer[cardNum] = 0;
			KillTimer(hWnd, animNum);
		}
		else
		{
			CardTimer[cardNum]++;
			int HoriBase = (card->left - (x - 100)) / 10;
			int VertBase = (card->top - (y - 130)) / 10;
			card->left = card->left - HoriBase;
			card->right = card->right - HoriBase;
			card->top = card->top - VertBase;
			card->bottom = card->bottom - VertBase;


			SetTimer(hWnd, animNum, 16, NULL);
		}
	}
}

void CheckState()
{

}

void Shupple(Player* player, int cardNum)
{
	if (cardNum >= 1)
	{
		for (int i = cardNum - 1; i > 2; --i)
		{
			int first = rand() % i;
			int last = rand() % ((i / 2) + (cardNum / 2)) ;

			Card tmp = player->deck.card[first];
			player->deck.card[first] = player->deck.card[last];
			player->deck.card[last] = tmp;
		}
	}
}

POS StartStage(HWND hWnd, Player* player)
{
	SetCard(player);


	Shupple(player, 10);
	player->deck.card[0].is_inhand = TRUE;
	player->deck.card[1].is_inhand = TRUE;
	player->deck.card[2].is_inhand = TRUE;
	player->deck.card[3].is_inhand = TRUE;
	player->deck.card[4].is_inhand = TRUE;
	CardAnimToXy(hWnd, 250, 650, Card_Timer, &(player->deck.card[0]), 0);
	CardAnimToXy(hWnd, 400, 650, Card_Timer, &(player->deck.card[1]), 1);
	CardAnimToXy(hWnd, 550, 650, Card_Timer, &(player->deck.card[2]), 2);
	CardAnimToXy(hWnd, 700, 650, Card_Timer, &(player->deck.card[3]), 3);
	CardAnimToXy(hWnd, 850, 650, Card_Timer, &(player->deck.card[4]), 4);
	POS pos = { 250, 650 };
	return pos;
}

