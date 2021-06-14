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



static CImage slmIdle1, slmIdle2, slmIdle3, slmIdle4, slmIdle5, slmIdle6;
static CImage slmAttack1, slmAttack2, slmAttack3, slmAttack4, slmAttack5, slmAttack6;

static int frontCard = 0;
static BOOL isFront = FALSE;
static BOOL isCharMove = FALSE;
static int selected = -1;
static BOOL isSelected = FALSE;
static BOOL isCardMove = FALSE;
static BOOL isAtkSelected = FALSE;
static int MoveCard = 0;

static int AtkMonster = 0;

static Monster monster[3] = { 0 };
static int monsterCount = 0;

static int timer = 0;
static int monsterTimer[3] = { 0 };
static int CardTimer[50] = { 0 };

static POS arrow_pos = { 0 };
static POS arrow_endPos = { 0 };

static const COLORREF red = RGB(255, 0, 0);
static const COLORREF white = RGB(255, 255, 255);

static void SetImg();
void DrawPlayer(HDC hDC, Player* player);
void DrawCard(HDC hDC, Player* player);
void DrawMonster(HDC hDC);

void PlayerAttack(HWND hWnd, Player* player);
void PlayerDeffence(HWND hWnd, Player* player);
void TurnChange();
void SetCardPos(HWND hWnd, Player* player, int num);
int CalcDmg(Player* player);
int CalcDmg(Monster monster);

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
		if (player->isMyTurn)
		{
			DrawPlayer(hDC, player);
			DrawMonster(hDC);
		}
		else
		{
			DrawMonster(hDC);
			DrawPlayer(hDC, player);
		}
		DrawCard(hDC, player);

		if (isFront)
		{
			if (player->deck.card[frontCard].type == Card_Type_Attack)
			{
				int pw = AttackCardImg.GetWidth();
				int ph = AttackCardImg.GetHeight();
				AttackCardImg.Draw(hDC,player->deck.card[frontCard].left, player->deck.card[frontCard].top,
					player->deck.card[frontCard].right - player->deck.card[frontCard].left, player->deck.card[frontCard].bottom - player->deck.card[frontCard].top, 0, 0, pw, ph);

			}
			else if (player->deck.card[frontCard].type == Card_Type_Deffence)
			{
				int pw = DeffenceCardImg.GetWidth();
				int ph = DeffenceCardImg.GetHeight();
				DeffenceCardImg.Draw(hDC, player->deck.card[frontCard].left,player->deck.card[frontCard].top,
					player->deck.card[frontCard].right - player->deck.card[frontCard].left, player->deck.card[frontCard].bottom - player->deck.card[frontCard].top, 0, 0, pw, ph);
			}
		}

		if (isAtkSelected)
		{
			HPEN hPen, oldPen;
			RECT rect;
			BOOL isInRect = FALSE;
			int num = 0;

			for (int i = 0; i < 3; ++i)
			{
				rect.left = monster[i].x;
				rect.top = 550;
				rect.right = monster[i].x + 60;
				rect.bottom = 600;
				if (is_in_rect(arrow_endPos.x, arrow_endPos.y, rect))
				{
					isInRect = TRUE;
					num = i;
				}
			}

			if (isInRect)
			{
				hPen = CreatePen(PS_SOLID, 10, red);
			}
			else
			{
				hPen = CreatePen(PS_SOLID, 10, white);
			}

			oldPen = (HPEN)SelectObject(hDC, hPen);

			MoveToEx(hDC, arrow_pos.x, arrow_pos.y, NULL);
			LineTo(hDC, arrow_endPos.x, arrow_endPos.y);

			SelectObject(hDC, oldPen);
			DeleteObject(hPen);
		}
	}
	
}

void SetCard(Player* player)
{ // 임시로 막 넣었음.
	Card tmpCard;

	tmpCard.is_Active = TRUE;
	tmpCard.is_enhanced = FALSE;
	tmpCard.is_inhand = FALSE;
	tmpCard.is_Moving = FALSE;
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
	tmpCard.is_Moving = FALSE;
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
				CheckState();
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
			charIdle1.Draw(hDC, player->x, 350, pw * 2, ph * 2, 0, 0, pw, ph);
			timer++;
			if (timer >= 7)
			{
				player->animation_num++;
			}
		}
		break;
		case 1:
		{
			int pw = charAttack1.GetWidth();
			int ph = charAttack1.GetHeight();
			charAttack1.Draw(hDC, monster[AtkMonster].x - 250 , 350, pw * 2, ph * 2, 0, 0, pw, ph);
			timer++;
			if (timer >= 14)
			{
				player->animation_num++;
			}

		}
		break;
		case 2:
		{
			int pw = charAttack2.GetWidth();
			int ph = charAttack2.GetHeight();
			charAttack2.Draw(hDC, monster[AtkMonster].x - 250, 350, pw * 2, ph * 2, 0, 0, pw, ph);
			timer++;
			if (timer >= 21)
			{
				player->animation_num++;
			}
		}
		break;
		case 3:
		{
			int pw = charAttack3.GetWidth();
			int ph = charAttack3.GetHeight();
			charAttack3.Draw(hDC, monster[AtkMonster].x - 250 + (charAttack3.GetWidth() / 2), 350, pw * 2, ph * 2, 0, 0, pw, ph);
			timer++;
			if (timer >= 28)
			{
				player->animation_num++;
			}

		}
		break;
		case 4:
		{
			int pw = charAttack4.GetWidth();
			int ph = charAttack4.GetHeight();
			charAttack4.Draw(hDC, monster[AtkMonster].x - 250 + (charAttack4.GetWidth() / 2), 350, pw * 2, ph * 2, 0, 0, pw, ph);
			timer++;
			if (timer >= 35)
			{
				player->animation_num++;
			}
		}
		break;
		case 5:
		{
			int pw = charAttack5.GetWidth();
			int ph = charAttack5.GetHeight();
			charAttack5.Draw(hDC, monster[AtkMonster].x - 250 + (charAttack5.GetWidth() / 2), 350, pw * 2, ph * 2, 0, 0, pw, ph);
			timer++;
			if (timer >= 42)
			{
				player->animation_num++;
			}
		}
		break;
		case 6:
		{
			int pw = charAttack6.GetWidth();
			int ph = charAttack6.GetHeight();
			charAttack6.Draw(hDC, monster[AtkMonster].x - 250 + (charAttack6.GetWidth() / 2), 350, pw * 2, ph * 2, 0, 0, pw, ph);
			timer++;
			if (timer >= 49)
			{
				player->animation_num++;
			}
		}
		break;
		case 7:
		{
			int pw = charAttack7.GetWidth();
			int ph = charAttack7.GetHeight();
			charAttack7.Draw(hDC, monster[AtkMonster].x - 250, 350, pw * 2, ph * 2, 0, 0, pw, ph);
			timer++;
			if (timer >= 56)
			{
				player->animation_state = State_Idle;
				player->animation_num = 0;
				CheckState();
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
					AttackCardImg.Draw(hDC, player->deck.card[i].left, player->deck.card[i].top,
						player->deck.card[i].right - player->deck.card[i].left, player->deck.card[i].bottom - player->deck.card[i].top, 0, 0, pw, ph);
				}
				else if (player->deck.card[i].type == Card_Type_Deffence)
				{
					int pw = DeffenceCardImg.GetWidth();
					int ph = DeffenceCardImg.GetHeight();
					DeffenceCardImg.Draw(hDC, player->deck.card[i].left, player->deck.card[i].top,
						player->deck.card[i].right - player->deck.card[i].left, player->deck.card[i].bottom - player->deck.card[i].top, 0, 0, pw, ph);
				}
			}
		}
	}
}

static void DrawMonster(HDC hDC)
{
	for (int i = 0; i < monsterCount; ++i)
	{
		if (monster[i].type == Monster_Type_Basic)
		{
			switch (monster[i].ob_num)
			{
			case 0:
			{
				if (monster[i].animation_state == State_Idle)
				{
					switch (monster[i].animation_num)
					{
					case 0:
					{
						int mw = slmIdle1.GetWidth();
						int mh = slmIdle1.GetHeight();
						slmIdle1.Draw(hDC, monster[i].x - (mw / 2), 550, mw*2, mh*2, 0, 0, mw, mh);
						monsterTimer[i]++;
						if (monsterTimer[i] >= 5)
						{
							monster[i].animation_num++;
						}
					}
						break;
					case 1:
					{
						int mw = slmIdle2.GetWidth();
						int mh = slmIdle2.GetHeight();
						slmIdle2.Draw(hDC, monster[i].x - (mw / 2), 550, mw*2, mh*2, 0, 0, mw, mh);
						monsterTimer[i]++;
						if (monsterTimer[i] >= 10)
						{
							monster[i].animation_num++;
						}
					}
						break;
					case 2:
					{
						int mw = slmIdle3.GetWidth();
						int mh = slmIdle3.GetHeight();
						slmIdle3.Draw(hDC, monster[i].x - (mw / 2), 550, mw*2, mh*2, 0, 0, mw, mh);
						monsterTimer[i]++;
						if (monsterTimer[i] >= 15)
						{
							monster[i].animation_num++;
						}
					}
						break;
					case 3:
					{
						int mw = slmIdle4.GetWidth();
						int mh = slmIdle4.GetHeight();
						slmIdle3.Draw(hDC, monster[i].x - (mw / 2), 550, mw*2, mh*2, 0, 0, mw, mh);
						monsterTimer[i]++;
						if (monsterTimer[i] >= 20)
						{
							monster[i].animation_num++;
						}
					}
						break;
					case 4:
					{
						int mw = slmIdle5.GetWidth();
						int mh = slmIdle5.GetHeight();
						slmIdle5.Draw(hDC, monster[i].x - (mw / 2), 550, mw*2, mh*2, 0, 0, mw, mh);
						monsterTimer[i]++;
						if (monsterTimer[i] >= 25)
						{
							monster[i].animation_num++;
						}
					}
						break;
					case 5:
					{
						int mw = slmIdle6.GetWidth();
						int mh = slmIdle6.GetHeight();
						slmIdle6.Draw(hDC, monster[i].x - (mw / 2), 550, mw*2, mh*2, 0, 0, mw, mh);
						monsterTimer[i]++;
						if (monsterTimer[i] >= 30)
						{
							monster[i].animation_num = 0;
							monsterTimer[i] = 0;
						}
					}
						break;
					}
				}
				else if (monster[i].animation_state == State_Attack)
				{
					switch (monster[i].animation_num)
					{
					case 0:
					{
						int mw = slmAttack1.GetWidth();
						int mh = slmAttack1.GetHeight();
						slmAttack1.Draw(hDC, monster[i].x - (mw / 2), 350, mw*2, mh*2, 0, 0, mw, mh);
					}
						break;
					case 1:
					{
						int mw = slmAttack2.GetWidth();
						int mh = slmAttack2.GetHeight();
						slmAttack2.Draw(hDC, monster[i].x - (mw / 2), 350, mw*2, mh*2, 0, 0, mw, mh);
					}
						break;
					case 2:
					{
						int mw = slmAttack3.GetWidth();
						int mh = slmAttack3.GetHeight();
						slmAttack3.Draw(hDC, monster[i].x - (mw / 2), 350, mw * 2, mh * 2, 0, 0, mw, mh);
					}
						break;
					case 3:
					{
						int mw = slmAttack4.GetWidth();
						int mh = slmAttack4.GetHeight();
						slmAttack4.Draw(hDC, monster[i].x - (mw / 2), 350, mw * 2, mh * 2, 0, 0, mw, mh);
					}
						break;
					case 4:
					{
						int mw = slmAttack5.GetWidth();
						int mh = slmAttack5.GetHeight();
						slmAttack5.Draw(hDC, monster[i].x - (mw / 2), 350, mw * 2, mh * 2, 0, 0, mw, mh);
					}
						break;
					case 5:
					{
						int mw = slmAttack6.GetWidth();
						int mh = slmAttack6.GetHeight();
						slmAttack6.Draw(hDC, monster[i].x - (mw / 2), 350, mw * 2, mh * 2, 0, 0, mw, mh);
					}
						break;
					}
				}
			}
				break;
			default:
				break;
			}
		}
		else if (monster[i].type == Monster_Type_Elite)
		{
			switch (monster[i].ob_num)
			{
			case 0:
				break;
			default:
				break;
			}
		}
		else if (monster[i].type == Monster_Type_Boss)
		{
			switch (monster[i].ob_num)
			{
			case 0:
				break;
			default:
				break;
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

POS GP_LBUTTONDOWN(HWND hWnd, int x, int y, Player* player, int Lx, int Ly)
{

	if (!isCardMove && !isCharMove)
	{
		if (!(player->isDragCard))
		{
			if (player->deck.card[frontCard].type == Card_Type_Deffence)
			{
				POS pos = { x, y };
				pos.x = player->deck.card[frontCard].left + 100;
				pos.y = player->deck.card[frontCard].top + 130;
				player->isDragCard = TRUE;
				isSelected = TRUE;
				player->deck.card[frontCard].left = x - 100;
				player->deck.card[frontCard].right = x + 100;
				player->deck.card[frontCard].top = y - 130;
				player->deck.card[frontCard].bottom = y + 130;
				return pos;
			}
			else if (player->deck.card[frontCard].type == Card_Type_Attack)
			{
				isAtkSelected = TRUE;
				player->isDragCard = TRUE;
				isSelected = TRUE;
				arrow_pos = { x, y };
				arrow_endPos = { x, y };
			}
		}
		else
		{
			if (player->deck.card[frontCard].type == Card_Type_Deffence)
			{
				player->isDragCard = FALSE;
				isSelected = FALSE;
				CardTimer[frontCard] = 0;
				if (arrow_endPos.y <= 500)
				{
					PlayerDeffence(hWnd, player);
				}
				else
				{
					CardAnimToXy(hWnd, Lx, Ly, Card_Timer, &(player->deck.card[frontCard]), frontCard);
				}
			}
			else if (player->deck.card[frontCard].type == Card_Type_Attack)
			{
				isAtkSelected = FALSE;
				player->isDragCard = FALSE;
				isSelected = FALSE;
				
				RECT rect;
				BOOL isInRect = FALSE;
				int num = 0;

				for (int i = 0; i < 3; ++i)
				{
					rect.left = monster[i].x;
					rect.top = 550;
					rect.right = monster[i].x + 60;
					rect.bottom = 600;
					if (is_in_rect(arrow_endPos.x, arrow_endPos.y, rect))
					{
						isInRect = TRUE;
						AtkMonster = i;
						break;
					}
				}

				if (isInRect)
				{
					PlayerAttack(hWnd, player);
				}
			}
		}
	}
	POS* posp = GetPosPointer();
	return { posp->x, posp->y };
}

void GP_MOUSEMOVE(int x, int y, Player* player)
{
	if (!isCardMove && !isCharMove)
	{
		if (!(player->isDragCard))
		{
			if (!isFront)
			{
				for (int i = 0; player->deck.card[i].is_Active; ++i)
				{
					if (player->deck.card[i].is_inhand)
					{
						RECT rect;
						rect.left = player->deck.card[i].left;
						rect.right = player->deck.card[i].right;
						rect.top = player->deck.card[i].top;
						rect.bottom = player->deck.card[i].bottom;

						if (is_in_rect(x, y, rect))
						{
							frontCard = i;
							player->deck.card[i].top -= 100;
							player->deck.card[i].bottom -= 100;
							isFront = TRUE;
							break;
						}
					}
				}
			}
			else
			{
				RECT rect;
				rect.left = player->deck.card[frontCard].left;
				rect.right = player->deck.card[frontCard].right;
				rect.top = player->deck.card[frontCard].top;
				rect.bottom = player->deck.card[frontCard].bottom;
				if (!is_in_rect(x, y, rect))
				{
					if (!isCardMove)
					{
						isFront = FALSE;
						player->deck.card[frontCard].top += 100;
						player->deck.card[frontCard].bottom += 100;
					}
				}
			}
		}
		else
		{
			if (player->deck.card[frontCard].type == Card_Type_Deffence)
			{
				player->deck.card[frontCard].left = x - 100;
				player->deck.card[frontCard].right = x + 100;
				player->deck.card[frontCard].top = y - 130;
				player->deck.card[frontCard].bottom = y + 130;
			}
			else if (player->deck.card[frontCard].type == Card_Type_Attack)
			{
				arrow_endPos = { x, y };
			}
		}
	}

	arrow_endPos = { x, y };
}

void CardAnimToXy(HWND hWnd, int x, int y, int animNum, Card* card, int cardNum)
{
	if (card->is_inhand == TRUE)
	{
		if (CardTimer[cardNum] >= 40)
		{
			card->left = x - 100;
			card->right = x + 100;
			card->top = y - 130;
			card->bottom = y + 130;
			CardTimer[cardNum] = 0;
			KillTimer(hWnd, animNum);
			isCardMove = FALSE;
			card->is_Moving = FALSE;
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
			isCardMove = TRUE;
			card->is_Moving = TRUE;

			SetTimer(hWnd, animNum, 16, NULL);
		}
	}
}


void CardAnimToBigger(HWND hWnd, int left, int top, int right, int bottom, int animNum, Card* card, int cardNum)
{
	if (card->is_inhand == TRUE)
	{
		if (CardTimer[cardNum] >= 20)
		{
			card->left = left;
			card->right = right;
			card->top = top;
			card->bottom = bottom;
			CardTimer[cardNum] = 0;
			KillTimer(hWnd, animNum);
			isCardMove = FALSE;
		}
		else
		{
			CardTimer[cardNum]++;
			int leftBase = (left - card->left) / 2;
			int topBase = (top - card->top) / 2;
			int rightBase = (right - card->right) / 2;
			int bottomBase = (bottom - card->bottom) / 2;
			card->left = card->left + leftBase;
			card->right = card->right + right;
			card->top = card->top + top;
			card->bottom = card->bottom + bottom;
			isCardMove = TRUE;

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

void LoadSlime()
{
	if (slmIdle1.IsNull())
	{
		slmIdle1.Load(L"slime_idle1.png");
	}
	if (slmIdle2.IsNull())
	{
		slmIdle2.Load(L"slime_idle2.png");
	}
	if (slmIdle3.IsNull())
	{
		slmIdle3.Load(L"slime_idle3.png");
	}
	if (slmIdle4.IsNull())
	{
		slmIdle4.Load(L"slime_idle4.png");
	}
	if (slmIdle5.IsNull())
	{
		slmIdle5.Load(L"slime_idle5.png");
	}
	if (slmIdle6.IsNull())
	{
		slmIdle6.Load(L"slime_idle6.png");
	}
	if (slmAttack1.IsNull())
	{
		slmAttack1.Load(L"slime_attack1.png");
	}
	if (slmAttack2.IsNull())
	{
		slmAttack2.Load(L"slime_attack2.png");
	}
	if (slmAttack3.IsNull())
	{
		slmAttack3.Load(L"slime_attack3.png");
	}
	if (slmAttack4.IsNull())
	{
		slmAttack4.Load(L"slime_attack4.png");
	}
	if (slmAttack5.IsNull())
	{
		slmAttack5.Load(L"slime_attack5.png");
	}
	if (slmAttack6.IsNull())
	{
		slmAttack6.Load(L"slime_attack6.png");
	}
}

void SetMonster(int monsterNum)
{
	if (monsterNum == 0)
	{
		monster[0].x = 900;
		monster[0].stage_num = 1;
		monster[0].type = Monster_Type_Basic;
		int randNum = rand() % 3 + 10;
		monster[0].hp.Current_hp = randNum;
		monster[0].hp.Max_hp = randNum;
		monster[0].hp.Shield_figure = 0;
		monster[0].ob_num = 0;
		monster[0].maxDmg = 6;
		monster[0].minDmg = 4;
		monster[0].animation_num = 0;
		monster[0].animation_state = State_Idle;
		monster[0].is_Active = TRUE;

		monsterCount = 1;

		LoadSlime();
	}
	else if (monsterNum == 1)
	{
		monster[0].x = 850;
		monster[0].stage_num = 1;
		monster[0].type = Monster_Type_Basic;
		monster[0].ob_num = 0;
		int randNum = rand() % 3 + 10;
		monster[0].hp.Current_hp = randNum;
		monster[0].hp.Max_hp = randNum;
		monster[0].hp.Shield_figure = 0;
		monster[0].maxDmg = 6;
		monster[0].minDmg = 4;
		monster[0].is_Active = TRUE;
		monster[0].animation_num = 0;
		monster[0].animation_state = State_Idle;

		monster[1].x = 950;
		monster[1].stage_num = 1;
		monster[1].type = Monster_Type_Basic;
		monster[1].ob_num = 0;
		randNum = rand() % 3 + 10;
		monster[1].hp.Current_hp = randNum;
		monster[1].hp.Max_hp = randNum;
		monster[1].hp.Shield_figure = 0;
		monster[1].maxDmg = 6;
		monster[1].minDmg = 4;
		monster[1].is_Active = TRUE;
		monster[1].animation_num = 0;
		monster[1].animation_state = State_Idle;

		monsterCount = 2;

		LoadSlime();
	}
	else if (monsterNum == 2)
	{
		monster[0].x = 800;
		monster[0].stage_num = 1;
		monster[0].type = Monster_Type_Basic;
		monster[0].ob_num = 0;
		int randNum = rand() % 3 + 10;
		monster[0].hp.Current_hp = randNum;
		monster[0].hp.Max_hp = randNum;
		monster[0].hp.Shield_figure = 0;
		monster[0].maxDmg = 6;
		monster[0].minDmg = 4;
		monster[0].is_Active = TRUE;
		monster[0].animation_num = 0;
		monster[0].animation_state = State_Idle;

		monster[1].x = 900;
		monster[1].stage_num = 1;
		monster[1].type = Monster_Type_Basic;
		monster[1].ob_num = 0;
		randNum = rand() % 3 + 10;
		monster[1].hp.Current_hp = randNum;
		monster[1].hp.Max_hp = randNum;
		monster[1].hp.Shield_figure = 0;
		monster[1].maxDmg = 6;
		monster[1].minDmg = 4;
		monster[1].is_Active = TRUE;
		monster[1].animation_num = 0;
		monster[1].animation_state = State_Idle;

		monster[2].x = 1000;
		monster[2].stage_num = 1;
		monster[2].type = Monster_Type_Basic;
		monster[2].ob_num = 0;
		randNum = rand() % 3 + 10;
		monster[2].hp.Current_hp = randNum;
		monster[2].hp.Max_hp = randNum;
		monster[2].hp.Shield_figure = 0;
		monster[2].maxDmg = 6;
		monster[2].minDmg = 4;
		monster[2].is_Active = TRUE;
		monster[2].animation_num = 0;
		monster[2].animation_state = State_Idle;

		monsterCount = 3;

		LoadSlime();
	}
}

POS StartStage(HWND hWnd, Player* player, int monsterNum)
{
	SetCard(player);
	SetMonster(monsterNum);

	player->isMyTurn = TRUE;

	Shupple(player, 10);
	player->deck.card[0].is_inhand = TRUE;
	player->deck.card[1].is_inhand = TRUE;
	player->deck.card[2].is_inhand = TRUE;
	player->deck.card[3].is_inhand = TRUE;
	player->deck.card[4].is_inhand = TRUE;
	CardAnimToXy(hWnd, 300, 800, Card_Timer, &(player->deck.card[0]), 0);
	CardAnimToXy(hWnd, 450, 800, Card_Timer, &(player->deck.card[1]), 1);
	CardAnimToXy(hWnd, 600, 800, Card_Timer, &(player->deck.card[2]), 2);
	CardAnimToXy(hWnd, 750, 800, Card_Timer, &(player->deck.card[3]), 3);
	CardAnimToXy(hWnd, 900, 800, Card_Timer, &(player->deck.card[4]), 4);
	isCardMove = TRUE;
	POS pos = { 300, 800 };
	return pos;
}

void PlayerAttack(HWND hWnd, Player* player)
{
	player->deck.card[frontCard] = { 0 };
	int targetNum = frontCard;
	for (int i = 0; player->deck.card[targetNum + 1].is_Active && frontCard + 1 < MNCD; ++i)
	{
		Card tmp = player->deck.card[targetNum];
		player->deck.card[targetNum] = player->deck.card[targetNum + 1];
		player->deck.card[targetNum + 1] = tmp;
		targetNum++;
	}
	
	targetNum = 0;

	for (int i = 0; player->deck.card[i].is_inhand; ++i)
	{
		targetNum++;
	}

	SetCardPos(hWnd, player, targetNum);

	player->animation_state = State_Attack;
	player->animation_num = 0;
	timer = 0;

	monster[AtkMonster].hp.Current_hp -= CalcDmg(player);


	isFront = FALSE;
	isSelected = FALSE;

}

void PlayerDeffence(HWND hWnd, Player* player)
{
	player->deck.card[frontCard] = { 0 };
	int targetNum = frontCard;
	for (int i = 0; player->deck.card[targetNum + 1].is_Active && frontCard + 1 < MNCD; ++i)
	{
		Card tmp = player->deck.card[targetNum];
		player->deck.card[targetNum] = player->deck.card[targetNum + 1];
		player->deck.card[targetNum + 1] = tmp;
		targetNum++;
	}

	targetNum = 0;

	for (int i = 0; player->deck.card[i].is_inhand; ++i)
	{
		targetNum++;
	}

	SetCardPos(hWnd, player, targetNum);



	isFront = FALSE;
	isSelected = FALSE;

}

void SetCardPos(HWND hWnd, Player* player, int num)
{
	switch (num)
	{
	case 0:
	{
		TurnChange();
	}
	break;
	case 1:
	{
		CardAnimToXy(hWnd, 600, 800, Card_Timer, &(player->deck.card[0]), 0);
		isCardMove = TRUE;
		POS* posp = GetPosPointer();
		posp->x = 600;
		posp->y = 800;
	}
	break;
	case 2:
	{
		CardAnimToXy(hWnd, 525, 800, Card_Timer, &(player->deck.card[0]), 0);
		CardAnimToXy(hWnd, 675, 800, Card_Timer, &(player->deck.card[1]), 1);
		isCardMove = TRUE;
		POS* posp = GetPosPointer();
		posp->x = 525;
		posp->y = 800;
	}
	break;
	case 3:
	{
		CardAnimToXy(hWnd, 450, 800, Card_Timer, &(player->deck.card[0]), 0);
		CardAnimToXy(hWnd, 600, 800, Card_Timer, &(player->deck.card[1]), 1);
		CardAnimToXy(hWnd, 750, 800, Card_Timer, &(player->deck.card[2]), 2);
		isCardMove = TRUE;
		POS* posp = GetPosPointer();
		posp->x = 450;
		posp->y = 800;
	}
	break;
	case 4:
	{
		CardAnimToXy(hWnd, 375, 800, Card_Timer, &(player->deck.card[0]), 0);
		CardAnimToXy(hWnd, 525, 800, Card_Timer, &(player->deck.card[1]), 1);
		CardAnimToXy(hWnd, 675, 800, Card_Timer, &(player->deck.card[2]), 2);
		CardAnimToXy(hWnd, 825, 800, Card_Timer, &(player->deck.card[3]), 3);
		isCardMove = TRUE;
		POS* posp = GetPosPointer();
		posp->x = 375;
		posp->y = 800;
	}
	break;
	case 5:
	{
		CardAnimToXy(hWnd, 300, 800, Card_Timer, &(player->deck.card[0]), 0);
		CardAnimToXy(hWnd, 450, 800, Card_Timer, &(player->deck.card[1]), 1);
		CardAnimToXy(hWnd, 600, 800, Card_Timer, &(player->deck.card[2]), 2);
		CardAnimToXy(hWnd, 750, 800, Card_Timer, &(player->deck.card[3]), 3);
		CardAnimToXy(hWnd, 900, 800, Card_Timer, &(player->deck.card[4]), 4);
		isCardMove = TRUE;
		POS* posp = GetPosPointer();
		posp->x = 300;
		posp->y = 800;
	}
	break;
	case 6:
	{

	}
	break;
	case 7:
	{

	}
	break;
	case 8:
	{

	}
	break;
	case 9:
	{

	}
	break;
	case 10:
	{

	}
	break;
	}
}

int CalcDmg(Player* player)
{
	return 5;
}
int CalcDmg(Monster monster)
{
	return rand() % 3 + 4;
}

void TurnChange()
{

}
