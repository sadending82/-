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
static CImage turnEnd, turnEnd_;
static CImage HPbar, HPred;
static CImage shield;

static int frontCard = 0;
static BOOL isFront = FALSE;
static BOOL isCharMove = FALSE;
static int selected = -1;
static BOOL isSelected = FALSE;
static BOOL isCardMove = FALSE;
static BOOL isAtkSelected = FALSE;
static BOOL isTurnChange = FALSE;
static BOOL isChangedTurn = FALSE;
static BOOL isMouseUpTurnEnd = FALSE;

static BOOL isMyTurnPrint = FALSE;
static BOOL isEnemyTurnPrint = FALSE;

static BOOL isEnemyDmgPrint = FALSE;
static BOOL isMyDmgPrint = FALSE;

static int MoveCard = 0;

static int AtkMonster = 0;

static int monsterAtkDmg = 0;
static int myAtkDmg = 0;

static Monster monster[3] = { 0 };
static int monsterCount = 0;

static int timer = 0;
static int monsterTimer[3] = { 0 };
static int CardTimer[50] = { 0 };
static int DmgTimer = 0;

static int TurnMonsterNum = 0;

static POS arrow_pos = { 0 };
static POS arrow_endPos = { 0 };

static const COLORREF red = RGB(255, 0, 0);
static const COLORREF white = RGB(255, 255, 255);

static void SetImg();
void DrawPlayer(HWND hWnd, HDC hDC, Player* player);
void DrawCard(HWND hWnd, HDC hDC, Player* player);
void DrawMonster(HWND hWnd, HDC hDC, Player* player);

void PlayerAttack(HWND hWnd, Player* player);
void PlayerDeffence(HWND hWnd, Player* player);
void TurnChange(HWND hWnd, Player* player);
void SetCardPos(HWND hWnd, Player* player, int num);
int CalcDmg(Player* player);
void CalcDmg(Player* player, Monster monster);
int CalcShield(Player* player);
void PlayerDefeat(HWND hWnd);
void PlayerWin(HWND hWnd);
void CheckState(HWND hWnd, Player* player);
void SetTurnChangeTimer(HWND hWnd);

void DisplayGame(HWND hWnd, HDC hDC, Player* player)
{
	/*이미지 설정*/
	SetImg();


	/*배경화면 그리기*/
	int bgw = bgImg.GetWidth();
	int bgh = bgImg.GetHeight();
	bgImg.Draw(hDC, 0, 0, WindowWidth, WindowHeight, 0, 0, bgw, bgh);

	/*캐릭터 그리기*/

	/*카드 설정(현재는 아무것도 없음)*/
	WCHAR str[20];
	wsprintf(str, L"코스트 : %d", player->cost);
	TextOut(hDC, 100, 400, str, lstrlen(str));

	if (isMyTurnPrint)
	{
		TextOut(hDC, 550, 100, L"당신의 차례입니다.", lstrlen(L"당신의 차례입니다."));
	}

	if (isEnemyTurnPrint)
	{
		TextOut(hDC, 550, 100, L"적의 차례입니다.", lstrlen(L"적의 차례입니다.")); 
	}

	if (player->isMyTurn)
	{
		if (isMouseUpTurnEnd)
		{
			int pw = turnEnd.GetWidth();
			int ph = turnEnd.GetHeight();
			turnEnd.Draw(hDC, 1050, 650, pw, ph, 0, 0, pw, ph);
		}
		else
		{
			int pw = turnEnd_.GetWidth();
			int ph = turnEnd_.GetHeight();
			turnEnd_.Draw(hDC, 1050, 650, pw, ph, 0, 0, pw, ph);
		}
	}

	if (player->isCharacterActive == TRUE)
	{
		if (player->isMyTurn)
		{
			DrawMonster(hWnd, hDC, player);
			DrawPlayer(hWnd, hDC, player);

		}
		else
		{
			DrawPlayer(hWnd, hDC, player);
			DrawMonster(hWnd, hDC, player);

		}
		DrawCard(hWnd, hDC, player);

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
	tmpCard.cost = 1;


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
	tmpCard.cost = 1;

	player->deck.card[5] = tmpCard;
	player->deck.card[6] = tmpCard;
	player->deck.card[7] = tmpCard;
	player->deck.card[8] = tmpCard;
	player->deck.card[9] = tmpCard;
	//직업 전용 카드 추가
	switch (player->occupation)
	{
	case 0:
		break;
	case 1:
		break;
	}

	int tmp = 0;

	for (int i = 0; i < MNCD; ++i)
	{
		if (player->deck.card[i].is_Active)
		{
			tmp++;
		}
	}

	player->deck.num_of_cards = tmp;
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
	if (turnEnd.IsNull())
	{
		turnEnd.Load(L"TurnEnd1.png");
	}
	if (turnEnd_.IsNull())
	{
		turnEnd_.Load(L"TurnEnd1_.png");
	}
	if (HPbar.IsNull())
	{
		HPbar.Load(L"HP_Bar_Empty.png");
	}
	if (HPred.IsNull())
	{
		HPred.Load(L"HP_Bar_HP.png");
	}
	if (shield.IsNull())
	{
		shield.Load(L"방패.png");
	}
	
}




void DrawPlayer(HWND hWnd, HDC hDC, Player* player)
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
			int hpw = HPbar.GetWidth();
			int hph = HPbar.GetHeight();
			HPbar.Draw(hDC, player->x + (pw / 2), 350 + (ph * 2), hpw, hph, 0, 0, hpw, hph);
			if (player->hp.Current_hp > 0)
			{
				float percent = hpw * (player->hp.Current_hp / (float)(player->hp.Max_hp));
				int intper = (int)percent;
				HPred.Draw(hDC, player->x + (pw / 2) - 1, 350 + (ph * 2) + 1, intper, hph, 0, 0, intper, hph);
			}
			HFONT hFont, oldFont;
			hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, L"궁서");
			oldFont = (HFONT)SelectObject(hDC, hFont);
			WCHAR str[20];
			wsprintf(str, L"%d / %d", player->hp.Current_hp, player->hp.Max_hp);
			SIZE size;
			GetTextExtentPoint(hDC, str, lstrlen(str), &size);
			TextOut(hDC, player->x + pw - (size.cx) + 7, 350 + (ph * 2), str, lstrlen(str));
			SelectObject(hDC, oldFont);
			DeleteObject(hFont);
			if (player->hp.Shield_figure > 0)
			{
				wsprintf(str, L"+     %d", player->hp.Shield_figure);
				TextOut(hDC, player->x + pw + 40, 350 + (ph * 2) + 1, str, lstrlen(str));
				int sw = shield.GetWidth();
				int sh = shield.GetHeight();
				shield.Draw(hDC, player->x + pw + 55, 350 + (ph * 2) - 5, sw, sh, 0, 0, sw, sh);
			}
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
			int hpw = HPbar.GetWidth();
			int hph = HPbar.GetHeight();
			HPbar.Draw(hDC, player->x + (pw / 2), 350 + (ph * 2), hpw, hph, 0, 0, hpw, hph);
			if (player->hp.Current_hp > 0)
			{
				float percent = hpw * (player->hp.Current_hp / (float)(player->hp.Max_hp));
				int intper = (int)percent;
				HPred.Draw(hDC, player->x + (pw / 2) - 1, 350 + (ph * 2) + 1, intper, hph, 0, 0, intper, hph);
			}
			HFONT hFont, oldFont;
			hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, L"궁서");
			oldFont = (HFONT)SelectObject(hDC, hFont);
			WCHAR str[20];
			wsprintf(str, L"%d / %d", player->hp.Current_hp, player->hp.Max_hp);
			SIZE size;
			GetTextExtentPoint(hDC, str, lstrlen(str), &size);
			TextOut(hDC, player->x + pw - (size.cx) + 7, 350 + (ph * 2), str, lstrlen(str));
			SelectObject(hDC, oldFont);
			DeleteObject(hFont);
			if (player->hp.Shield_figure > 0)
			{
				wsprintf(str, L"+     %d", player->hp.Shield_figure);
				TextOut(hDC, player->x + pw + 40, 350 + (ph * 2) + 1, str, lstrlen(str));
				int sw = shield.GetWidth();
				int sh = shield.GetHeight();
				shield.Draw(hDC, player->x + pw + 55, 350 + (ph * 2) - 5, sw, sh, 0, 0, sw, sh);
			}
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
			int hpw = HPbar.GetWidth();
			int hph = HPbar.GetHeight();
			HPbar.Draw(hDC, player->x + (pw / 2), 350 + (ph * 2), hpw, hph, 0, 0, hpw, hph);
			if (player->hp.Current_hp > 0)
			{
				float percent = hpw * (player->hp.Current_hp / (float)(player->hp.Max_hp));
				int intper = (int)percent;
				HPred.Draw(hDC, player->x + (pw / 2) - 1, 350 + (ph * 2) + 1, intper, hph, 0, 0, intper, hph);
			}
			HFONT hFont, oldFont;
			hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, L"궁서");
			oldFont = (HFONT)SelectObject(hDC, hFont);
			WCHAR str[20];
			wsprintf(str, L"%d / %d", player->hp.Current_hp, player->hp.Max_hp);
			SIZE size;
			GetTextExtentPoint(hDC, str, lstrlen(str), &size);
			TextOut(hDC, player->x + pw - (size.cx) + 7, 350 + (ph * 2), str, lstrlen(str));
			SelectObject(hDC, oldFont);
			DeleteObject(hFont);
			if (player->hp.Shield_figure > 0)
			{
				wsprintf(str, L"+     %d", player->hp.Shield_figure);
				TextOut(hDC, player->x + pw + 40, 350 + (ph * 2) + 1, str, lstrlen(str));
				int sw = shield.GetWidth();
				int sh = shield.GetHeight();
				shield.Draw(hDC, player->x + pw + 55, 350 + (ph * 2) - 5, sw, sh, 0, 0, sw, sh);
			}
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
			int hpw = HPbar.GetWidth();
			int hph = HPbar.GetHeight();
			HPbar.Draw(hDC, player->x + (pw / 2), 350 + (ph * 2), hpw, hph, 0, 0, hpw, hph);
			if (player->hp.Current_hp > 0)
			{
				float percent = hpw * (player->hp.Current_hp / (float)(player->hp.Max_hp));
				int intper = (int)percent;
				HPred.Draw(hDC, player->x + (pw / 2) - 1, 350 + (ph * 2) + 1, intper, hph, 0, 0, intper, hph);
			}
			HFONT hFont, oldFont;
			hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, L"궁서");
			oldFont = (HFONT)SelectObject(hDC, hFont);
			WCHAR str[20];
			wsprintf(str, L"%d / %d", player->hp.Current_hp, player->hp.Max_hp);
			SIZE size;
			GetTextExtentPoint(hDC, str, lstrlen(str), &size);
			TextOut(hDC, player->x + pw - (size.cx) + 7, 350 + (ph * 2), str, lstrlen(str));
			SelectObject(hDC, oldFont);
			DeleteObject(hFont);
			if (player->hp.Shield_figure > 0)
			{
				wsprintf(str, L"+     %d", player->hp.Shield_figure);
				TextOut(hDC, player->x + pw + 40, 350 + (ph * 2) + 1, str, lstrlen(str));
				int sw = shield.GetWidth();
				int sh = shield.GetHeight();
				shield.Draw(hDC, player->x + pw + 55, 350 + (ph * 2) - 5, sw, sh, 0, 0, sw, sh);
			}
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
			int hpw = HPbar.GetWidth();
			int hph = HPbar.GetHeight();
			HPbar.Draw(hDC, player->x + (pw / 2), 350 + (ph * 2), hpw, hph, 0, 0, hpw, hph);
			if (player->hp.Current_hp > 0)
			{
				float percent = hpw * (player->hp.Current_hp / (float)(player->hp.Max_hp));
				int intper = (int)percent;
				HPred.Draw(hDC, player->x + (pw / 2) - 1, 350 + (ph * 2) + 1, intper, hph, 0, 0, intper, hph);
			}
			HFONT hFont, oldFont;
			hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, L"궁서");
			oldFont = (HFONT)SelectObject(hDC, hFont);
			WCHAR str[20];
			wsprintf(str, L"%d / %d", player->hp.Current_hp, player->hp.Max_hp);
			SIZE size;
			GetTextExtentPoint(hDC, str, lstrlen(str), &size);
			TextOut(hDC, player->x + pw - (size.cx) + 7, 350 + (ph * 2), str, lstrlen(str));
			SelectObject(hDC, oldFont);
			DeleteObject(hFont);
			if (player->hp.Shield_figure > 0)
			{
				wsprintf(str, L"+     %d", player->hp.Shield_figure);
				TextOut(hDC, player->x + pw + 40, 350 + (ph * 2) + 1, str, lstrlen(str));
				int sw = shield.GetWidth();
				int sh = shield.GetHeight();
				shield.Draw(hDC, player->x + pw + 55, 350 + (ph * 2) - 5, sw, sh, 0, 0, sw, sh);
			}
			timer++; 
			if (timer >= 50)
			{
				player->animation_num = 0;
				timer = 0;
				if (isTurnChange)
				{
					isTurnChange = FALSE;
					SetTurnChangeTimer(hWnd);
				}
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
			int hpw = HPbar.GetWidth();
			int hph = HPbar.GetHeight();
			HPbar.Draw(hDC, player->x + (pw / 2), 350 + (ph * 2), hpw, hph, 0, 0, hpw, hph);
			if (player->hp.Current_hp > 0)
			{
				float percent = hpw * (player->hp.Current_hp / (float)(player->hp.Max_hp));
				int intper = (int)percent;
				HPred.Draw(hDC, player->x + (pw / 2) - 1, 350 + (ph * 2) + 1, intper, hph, 0, 0, intper, hph);
			}
			TextOut(hDC, 600, 200, L"공  격", 4);
			HFONT hFont, oldFont;
			hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, L"궁서");
			oldFont = (HFONT)SelectObject(hDC, hFont);
			WCHAR str[20];
			wsprintf(str, L"%d / %d", player->hp.Current_hp, player->hp.Max_hp);
			SIZE size;
			GetTextExtentPoint(hDC, str, lstrlen(str), &size);
			TextOut(hDC, player->x + pw - (size.cx) + 7, 350 + (ph * 2), str, lstrlen(str));
			SelectObject(hDC, oldFont);
			DeleteObject(hFont);
			if (player->hp.Shield_figure > 0)
			{
				wsprintf(str, L"+     %d", player->hp.Shield_figure);
				TextOut(hDC, player->x + pw + 40, 350 + (ph * 2) + 1, str, lstrlen(str));
				int sw = shield.GetWidth();
				int sh = shield.GetHeight();
				shield.Draw(hDC, player->x + pw + 55, 350 + (ph * 2) - 5, sw, sh, 0, 0, sw, sh);
			}
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
			TextOut(hDC, 600, 200, L"공  격", 4);
			int hpw = HPbar.GetWidth();
			int hph = HPbar.GetHeight();
			HPbar.Draw(hDC, player->x + (pw / 2), 350 + (ph * 2), hpw, hph, 0, 0, hpw, hph);
			if (player->hp.Current_hp > 0)
			{
				float percent = hpw * (player->hp.Current_hp / (float)(player->hp.Max_hp));
				int intper = (int)percent;
				HPred.Draw(hDC, player->x + (pw / 2) - 1, 350 + (ph * 2) + 1, intper, hph, 0, 0, intper, hph);
			}
			HFONT hFont, oldFont;
			hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, L"궁서");
			oldFont = (HFONT)SelectObject(hDC, hFont);
			WCHAR str[20];
			wsprintf(str, L"%d / %d", player->hp.Current_hp, player->hp.Max_hp);
			SIZE size;
			GetTextExtentPoint(hDC, str, lstrlen(str), &size);
			TextOut(hDC, player->x + pw - (size.cx) + 7, 350 + (ph * 2), str, lstrlen(str));
			SelectObject(hDC, oldFont);
			DeleteObject(hFont);
			if (player->hp.Shield_figure > 0)
			{
				wsprintf(str, L"+     %d", player->hp.Shield_figure);
				TextOut(hDC, player->x + pw + 40, 350 + (ph * 2) + 1, str, lstrlen(str));
				int sw = shield.GetWidth();
				int sh = shield.GetHeight();
				shield.Draw(hDC, player->x + pw + 55, 350 + (ph * 2) - 5, sw, sh, 0, 0, sw, sh);
			}
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
			TextOut(hDC, 600, 200, L"공  격", 4);
			int hpw = HPbar.GetWidth();
			int hph = HPbar.GetHeight();
			HPbar.Draw(hDC, player->x + (pw / 2), 350 + (ph * 2), hpw, hph, 0, 0, hpw, hph);
			if (player->hp.Current_hp > 0)
			{
				float percent = hpw * (player->hp.Current_hp / (float)(player->hp.Max_hp));
				int intper = (int)percent;
				HPred.Draw(hDC, player->x + (pw / 2) - 1, 350 + (ph * 2) + 1, intper, hph, 0, 0, intper, hph);
			}
			HFONT hFont, oldFont;
			hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, L"궁서");
			oldFont = (HFONT)SelectObject(hDC, hFont);
			WCHAR str[20];
			wsprintf(str, L"%d / %d", player->hp.Current_hp, player->hp.Max_hp);
			SIZE size;
			GetTextExtentPoint(hDC, str, lstrlen(str), &size);
			TextOut(hDC, player->x + pw - (size.cx) + 7, 350 + (ph * 2), str, lstrlen(str));
			SelectObject(hDC, oldFont);
			DeleteObject(hFont);
			if (player->hp.Shield_figure > 0)
			{
				wsprintf(str, L"+     %d", player->hp.Shield_figure);
				TextOut(hDC, player->x + pw + 40, 350 + (ph * 2) + 1, str, lstrlen(str));
				int sw = shield.GetWidth();
				int sh = shield.GetHeight();
				shield.Draw(hDC, player->x + pw + 55, 350 + (ph * 2) - 5, sw, sh, 0, 0, sw, sh);
			}
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
			TextOut(hDC, 600, 200, L"공  격", 4);
			int hpw = HPbar.GetWidth();
			int hph = HPbar.GetHeight();
			HPbar.Draw(hDC, player->x + (pw / 2), 350 + (ph * 2), hpw, hph, 0, 0, hpw, hph);
			if (player->hp.Current_hp > 0)
			{
				float percent = hpw * (player->hp.Current_hp / (float)(player->hp.Max_hp));
				int intper = (int)percent;
				HPred.Draw(hDC, player->x + (pw / 2) - 1, 350 + (ph * 2) + 1, intper, hph, 0, 0, intper, hph);
			}
			HFONT hFont, oldFont;
			hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, L"궁서");
			oldFont = (HFONT)SelectObject(hDC, hFont);
			WCHAR str[20];
			wsprintf(str, L"%d / %d", player->hp.Current_hp, player->hp.Max_hp);
			SIZE size;
			GetTextExtentPoint(hDC, str, lstrlen(str), &size);
			TextOut(hDC, player->x + pw - (size.cx) + 7, 350 + (ph * 2), str, lstrlen(str));
			SelectObject(hDC, oldFont);
			DeleteObject(hFont);
			if (player->hp.Shield_figure > 0)
			{
				wsprintf(str, L"+     %d", player->hp.Shield_figure);
				TextOut(hDC, player->x + pw + 40, 350 + (ph * 2) + 1, str, lstrlen(str));
				int sw = shield.GetWidth();
				int sh = shield.GetHeight();
				shield.Draw(hDC, player->x + pw + 55, 350 + (ph * 2) - 5, sw, sh, 0, 0, sw, sh);
			}
			timer++;
			if (timer >= 28)
			{
				player->animation_num++;

				monster[AtkMonster].hp.Current_hp -= CalcDmg(player);

				if (monster[AtkMonster].hp.Current_hp <= 0)
				{
					monster[AtkMonster].hp.Current_hp = 0;
				}

				monster[AtkMonster].animation_state = State_Attacked;
				monster[AtkMonster].animation_num = 0;
				monsterTimer[AtkMonster] = 0;
				DmgTimer = 0;
				SetMyDmgPrint(hWnd);
			}

		}
		break;
		case 4:
		{
			int pw = charAttack4.GetWidth();
			int ph = charAttack4.GetHeight();
			charAttack4.Draw(hDC, monster[AtkMonster].x - 250 + (charAttack4.GetWidth() / 2), 350, pw * 2, ph * 2, 0, 0, pw, ph);
			TextOut(hDC, 600, 200, L"공  격", 4);
			int hpw = HPbar.GetWidth();
			int hph = HPbar.GetHeight();
			HPbar.Draw(hDC, player->x + (pw / 2), 350 + (ph * 2), hpw, hph, 0, 0, hpw, hph);
			if (player->hp.Current_hp > 0)
			{
				float percent = hpw * (player->hp.Current_hp / (float)(player->hp.Max_hp));
				int intper = (int)percent;
				HPred.Draw(hDC, player->x + (pw / 2) - 1, 350 + (ph * 2) + 1, intper, hph, 0, 0, intper, hph);
			}
			HFONT hFont, oldFont;
			hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, L"궁서");
			oldFont = (HFONT)SelectObject(hDC, hFont);
			WCHAR str[20];
			wsprintf(str, L"%d / %d", player->hp.Current_hp, player->hp.Max_hp);
			SIZE size;
			GetTextExtentPoint(hDC, str, lstrlen(str), &size);
			TextOut(hDC, player->x + pw - (size.cx) + 7, 350 + (ph * 2), str, lstrlen(str));
			SelectObject(hDC, oldFont);
			DeleteObject(hFont);
			if (player->hp.Shield_figure > 0)
			{
				wsprintf(str, L"+     %d", player->hp.Shield_figure);
				TextOut(hDC, player->x + pw + 40, 350 + (ph * 2) + 1, str, lstrlen(str));
				int sw = shield.GetWidth();
				int sh = shield.GetHeight();
				shield.Draw(hDC, player->x + pw + 55, 350 + (ph * 2) - 5, sw, sh, 0, 0, sw, sh);
			}
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
			TextOut(hDC, 600, 200, L"공  격", 4);
			int hpw = HPbar.GetWidth();
			int hph = HPbar.GetHeight();
			HPbar.Draw(hDC, player->x + (pw / 2), 350 + (ph * 2), hpw, hph, 0, 0, hpw, hph);
			if (player->hp.Current_hp > 0)
			{
				float percent = hpw * (player->hp.Current_hp / (float)(player->hp.Max_hp));
				int intper = (int)percent;
				HPred.Draw(hDC, player->x + (pw / 2) - 1, 350 + (ph * 2) + 1, intper, hph, 0, 0, intper, hph);
			}
			HFONT hFont, oldFont;
			hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, L"궁서");
			oldFont = (HFONT)SelectObject(hDC, hFont);
			WCHAR str[20];
			wsprintf(str, L"%d / %d", player->hp.Current_hp, player->hp.Max_hp);
			SIZE size;
			GetTextExtentPoint(hDC, str, lstrlen(str), &size);
			TextOut(hDC, player->x + pw - (size.cx) + 7, 350 + (ph * 2), str, lstrlen(str));
			SelectObject(hDC, oldFont);
			DeleteObject(hFont);
			if (player->hp.Shield_figure > 0)
			{
				wsprintf(str, L"+     %d", player->hp.Shield_figure);
				TextOut(hDC, player->x + pw + 40, 350 + (ph * 2) + 1, str, lstrlen(str));
				int sw = shield.GetWidth();
				int sh = shield.GetHeight();
				shield.Draw(hDC, player->x + pw + 55, 350 + (ph * 2) - 5, sw, sh, 0, 0, sw, sh);
			}
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
			TextOut(hDC, 600, 200, L"공  격", 4);
			int hpw = HPbar.GetWidth();
			int hph = HPbar.GetHeight();
			HPbar.Draw(hDC, player->x + (pw / 2), 350 + (ph * 2), hpw, hph, 0, 0, hpw, hph);
			if (player->hp.Current_hp > 0)
			{
				float percent = hpw * (player->hp.Current_hp / (float)(player->hp.Max_hp));
				int intper = (int)percent;
				HPred.Draw(hDC, player->x + (pw / 2) - 1, 350 + (ph * 2) + 1, intper, hph, 0, 0, intper, hph);
			}
			HFONT hFont, oldFont;
			hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, L"궁서");
			oldFont = (HFONT)SelectObject(hDC, hFont);
			WCHAR str[20];
			wsprintf(str, L"%d / %d", player->hp.Current_hp, player->hp.Max_hp);
			SIZE size;
			GetTextExtentPoint(hDC, str, lstrlen(str), &size);
			TextOut(hDC, player->x + pw - (size.cx) + 7, 350 + (ph * 2), str, lstrlen(str));
			SelectObject(hDC, oldFont);
			DeleteObject(hFont);
			if (player->hp.Shield_figure > 0)
			{
				wsprintf(str, L"+     %d", player->hp.Shield_figure);
				TextOut(hDC, player->x + pw + 40, 350 + (ph * 2) + 1, str, lstrlen(str));
				int sw = shield.GetWidth();
				int sh = shield.GetHeight();
				shield.Draw(hDC, player->x + pw + 55, 350 + (ph * 2) - 5, sw, sh, 0, 0, sw, sh);
			}
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
			TextOut(hDC, 600, 200, L"공  격", 4);
			int hpw = HPbar.GetWidth();
			int hph = HPbar.GetHeight();
			HPbar.Draw(hDC, player->x + (pw / 2), 350 + (ph * 2), hpw, hph, 0, 0, hpw, hph);
			if (player->hp.Current_hp > 0)
			{
				float percent = hpw * (player->hp.Current_hp / (float)(player->hp.Max_hp));
				int intper = (int)percent;
				HPred.Draw(hDC, player->x + (pw / 2) - 1, 350 + (ph * 2) + 1, intper, hph, 0, 0, intper, hph);
			}
			HFONT hFont, oldFont;
			hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, L"궁서");
			oldFont = (HFONT)SelectObject(hDC, hFont);
			WCHAR str[20];
			wsprintf(str, L"%d / %d", player->hp.Current_hp, player->hp.Max_hp);
			SIZE size;
			GetTextExtentPoint(hDC, str, lstrlen(str), &size);
			TextOut(hDC, player->x + pw - (size.cx) + 7, 350 + (ph * 2), str, lstrlen(str));
			SelectObject(hDC, oldFont);
			DeleteObject(hFont);
			if (player->hp.Shield_figure > 0)
			{
				wsprintf(str, L"+     %d", player->hp.Shield_figure);
				TextOut(hDC, player->x + pw + 40, 350 + (ph * 2) + 1, str, lstrlen(str));
				int sw = shield.GetWidth();
				int sh = shield.GetHeight();
				shield.Draw(hDC, player->x + pw + 55, 350 + (ph * 2) - 5, sw, sh, 0, 0, sw, sh);
			}
			timer++;
			if (timer >= 56)
			{
				player->animation_state = State_Idle;
				player->animation_num = 0;
				isCharMove = FALSE;
				if (isTurnChange)
				{
					isTurnChange = FALSE;
					SetTurnChangeTimer(hWnd);
				}
				CheckState(hWnd, player);
			}


		}
		break;
		}
	}
	else if (player->animation_state == State_Deffence)
	{
		int pw = charIdle1.GetWidth();
		int ph = charIdle1.GetHeight();
		charIdle1.Draw(hDC, player->x, 350, pw * 2, ph * 2, 0, 0, pw, ph);
		TextOut(hDC, 600, 200, L"방  어", 4);
		int hpw = HPbar.GetWidth();
		int hph = HPbar.GetHeight();
		HPbar.Draw(hDC, player->x + (pw / 2), 350 + (ph * 2), hpw, hph, 0, 0, hpw, hph);
		if (player->hp.Current_hp > 0)
		{
			float percent = hpw * (player->hp.Current_hp / (float)(player->hp.Max_hp));
			int intper = (int)percent;
			HPred.Draw(hDC, player->x + (pw / 2) - 1, 350 + (ph * 2) + 1, intper, hph, 0, 0, intper, hph);
		}
		HFONT hFont, oldFont;
		hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, L"궁서");
		oldFont = (HFONT)SelectObject(hDC, hFont);
		WCHAR str[20];
		wsprintf(str, L"%d / %d", player->hp.Current_hp, player->hp.Max_hp);
		SIZE size;
		GetTextExtentPoint(hDC, str, lstrlen(str), &size);
		TextOut(hDC, player->x + pw - (size.cx) + 7, 350 + (ph * 2), str, lstrlen(str));
		SelectObject(hDC, oldFont);
		DeleteObject(hFont);
		if (player->hp.Shield_figure > 0)
		{
			wsprintf(str, L"+     %d", player->hp.Shield_figure);
			TextOut(hDC, player->x + pw + 40, 350 + (ph * 2) + 1, str, lstrlen(str));
			int sw = shield.GetWidth();
			int sh = shield.GetHeight();
			shield.Draw(hDC, player->x + pw + 55, 350 + (ph * 2) - 5, sw, sh, 0, 0, sw, sh);
		}
		timer++;
		if (timer >= 56)
		{
			player->animation_state = State_Idle;
			player->animation_num = 0;
			isCharMove = FALSE;
			if (isTurnChange)
			{
				isTurnChange = FALSE;
				SetTurnChangeTimer(hWnd);
			}
			CheckState(hWnd, player);

		}
	}
	else if (player->animation_state == State_Attacked)
	{
		switch (player->animation_num)
		{
		case 0:
		{
			int pw = charIdle1.GetWidth();
			int ph = charIdle1.GetHeight();
			charIdle1.Draw(hDC, player->x - 30, 350, pw * 2, ph * 2, 0, 0, pw, ph);
			int hpw = HPbar.GetWidth();
			int hph = HPbar.GetHeight();
			HPbar.Draw(hDC, player->x + (pw / 2), 350 + (ph * 2), hpw, hph, 0, 0, hpw, hph);
			if (player->hp.Current_hp > 0)
			{
				float percent = hpw * (player->hp.Current_hp / (float)(player->hp.Max_hp));
				int intper = (int)percent;
				HPred.Draw(hDC, player->x + (pw / 2) - 1, 350 + (ph * 2) + 1, intper, hph, 0, 0, intper, hph);
			}
			HFONT hFont, oldFont;
			hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, L"궁서");
			oldFont = (HFONT)SelectObject(hDC, hFont);
			WCHAR str[20];
			wsprintf(str, L"%d / %d", player->hp.Current_hp, player->hp.Max_hp);
			SIZE size;
			GetTextExtentPoint(hDC, str, lstrlen(str), &size);
			TextOut(hDC, player->x + pw - (size.cx) + 7, 350 + (ph * 2), str, lstrlen(str));
			SelectObject(hDC, oldFont);
			DeleteObject(hFont);
			if (player->hp.Shield_figure > 0)
			{
				wsprintf(str, L"+     %d", player->hp.Shield_figure);
				TextOut(hDC, player->x + pw + 40, 350 + (ph * 2) + 1, str, lstrlen(str));
				int sw = shield.GetWidth();
				int sh = shield.GetHeight();
				shield.Draw(hDC, player->x + pw + 55, 350 + (ph * 2) - 5, sw, sh, 0, 0, sw, sh);
			}
			timer++;
			if (timer >= 5)
			{
				player->animation_num++;
			}
		}
			break;
		case 1:
		{
			int pw = charIdle1.GetWidth();
			int ph = charIdle1.GetHeight();
			charIdle1.Draw(hDC, player->x - 20, 350, pw * 2, ph * 2, 0, 0, pw, ph);
			int hpw = HPbar.GetWidth();
			int hph = HPbar.GetHeight();
			HPbar.Draw(hDC, player->x + (pw / 2), 350 + (ph * 2), hpw, hph, 0, 0, hpw, hph);
			if (player->hp.Current_hp > 0)
			{
				float percent = hpw * (player->hp.Current_hp / (float)(player->hp.Max_hp));
				int intper = (int)percent;
				HPred.Draw(hDC, player->x + (pw / 2) - 1, 350 + (ph * 2) + 1, intper, hph, 0, 0, intper, hph);
			}
			HFONT hFont, oldFont;
			hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, L"궁서");
			oldFont = (HFONT)SelectObject(hDC, hFont);
			WCHAR str[20];
			wsprintf(str, L"%d / %d", player->hp.Current_hp, player->hp.Max_hp);
			SIZE size;
			GetTextExtentPoint(hDC, str, lstrlen(str), &size);
			TextOut(hDC, player->x + pw - (size.cx) + 7, 350 + (ph * 2), str, lstrlen(str));
			SelectObject(hDC, oldFont);
			DeleteObject(hFont);
			if (player->hp.Shield_figure > 0)
			{
				wsprintf(str, L"+     %d", player->hp.Shield_figure);
				TextOut(hDC, player->x + pw + 40, 350 + (ph * 2) + 1, str, lstrlen(str));
				int sw = shield.GetWidth();
				int sh = shield.GetHeight();
				shield.Draw(hDC, player->x + pw + 55, 350 + (ph * 2) - 5, sw, sh, 0, 0, sw, sh);
			}
			timer++;
			if (timer >= 15)
			{
				player->animation_num++;
			}
		}
			break;
		case 2:
		{
			int pw = charIdle1.GetWidth();
			int ph = charIdle1.GetHeight();
			charIdle1.Draw(hDC, player->x - 10, 350, pw * 2, ph * 2, 0, 0, pw, ph);
			int hpw = HPbar.GetWidth();
			int hph = HPbar.GetHeight();
			HPbar.Draw(hDC, player->x + (pw / 2), 350 + (ph * 2), hpw, hph, 0, 0, hpw, hph);
			if (player->hp.Current_hp > 0)
			{
				float percent = hpw * (player->hp.Current_hp / (float)(player->hp.Max_hp));
				int intper = (int)percent;
				HPred.Draw(hDC, player->x + (pw / 2) - 1, 350 + (ph * 2) + 1, intper, hph, 0, 0, intper, hph);
			}
			HFONT hFont, oldFont;
			hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, L"궁서");
			oldFont = (HFONT)SelectObject(hDC, hFont);
			WCHAR str[20];
			wsprintf(str, L"%d / %d", player->hp.Current_hp, player->hp.Max_hp);
			SIZE size;
			GetTextExtentPoint(hDC, str, lstrlen(str), &size);
			TextOut(hDC, player->x + pw - (size.cx) + 7, 350 + (ph * 2), str, lstrlen(str));
			SelectObject(hDC, oldFont);
			DeleteObject(hFont);
			if (player->hp.Shield_figure > 0)
			{
				wsprintf(str, L"+     %d", player->hp.Shield_figure);
				TextOut(hDC, player->x + pw + 40, 350 + (ph * 2) + 1, str, lstrlen(str));
				int sw = shield.GetWidth();
				int sh = shield.GetHeight();
				shield.Draw(hDC, player->x + pw + 55, 350 + (ph * 2) - 5, sw, sh, 0, 0, sw, sh);
			}
			timer++;
			if (timer >= 25)
			{
				player->animation_num++;
			}
		}
			break;
		case 3:
		{
			int pw = charIdle1.GetWidth();
			int ph = charIdle1.GetHeight();
			charIdle1.Draw(hDC, player->x, 350, pw * 2, ph * 2, 0, 0, pw, ph);
			int hpw = HPbar.GetWidth();
			int hph = HPbar.GetHeight();
			HPbar.Draw(hDC, player->x + (pw / 2), 350 + (ph * 2), hpw, hph, 0, 0, hpw, hph);
			if (player->hp.Current_hp > 0)
			{
				float percent = hpw * (player->hp.Current_hp / (float)(player->hp.Max_hp));
				int intper = (int)percent;
				HPred.Draw(hDC, player->x + (pw / 2) - 1, 350 + (ph * 2) + 1, intper, hph, 0, 0, intper, hph);
			}
			HFONT hFont, oldFont;
			hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, L"궁서");
			oldFont = (HFONT)SelectObject(hDC, hFont);
			WCHAR str[20];
			wsprintf(str, L"%d / %d", player->hp.Current_hp, player->hp.Max_hp);
			SIZE size;
			GetTextExtentPoint(hDC, str, lstrlen(str), &size);
			TextOut(hDC, player->x + pw - (size.cx) + 7, 350 + (ph * 2), str, lstrlen(str));
			SelectObject(hDC, oldFont);
			DeleteObject(hFont);
			if (player->hp.Shield_figure > 0)
			{
				wsprintf(str, L"+     %d", player->hp.Shield_figure);
				TextOut(hDC, player->x + pw + 40, 350 + (ph * 2) + 1, str, lstrlen(str));
				int sw = shield.GetWidth();
				int sh = shield.GetHeight();
				shield.Draw(hDC, player->x + pw + 55, 350 + (ph * 2) - 5, sw, sh, 0, 0, sw, sh);
			}
			timer++;
			if (timer >= 35)
			{
				player->animation_num = 0;
				player->animation_state = State_Idle;
				timer = 0;
			}
		}
			break;
		}
	}

	if (isEnemyDmgPrint)
	{
		DmgTimer++;
		WCHAR tstr[20] = { 0 };
		int pw = charIdle1.GetWidth();
		int ph = charIdle1.GetHeight();
		wsprintf(tstr, L"%d", monsterAtkDmg);
		TextOut(hDC, player->x + 100, 350 - DmgTimer, tstr, lstrlen(tstr));
	}
}

static void DrawCard(HWND hWnd, HDC hDC, Player* player)
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

static void DrawMonster(HWND hWnd, HDC hDC, Player* player)
{
	for (int i = 0; i < monsterCount; ++i)
	{
		if (monster[i].is_Active)
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
							slmIdle1.Draw(hDC, monster[i].x - (mw / 2), 550, mw * 2, mh * 2, 0, 0, mw, mh);
							int hpw = HPbar.GetWidth();
							int hph = HPbar.GetHeight();
							HPbar.Draw(hDC, monster[i].x - (mw / 2), 550 + (mh * 2), hpw, hph, 0, 0, hpw, hph);
							if (monster[i].hp.Current_hp > 0)
							{
								float percent = hpw * (monster[i].hp.Current_hp / (float)(monster[i].hp.Max_hp));
								int intper = (int)percent;
								HPred.Draw(hDC, monster[i].x - (mw / 2) - 1, 550 + (mh * 2) + 1, intper, hph, 0, 0, intper, hph);
							}
							HFONT hFont, oldFont;
							hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, L"궁서");
							oldFont = (HFONT)SelectObject(hDC, hFont);
							WCHAR str[20];
							wsprintf(str, L"%d / %d", monster[i].hp.Current_hp, monster[i].hp.Max_hp);
							SIZE size;
							GetTextExtentPoint(hDC, str, lstrlen(str), &size);
							TextOut(hDC, monster[i].x - (mw / 2) + (size.cx / 2) + 7, 550 + (mh * 2), str, lstrlen(str));
							SelectObject(hDC, oldFont);
							DeleteObject(hFont);
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
							slmIdle2.Draw(hDC, monster[i].x - (mw / 2), 550, mw * 2, mh * 2, 0, 0, mw, mh);
							int hpw = HPbar.GetWidth();
							int hph = HPbar.GetHeight();
							HPbar.Draw(hDC, monster[i].x - (mw / 2), 550 + (mh * 2), hpw, hph, 0, 0, hpw, hph);
							if (monster[i].hp.Current_hp > 0)
							{
								float percent = hpw * (monster[i].hp.Current_hp / (float)(monster[i].hp.Max_hp));
								int intper = (int)percent;
								HPred.Draw(hDC, monster[i].x - (mw / 2) - 1, 550 + (mh * 2) + 1, intper, hph, 0, 0, intper, hph);
							}
							HFONT hFont, oldFont;
							hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, L"궁서");
							oldFont = (HFONT)SelectObject(hDC, hFont);
							WCHAR str[20];
							wsprintf(str, L"%d / %d", monster[i].hp.Current_hp, monster[i].hp.Max_hp);
							SIZE size;
							GetTextExtentPoint(hDC, str, lstrlen(str), &size);
							TextOut(hDC, monster[i].x - (mw / 2) + (size.cx / 2) + 7, 550 + (mh * 2), str, lstrlen(str));
							SelectObject(hDC, oldFont);
							DeleteObject(hFont);
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
							slmIdle3.Draw(hDC, monster[i].x - (mw / 2), 550, mw * 2, mh * 2, 0, 0, mw, mh);
							int hpw = HPbar.GetWidth();
							int hph = HPbar.GetHeight();
							HPbar.Draw(hDC, monster[i].x - (mw / 2), 550 + (mh * 2), hpw, hph, 0, 0, hpw, hph);
							if (monster[i].hp.Current_hp > 0)
							{
								float percent = hpw * (monster[i].hp.Current_hp / (float)(monster[i].hp.Max_hp));
								int intper = (int)percent;
								HPred.Draw(hDC, monster[i].x - (mw / 2) - 1, 550 + (mh * 2) + 1, intper, hph, 0, 0, intper, hph);
							}
							HFONT hFont, oldFont;
							hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, L"궁서");
							oldFont = (HFONT)SelectObject(hDC, hFont);
							WCHAR str[20];
							wsprintf(str, L"%d / %d", monster[i].hp.Current_hp, monster[i].hp.Max_hp);
							SIZE size;
							GetTextExtentPoint(hDC, str, lstrlen(str), &size);
							TextOut(hDC, monster[i].x - (mw / 2) + (size.cx / 2) + 7, 550 + (mh * 2), str, lstrlen(str));
							SelectObject(hDC, oldFont);
							DeleteObject(hFont);
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
							slmIdle3.Draw(hDC, monster[i].x - (mw / 2), 550, mw * 2, mh * 2, 0, 0, mw, mh);
							int hpw = HPbar.GetWidth();
							int hph = HPbar.GetHeight();
							HPbar.Draw(hDC, monster[i].x - (mw / 2), 550 + (mh * 2), hpw, hph, 0, 0, hpw, hph);
							if (monster[i].hp.Current_hp > 0)
							{
								float percent = hpw * (monster[i].hp.Current_hp / (float)(monster[i].hp.Max_hp));
								int intper = (int)percent;
								HPred.Draw(hDC, monster[i].x - (mw / 2) - 1, 550 + (mh * 2) + 1, intper, hph, 0, 0, intper, hph);
							}
							HFONT hFont, oldFont;
							hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, L"궁서");
							oldFont = (HFONT)SelectObject(hDC, hFont);
							WCHAR str[20];
							wsprintf(str, L"%d / %d", monster[i].hp.Current_hp, monster[i].hp.Max_hp);
							SIZE size;
							GetTextExtentPoint(hDC, str, lstrlen(str), &size);
							TextOut(hDC, monster[i].x - (mw / 2) + (size.cx / 2) + 7, 550 + (mh * 2), str, lstrlen(str));
							SelectObject(hDC, oldFont);
							DeleteObject(hFont);
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
							slmIdle5.Draw(hDC, monster[i].x - (mw / 2), 550, mw * 2, mh * 2, 0, 0, mw, mh);
							int hpw = HPbar.GetWidth();
							int hph = HPbar.GetHeight();
							HPbar.Draw(hDC, monster[i].x - (mw / 2), 550 + (mh * 2), hpw, hph, 0, 0, hpw, hph);
							if (monster[i].hp.Current_hp > 0)
							{
								float percent = hpw * (monster[i].hp.Current_hp / (float)(monster[i].hp.Max_hp));
								int intper = (int)percent;
								HPred.Draw(hDC, monster[i].x - (mw / 2) - 1, 550 + (mh * 2) + 1, intper, hph, 0, 0, intper, hph);
							}
							HFONT hFont, oldFont;
							hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, L"궁서");
							oldFont = (HFONT)SelectObject(hDC, hFont);
							WCHAR str[20];
							wsprintf(str, L"%d / %d", monster[i].hp.Current_hp, monster[i].hp.Max_hp);
							SIZE size;
							GetTextExtentPoint(hDC, str, lstrlen(str), &size);
							TextOut(hDC, monster[i].x - (mw / 2) + (size.cx / 2) + 7, 550 + (mh * 2), str, lstrlen(str));
							SelectObject(hDC, oldFont);
							DeleteObject(hFont);
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
							slmIdle6.Draw(hDC, monster[i].x - (mw / 2), 550, mw * 2, mh * 2, 0, 0, mw, mh);
							int hpw = HPbar.GetWidth();
							int hph = HPbar.GetHeight();
							HPbar.Draw(hDC, monster[i].x - (mw / 2), 550 + (mh * 2), hpw, hph, 0, 0, hpw, hph);
							if (monster[i].hp.Current_hp > 0)
							{
								float percent = hpw * (monster[i].hp.Current_hp / (float)(monster[i].hp.Max_hp));
								int intper = (int)percent;
								HPred.Draw(hDC, monster[i].x - (mw / 2) - 1, 550 + (mh * 2) + 1, intper, hph, 0, 0, intper, hph);
							}
							HFONT hFont, oldFont;
							hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, L"궁서");
							oldFont = (HFONT)SelectObject(hDC, hFont);
							WCHAR str[20];
							wsprintf(str, L"%d / %d", monster[i].hp.Current_hp, monster[i].hp.Max_hp);
							SIZE size;
							GetTextExtentPoint(hDC, str, lstrlen(str), &size);
							TextOut(hDC, monster[i].x - (mw / 2) + (size.cx / 2) + 7, 550 + (mh * 2), str, lstrlen(str));
							SelectObject(hDC, oldFont);
							DeleteObject(hFont);
							monsterTimer[i]++;
							if (monsterTimer[i] >= 30)
							{
								monster[i].animation_num = 0;
								monsterTimer[i] = 0;
							}
							if (i == TurnMonsterNum && isChangedTurn)
							{
								SetTurnChangeTimer(hWnd);

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
							int mw = slmIdle1.GetWidth();
							int mh = slmIdle1.GetHeight();
							slmIdle1.Draw(hDC, monster[i].x - (mw / 2) + 10, 550, mw * 2, mh * 2, 0, 0, mw, mh);
							int hpw = HPbar.GetWidth();
							int hph = HPbar.GetHeight();
							HPbar.Draw(hDC, monster[i].x - (mw / 2), 550 + (mh * 2), hpw, hph, 0, 0, hpw, hph);
							if (monster[i].hp.Current_hp > 0)
							{
								float percent = hpw * (monster[i].hp.Current_hp / (float)(monster[i].hp.Max_hp));
								int intper = (int)percent;
								HPred.Draw(hDC, monster[i].x - (mw / 2) - 1, 550 + (mh * 2) + 1, intper, hph, 0, 0, intper, hph);
							}
							HFONT hFont, oldFont;
							hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, L"궁서");
							oldFont = (HFONT)SelectObject(hDC, hFont);
							WCHAR str[20];
							wsprintf(str, L"%d / %d", monster[i].hp.Current_hp, monster[i].hp.Max_hp);
							SIZE size;
							GetTextExtentPoint(hDC, str, lstrlen(str), &size);
							TextOut(hDC, monster[i].x - (mw / 2) + (size.cx / 2) + 7, 550 + (mh * 2), str, lstrlen(str));
							SelectObject(hDC, oldFont);
							DeleteObject(hFont);
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
							slmIdle2.Draw(hDC, monster[i].x - (mw / 2) + 10, 550, mw * 2, mh * 2, 0, 0, mw, mh);
							int hpw = HPbar.GetWidth();
							int hph = HPbar.GetHeight();
							HPbar.Draw(hDC, monster[i].x - (mw / 2), 550 + (mh * 2), hpw, hph, 0, 0, hpw, hph);
							if (monster[i].hp.Current_hp > 0)
							{
								float percent = hpw * (monster[i].hp.Current_hp / (float)(monster[i].hp.Max_hp));
								int intper = (int)percent;
								HPred.Draw(hDC, monster[i].x - (mw / 2) - 1, 550 + (mh * 2) + 1, intper, hph, 0, 0, intper, hph);
							}
							HFONT hFont, oldFont;
							hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, L"궁서");
							oldFont = (HFONT)SelectObject(hDC, hFont);
							WCHAR str[20];
							wsprintf(str, L"%d / %d", monster[i].hp.Current_hp, monster[i].hp.Max_hp);
							SIZE size;
							GetTextExtentPoint(hDC, str, lstrlen(str), &size);
							TextOut(hDC, monster[i].x - (mw / 2) + (size.cx / 2) + 7, 550 + (mh * 2), str, lstrlen(str));
							SelectObject(hDC, oldFont);
							DeleteObject(hFont);
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
							slmIdle3.Draw(hDC, monster[i].x - (mw / 2) + 10, 550, mw * 2, mh * 2, 0, 0, mw, mh);
							int hpw = HPbar.GetWidth();
							int hph = HPbar.GetHeight();
							HPbar.Draw(hDC, monster[i].x - (mw / 2), 550 + (mh * 2), hpw, hph, 0, 0, hpw, hph);
							if (monster[i].hp.Current_hp > 0)
							{
								float percent = hpw * (monster[i].hp.Current_hp / (float)(monster[i].hp.Max_hp));
								int intper = (int)percent;
								HPred.Draw(hDC, monster[i].x - (mw / 2) - 1, 550 + (mh * 2) + 1, intper, hph, 0, 0, intper, hph);
							}
							HFONT hFont, oldFont;
							hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, L"궁서");
							oldFont = (HFONT)SelectObject(hDC, hFont);
							WCHAR str[20];
							wsprintf(str, L"%d / %d", monster[i].hp.Current_hp, monster[i].hp.Max_hp);
							SIZE size;
							GetTextExtentPoint(hDC, str, lstrlen(str), &size);
							TextOut(hDC, monster[i].x - (mw / 2) + (size.cx / 2) + 7, 550 + (mh * 2), str, lstrlen(str));
							SelectObject(hDC, oldFont);
							DeleteObject(hFont);
							monsterTimer[i]++;
							if (monsterTimer[i] >= 15)
							{
								monster[i].animation_num++;
							}
						}
						break;
						case 3:
						{
							int mw = slmAttack1.GetWidth();
							int mh = slmAttack1.GetHeight();
							slmAttack1.Draw(hDC, player->x + (mw / 2) + 50, 150 + (monsterTimer[i] - 1) * 15, mw * 2, mh * 2, 0, 0, mw, mh);
							TextOut(hDC, 600, 200, L"공  격", 4);
							mw = slmIdle1.GetWidth();
							mh = slmIdle1.GetHeight();
							int hpw = HPbar.GetWidth();
							int hph = HPbar.GetHeight();
							HPbar.Draw(hDC, monster[i].x - (mw / 2), 550 + (mh * 2), hpw, hph, 0, 0, hpw, hph);
							if (monster[i].hp.Current_hp > 0)
							{
								float percent = hpw * (monster[i].hp.Current_hp / (float)(monster[i].hp.Max_hp));
								int intper = (int)percent;
								HPred.Draw(hDC, monster[i].x - (mw / 2) - 1, 550 + (mh * 2) + 1, intper, hph, 0, 0, intper, hph);
							}
							HFONT hFont, oldFont;
							hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, L"궁서");
							oldFont = (HFONT)SelectObject(hDC, hFont);
							WCHAR str[20];
							wsprintf(str, L"%d / %d", monster[i].hp.Current_hp, monster[i].hp.Max_hp);
							SIZE size;
							GetTextExtentPoint(hDC, str, lstrlen(str), &size);
							TextOut(hDC, monster[i].x - (mw / 2) + (size.cx / 2) + 7, 550 + (mh * 2), str, lstrlen(str));
							SelectObject(hDC, oldFont);
							DeleteObject(hFont);
							monsterTimer[i]++;
							if (monsterTimer[i] >= 30)
							{
								monster[i].animation_num++;
								CalcDmg(player, monster[i]);
								DmgTimer = 0;
								SetEnemyDmgPrint(hWnd);

								player->animation_state = State_Attacked;
								player->animation_num = 0;
							}
						}
						break;
						case 4:
						{
							int mw = slmAttack2.GetWidth();
							int mh = slmAttack2.GetHeight();
							slmAttack2.Draw(hDC, player->x + (mw / 2) + 10, 550, mw * 2, mh * 2, 0, 0, mw, mh);
							TextOut(hDC, 600, 200, L"공  격", 4);
							mw = slmIdle1.GetWidth();
							mh = slmIdle1.GetHeight();
							int hpw = HPbar.GetWidth();
							int hph = HPbar.GetHeight();
							HPbar.Draw(hDC, monster[i].x - (mw / 2), 550 + (mh * 2), hpw, hph, 0, 0, hpw, hph);
							if (monster[i].hp.Current_hp > 0)
							{
								float percent = hpw * (monster[i].hp.Current_hp / (float)(monster[i].hp.Max_hp));
								int intper = (int)percent;
								HPred.Draw(hDC, monster[i].x - (mw / 2) - 1, 550 + (mh * 2) + 1, intper, hph, 0, 0, intper, hph);
							}
							HFONT hFont, oldFont;
							hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, L"궁서");
							oldFont = (HFONT)SelectObject(hDC, hFont);
							WCHAR str[20];
							wsprintf(str, L"%d / %d", monster[i].hp.Current_hp, monster[i].hp.Max_hp);
							SIZE size;
							GetTextExtentPoint(hDC, str, lstrlen(str), &size);
							TextOut(hDC, monster[i].x - (mw / 2) + (size.cx / 2) + 7, 550 + (mh * 2), str, lstrlen(str));
							SelectObject(hDC, oldFont);
							DeleteObject(hFont);
							monsterTimer[i]++;
							if (monsterTimer[i] >= 35)
							{
								monster[i].animation_num++;
							}
						}
						break;
						case 5:
						{
							int mw = slmAttack3.GetWidth();
							int mh = slmAttack3.GetHeight();
							slmAttack3.Draw(hDC, player->x + (mw / 2) + 10, 550, mw * 2, mh * 2, 0, 0, mw, mh);
							TextOut(hDC, 600, 200, L"공  격", 4);
							mw = slmIdle1.GetWidth();
							mh = slmIdle1.GetHeight();
							int hpw = HPbar.GetWidth();
							int hph = HPbar.GetHeight();
							HPbar.Draw(hDC, monster[i].x - (mw / 2), 550 + (mh * 2), hpw, hph, 0, 0, hpw, hph);
							if (monster[i].hp.Current_hp > 0)
							{
								float percent = hpw * (monster[i].hp.Current_hp / (float)(monster[i].hp.Max_hp));
								int intper = (int)percent;
								HPred.Draw(hDC, monster[i].x - (mw / 2) - 1, 550 + (mh * 2) + 1, intper, hph, 0, 0, intper, hph);
							}
							HFONT hFont, oldFont;
							hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, L"궁서");
							oldFont = (HFONT)SelectObject(hDC, hFont);
							WCHAR str[20];
							wsprintf(str, L"%d / %d", monster[i].hp.Current_hp, monster[i].hp.Max_hp);
							SIZE size;
							GetTextExtentPoint(hDC, str, lstrlen(str), &size);
							TextOut(hDC, monster[i].x - (mw / 2) + (size.cx / 2) + 7, 550 + (mh * 2), str, lstrlen(str));
							SelectObject(hDC, oldFont);
							DeleteObject(hFont);
							monsterTimer[i]++;
							if (monsterTimer[i] >= 45)
							{
								monster[i].animation_num++;
							}
						}
						break;
						case 6:
						{
							int mw = slmAttack4.GetWidth();
							int mh = slmAttack4.GetHeight();
							slmAttack4.Draw(hDC, player->x + (mw / 2) + 10, 550, mw * 2, mh * 2, 0, 0, mw, mh);
							TextOut(hDC, 600, 200, L"공  격", 4);
							mw = slmIdle1.GetWidth();
							mh = slmIdle1.GetHeight();
							int hpw = HPbar.GetWidth();
							int hph = HPbar.GetHeight();
							HPbar.Draw(hDC, monster[i].x - (mw / 2), 550 + (mh * 2), hpw, hph, 0, 0, hpw, hph);
							if (monster[i].hp.Current_hp > 0)
							{
								float percent = hpw * (monster[i].hp.Current_hp / (float)(monster[i].hp.Max_hp));
								int intper = (int)percent;
								HPred.Draw(hDC, monster[i].x - (mw / 2) - 1, 550 + (mh * 2) + 1, intper, hph, 0, 0, intper, hph);
							}
							HFONT hFont, oldFont;
							hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, L"궁서");
							oldFont = (HFONT)SelectObject(hDC, hFont);
							WCHAR str[20];
							wsprintf(str, L"%d / %d", monster[i].hp.Current_hp, monster[i].hp.Max_hp);
							SIZE size;
							GetTextExtentPoint(hDC, str, lstrlen(str), &size);
							TextOut(hDC, monster[i].x - (mw / 2) + (size.cx / 2) + 7, 550 + (mh * 2), str, lstrlen(str));
							SelectObject(hDC, oldFont);
							DeleteObject(hFont);
							monsterTimer[i]++;
							if (monsterTimer[i] >= 55)
							{
								monster[i].animation_num++;
							}
						}
						break;
						case 7:
						{
							int mw = slmAttack5.GetWidth();
							int mh = slmAttack5.GetHeight();
							slmAttack5.Draw(hDC, player->x + (mw / 2) + 10, 550, mw * 2, mh * 2, 0, 0, mw, mh);
							TextOut(hDC, 600, 200, L"공  격", 4);
							mw = slmIdle1.GetWidth();
							mh = slmIdle1.GetHeight();
							int hpw = HPbar.GetWidth();
							int hph = HPbar.GetHeight();
							HPbar.Draw(hDC, monster[i].x - (mw / 2), 550 + (mh * 2), hpw, hph, 0, 0, hpw, hph);
							if (monster[i].hp.Current_hp > 0)
							{
								float percent = hpw * (monster[i].hp.Current_hp / (float)(monster[i].hp.Max_hp));
								int intper = (int)percent;
								HPred.Draw(hDC, monster[i].x - (mw / 2) - 1, 550 + (mh * 2) + 1, intper, hph, 0, 0, intper, hph);
							}
							HFONT hFont, oldFont;
							hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, L"궁서");
							oldFont = (HFONT)SelectObject(hDC, hFont);
							WCHAR str[20];
							wsprintf(str, L"%d / %d", monster[i].hp.Current_hp, monster[i].hp.Max_hp);
							SIZE size;
							GetTextExtentPoint(hDC, str, lstrlen(str), &size);
							TextOut(hDC, monster[i].x - (mw / 2) + (size.cx / 2) + 7, 550 + (mh * 2), str, lstrlen(str));
							SelectObject(hDC, oldFont);
							DeleteObject(hFont);
							monsterTimer[i]++;
							if (monsterTimer[i] >= 65)
							{
								monster[i].animation_num++;
							}
						}
						break;
						case 8:
						{
							int mw = slmAttack6.GetWidth();
							int mh = slmAttack6.GetHeight();
							slmAttack6.Draw(hDC, player->x + (mw / 2) + 10, 550, mw * 2, mh * 2, 0, 0, mw, mh);
							TextOut(hDC, 600, 200, L"공  격", 4);
							mw = slmIdle1.GetWidth();
							mh = slmIdle1.GetHeight();
							int hpw = HPbar.GetWidth();
							int hph = HPbar.GetHeight();
							HPbar.Draw(hDC, monster[i].x - (mw / 2), 550 + (mh * 2), hpw, hph, 0, 0, hpw, hph);
							if (monster[i].hp.Current_hp > 0)
							{
								float percent = hpw * (monster[i].hp.Current_hp / (float)(monster[i].hp.Max_hp));
								int intper = (int)percent;
								HPred.Draw(hDC, monster[i].x - (mw / 2) - 1, 550 + (mh * 2) + 1, intper, hph, 0, 0, intper, hph);
							}
							HFONT hFont, oldFont;
							hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, L"궁서");
							oldFont = (HFONT)SelectObject(hDC, hFont);
							WCHAR str[20];
							wsprintf(str, L"%d / %d", monster[i].hp.Current_hp, monster[i].hp.Max_hp);
							SIZE size;
							GetTextExtentPoint(hDC, str, lstrlen(str), &size);
							TextOut(hDC, monster[i].x - (mw / 2) + (size.cx / 2) + 7, 550 + (mh * 2), str, lstrlen(str));
							SelectObject(hDC, oldFont);
							DeleteObject(hFont);
							monsterTimer[i]++;
							if (monsterTimer[i] >= 75)
							{
								monster[i].animation_state = State_Idle;
								monster[i].animation_num = 0;
								monsterTimer[i] = 0;

							}

						}
						break;
						}
					}
					else if (monster[i].animation_state == State_Dead)
					{
						switch (monster[i].animation_num)
						{
						case 0:
						{
							int mw = slmIdle4.GetWidth();
							int mh = slmIdle4.GetHeight();
							slmIdle4.Draw(hDC, monster[i].x - (mw / 2), 550, mw * 2, mh * 2, 0, 0, mw, mh);
							monsterTimer[i]++;
							if (monsterTimer[i] >= 10)
							{
								monster[i].animation_num++;
							}
						}
						break;
						case 1:
						{
							int mw = slmIdle5.GetWidth();
							int mh = slmIdle5.GetHeight();
							slmIdle5.Draw(hDC, monster[i].x - (mw / 2), 550, mw * 2, mh * 2, 0, 0, mw, mh);
							monsterTimer[i]++;
							if (monsterTimer[i] >= 20)
							{
								monster[i].animation_num++;
							}
						}
						break;
						case 2:
						{
							int mw = slmIdle6.GetWidth();
							int mh = slmIdle6.GetHeight();
							slmIdle6.Draw(hDC, monster[i].x - (mw / 2), 550, mw * 2, mh * 2, 0, 0, mw, mh);
							monsterTimer[i]++;
							if (monsterTimer[i] >= 30)
							{
								monster[i].animation_num++;
							}
						}
						break;
						case 3:
						{
							int mw = slmAttack4.GetWidth();
							int mh = slmAttack4.GetHeight();
							slmAttack4.Draw(hDC, monster[i].x - (mw / 2) - 10, 550, mw * 2, mh * 2, 0, 0, mw, mh);
							monsterTimer[i]++;
							if (monsterTimer[i] >= 40)
							{
								monster[i].animation_num++;
							}
						}
						break;
						case 4:
						{
							int mw = slmAttack3.GetWidth();
							int mh = slmAttack3.GetHeight();
							slmAttack3.Draw(hDC, monster[i].x - (mw / 2) - 10, 550, mw * 2, mh * 2, 0, 0, mw, mh);
							monsterTimer[i]++;
							if (monsterTimer[i] >= 50)
							{
								monster[i].animation_num++;
							}
						}
						break;
						case 5:
						{
							int mw = slmAttack2.GetWidth();
							int mh = slmAttack2.GetHeight();
							slmAttack2.Draw(hDC, monster[i].x - (mw / 2) - 10, 550, mw * 2, mh * 2, 0, 0, mw, mh);
							monsterTimer[i]++;
							if (monsterTimer[i] >= 60)
							{
								monsterTimer[i] = 0;
								monster[i].is_Active = FALSE;
								isCharMove = FALSE;
								CheckState(hWnd, player);
							}
						}
						break;
						}
					}
					else if (State_Attacked)
					{
						switch (monster[i].animation_num)
						{
						case 0:
						{
							int mw = slmIdle1.GetWidth();
							int mh = slmIdle1.GetHeight();
							slmIdle1.Draw(hDC, monster[i].x - (mw / 2) + 30, 550, mw * 2, mh * 2, 0, 0, mw, mh);
							int hpw = HPbar.GetWidth();
							int hph = HPbar.GetHeight();
							HPbar.Draw(hDC, monster[i].x - (mw / 2), 550 + (mh * 2), hpw, hph, 0, 0, hpw, hph);
							if (monster[i].hp.Current_hp > 0)
							{
								float percent = hpw * (monster[i].hp.Current_hp / (float)(monster[i].hp.Max_hp));
								int intper = (int)percent;
								HPred.Draw(hDC, monster[i].x - (mw / 2) - 1, 550 + (mh * 2) + 1, intper, hph, 0, 0, intper, hph);
							}

							HFONT hFont, oldFont;
							hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, L"궁서");
							oldFont = (HFONT)SelectObject(hDC, hFont);
							WCHAR str[20];
							wsprintf(str, L"%d / %d", monster[i].hp.Current_hp, monster[i].hp.Max_hp);
							SIZE size;
							GetTextExtentPoint(hDC, str, lstrlen(str), &size);
							TextOut(hDC, monster[i].x - (mw / 2) + (size.cx / 2) + 7, 550 + (mh * 2), str, lstrlen(str));
							SelectObject(hDC, oldFont);
							DeleteObject(hFont);
							monsterTimer[i]++;
							if (monsterTimer[i] >= 5)
							{
								monster[i].animation_num++;
							}
						}
						break;
						case 1:
						{
							int mw = slmIdle1.GetWidth();
							int mh = slmIdle1.GetHeight();
							slmIdle1.Draw(hDC, monster[i].x - (mw / 2) + 20, 550, mw * 2, mh * 2, 0, 0, mw, mh);
							int hpw = HPbar.GetWidth();
							int hph = HPbar.GetHeight();
							HPbar.Draw(hDC, monster[i].x - (mw / 2), 550 + (mh * 2), hpw, hph, 0, 0, hpw, hph);
							if (monster[i].hp.Current_hp > 0)
							{
								float percent = hpw * (monster[i].hp.Current_hp / (float)(monster[i].hp.Max_hp));
								int intper = (int)percent;
								HPred.Draw(hDC, monster[i].x - (mw / 2) - 1, 550 + (mh * 2) + 1, intper, hph, 0, 0, intper, hph);
							}
							HFONT hFont, oldFont;
							hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, L"궁서");
							oldFont = (HFONT)SelectObject(hDC, hFont);
							WCHAR str[20];
							wsprintf(str, L"%d / %d", monster[i].hp.Current_hp, monster[i].hp.Max_hp);
							SIZE size;
							GetTextExtentPoint(hDC, str, lstrlen(str), &size);
							TextOut(hDC, monster[i].x - (mw / 2) + (size.cx / 2) + 7, 550 + (mh * 2), str, lstrlen(str));
							SelectObject(hDC, oldFont);
							DeleteObject(hFont);
							monsterTimer[i]++;
							if (monsterTimer[i] >= 15)
							{
								monster[i].animation_num++;
							}
						}
						break;
						case 2:
						{
							int mw = slmIdle1.GetWidth();
							int mh = slmIdle1.GetHeight();
							slmIdle1.Draw(hDC, monster[i].x - (mw / 2) + 10, 550, mw * 2, mh * 2, 0, 0, mw, mh);
							int hpw = HPbar.GetWidth();
							int hph = HPbar.GetHeight();
							HPbar.Draw(hDC, monster[i].x - (mw / 2), 550 + (mh * 2), hpw, hph, 0, 0, hpw, hph);
							if (monster[i].hp.Current_hp > 0)
							{
								float percent = hpw * (monster[i].hp.Current_hp / (float)(monster[i].hp.Max_hp));
								int intper = (int)percent;
								HPred.Draw(hDC, monster[i].x - (mw / 2) - 1, 550 + (mh * 2) + 1, intper, hph, 0, 0, intper, hph);
							}
							HFONT hFont, oldFont;
							hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, L"궁서");
							oldFont = (HFONT)SelectObject(hDC, hFont);
							WCHAR str[20];
							wsprintf(str, L"%d / %d", monster[i].hp.Current_hp, monster[i].hp.Max_hp);
							SIZE size;
							GetTextExtentPoint(hDC, str, lstrlen(str), &size);
							TextOut(hDC, monster[i].x - (mw / 2) + (size.cx / 2) + 7, 550 + (mh * 2), str, lstrlen(str));
							SelectObject(hDC, oldFont);
							DeleteObject(hFont);
							monsterTimer[i]++;
							if (monsterTimer[i] >= 25)
							{
								monster[i].animation_num++;
							}
						}
						break;
						case 3:
						{
							int mw = slmIdle1.GetWidth();
							int mh = slmIdle1.GetHeight();
							slmIdle1.Draw(hDC, monster[i].x - (mw / 2), 550, mw * 2, mh * 2, 0, 0, mw, mh);
							int hpw = HPbar.GetWidth();
							int hph = HPbar.GetHeight();
							HPbar.Draw(hDC, monster[i].x - (mw / 2), 550 + (mh * 2), hpw, hph, 0, 0, hpw, hph);
							if (monster[i].hp.Current_hp > 0)
							{
								float percent = hpw * (monster[i].hp.Current_hp / (float)(monster[i].hp.Max_hp));
								int intper = (int)percent;
								HPred.Draw(hDC, monster[i].x - (mw / 2) - 1, 550 + (mh * 2) + 1, intper, hph, 0, 0, intper, hph);
							}
							HFONT hFont, oldFont;
							hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, L"궁서");
							oldFont = (HFONT)SelectObject(hDC, hFont);
							WCHAR str[20];
							wsprintf(str, L"%d / %d", monster[i].hp.Current_hp, monster[i].hp.Max_hp);
							SIZE size;
							GetTextExtentPoint(hDC, str, lstrlen(str), &size);
							TextOut(hDC, monster[i].x - (mw / 2) + (size.cx / 2) + 7, 550 + (mh * 2), str, lstrlen(str));
							SelectObject(hDC, oldFont);
							DeleteObject(hFont);
							monsterTimer[i]++;
							if (monsterTimer[i] >= 35)
							{
								monster[i].animation_state = State_Idle;
								monster[i].animation_num = 0;
								monsterTimer[i] = 0;
							}
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

	if (isMyDmgPrint)
	{
		DmgTimer++;
		WCHAR tstr[20] = { 0 };
		int mw = slmIdle1.GetWidth();
		int mh = slmIdle1.GetHeight();
		wsprintf(tstr, L"%d", myAtkDmg);
		TextOut(hDC, monster[AtkMonster].x - (mw / 2) + 50, 500 - DmgTimer, tstr, lstrlen(tstr));
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
				if (isFront)
				{
					if (player->cost >= 1)
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
				}
			}
			else if (player->deck.card[frontCard].type == Card_Type_Attack)
			{
				if (isFront)
				{
					if (player->cost >= 1)
					{
						isAtkSelected = TRUE;
						player->isDragCard = TRUE;
						isSelected = TRUE;
						arrow_pos = { player->deck.card[frontCard].left + 100, player->deck.card[frontCard].top + 130 };
						arrow_endPos = { x, y };
					}
				}
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
					if (player->cost >= 1)
					{
						PlayerDeffence(hWnd, player);
					}
				}
				else
				{
					CardAnimToXy(hWnd, Lx, Ly, Card_Timer, &(player->deck.card[frontCard]), frontCard);
				}
			}
			else if (player->deck.card[frontCard].type == Card_Type_Attack)
			{
				if (player->cost >= 1)
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
							if (monster[i].hp.Current_hp != 0)
							{
								isInRect = TRUE;
								AtkMonster = i;
								break;
							}
						}
					}

					if (isInRect)
					{

						PlayerAttack(hWnd, player);
					}
				}
			}
		}
		if (player->isMyTurn)
		{
			RECT lrect;

			lrect.left = 1050;
			lrect.top = 650;
			lrect.right = 1050 + turnEnd.GetWidth();
			lrect.bottom = 650 + turnEnd.GetHeight();

			if (is_in_rect(x, y, lrect))
			{
				if (!isCardMove && !isCharMove)
				{
					for (int i = 0; i < 50; ++i)
					{
						player->deck.card[i] = { 0 };
					}
					SetTurnChangeTimer(hWnd);
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
		if (player->isMyTurn)
		{
			RECT lrect;
			lrect.left = 1050;
			lrect.top = 650;
			lrect.right = 1050 + turnEnd.GetWidth();
			lrect.bottom = 650 + turnEnd.GetHeight();
			if (is_in_rect(x, y, lrect))
			{
				isMouseUpTurnEnd = TRUE;
			}
			else
			{
				isMouseUpTurnEnd = FALSE;
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

void StartStage(HWND hWnd, Player* player, int monsterNum)
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
	POS* tposp = GetPosPointer();
	tposp->x = pos.x;
	tposp->y = pos.y;
	isMyTurnPrint = FALSE;
	SetMyTurnPrint(hWnd);

}

void ChangePlayerTurn(HWND hWnd, Player* player)
{
	SetCard(player);

	player->isMyTurn = TRUE;

	Shupple(player, 10);
	player->deck.card[0].is_inhand = TRUE;
	player->deck.card[1].is_inhand = TRUE;
	player->deck.card[2].is_inhand = TRUE;
	player->deck.card[3].is_inhand = TRUE;
	player->deck.card[4].is_inhand = TRUE;
	for (int i = 0; i < 5; ++i)
	{
		player->deck.card[i].left = 1200;
		player->deck.card[i].right = 1400;
		player->deck.card[i].top = 800;
		player->deck.card[i].bottom = 1060;
	}
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

void PlayerAttack(HWND hWnd, Player* player)
{
	player->deck.card[frontCard] = { 0 };
	player->cost--;
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
	isCharMove = TRUE;
	timer = 0;




	isFront = FALSE;
	isSelected = FALSE;

	if (player->cost == 0)
	{
		CheckState(hWnd, player);
	}

}

void PlayerDeffence(HWND hWnd, Player* player)
{
	player->deck.card[frontCard] = { 0 };
	player->cost--;
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

	player->animation_state = State_Deffence;
	player->animation_num = 0;
	isCharMove = TRUE;
	timer = 0;

	player->hp.Shield_figure += CalcShield(player);

	isFront = FALSE;
	isSelected = FALSE;

	if (player->cost == 0)
	{
		CheckState(hWnd, player);
	}

}

void SetCardPos(HWND hWnd, Player* player, int num)
{
	switch (num)
	{
	case 0:
	{
		isTurnChange = TRUE;

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
	myAtkDmg = 5 + player->item.buffs[0].num;
	return myAtkDmg;
}

void CalcDmg(Player* player, Monster monster)
{

	monsterAtkDmg = rand() % (monster.maxDmg-monster.minDmg + 1) + monster.minDmg;
	if (player->hp.Shield_figure > 0)
	{
		if (player->hp.Shield_figure >= monsterAtkDmg)
		{
			player->hp.Shield_figure -= monsterAtkDmg;
		}
		else
		{
			player->hp.Current_hp -= (monsterAtkDmg - player->hp.Shield_figure);

			if (player->hp.Current_hp <= 0)
			{
				player->hp.Current_hp = 0;
			}

			player->hp.Shield_figure = 0;

		}
	}
	else
	{
		player->hp.Current_hp -= monsterAtkDmg;

		if (player->hp.Current_hp <= 0)
		{
			player->hp.Current_hp = 0;
		}
	}
}
int CalcShield(Player* player)
{
	return 5 + player->item.buffs[1].num;
}

void TurnChange(HWND hWnd, Player* player)
{
	if (player->isMyTurn)
	{

			isTurnChange = FALSE;
			isChangedTurn = TRUE;
			player->isMyTurn = FALSE;
			for (int i = 0; i < MNCD; ++i)
			{
				player->deck.card[i] = { 0 };
			}
			TurnMonsterNum = 0;
			for (int i = TurnMonsterNum; i < 3; ++i)
			{
				if (monster[TurnMonsterNum].is_Active)
				{
					monster[TurnMonsterNum].animation_state = State_Attack;
					monster[TurnMonsterNum].animation_num = 0;
					monsterTimer[TurnMonsterNum] = 0;
//					player->hp.Current_hp -= CalcDmg(monster[TurnMonsterNum]);
					break;
				}
				else
				{
					TurnMonsterNum++;
				}
			}
			SetEnemyTurnPrint(hWnd);
	}
	else
	{
		BOOL isMonsterTurnNoneEnd = FALSE;

		TurnMonsterNum++;

		for (int i = TurnMonsterNum; i < 3; ++i)
		{
			if (monster[i].is_Active)
			{
				monster[i].animation_state = State_Attack;
				monster[i].animation_num = 0;
				monsterTimer[i] = 0;
//				player->hp.Current_hp -= CalcDmg(monster[i]);
				TurnMonsterNum = i;
				isMonsterTurnNoneEnd = TRUE;
				break;
			}
		}
		
		if (!isMonsterTurnNoneEnd)
		{
			player->isMyTurn = TRUE;
			player->cost = 3;
			ChangePlayerTurn(hWnd, player);
			SetMyTurnPrint(hWnd);
		}

	}
}

void CheckState(HWND hWnd, Player* player)
{

	BOOL isWin = TRUE;

	for (int i = 0; i < 3; ++i)
	{
		if (monster[i].is_Active)
		{
			isWin = FALSE;
		}
	}

	if (isWin)
	{
		PlayerWin(hWnd);
		return;
	}

	if (player->hp.Current_hp == 0)
	{
		PlayerDefeat(hWnd);
		return;
	}
	
	if (!isCharMove)
	{
		for (int i = 0; i < 3; ++i)
		{
			if (monster[i].hp.Current_hp == 0)
			{
				if (monster[i].is_Active)
				{
					monster[i].animation_state = State_Dead;
					monster[i].animation_num = 0;
					monsterTimer[i] = 0;
					isCharMove = TRUE;
					return;
				}
			}
		}
	}

	if (!isCharMove)
	{
		if (player->cost == 0)
		{
			SetTurnChangeTimer(hWnd);
			return;
		}
	}
}



void SetTurnChangeTimer(HWND hWnd)
{
	SetTimer(hWnd, TurnDelay_Timer, 500, NULL);
}

void GetTurnChangeTimer(HWND hWnd, Player* player)
{
	TurnChange(hWnd, player);
}

void SetMyTurnPrint(HWND hWnd)
{
	if (isMyTurnPrint == FALSE)
	{
		isMyTurnPrint = TRUE;
		isEnemyTurnPrint = FALSE;
		SetTimer(hWnd, Print_Timer, 2500, NULL);
	}
	else
	{
		isMyTurnPrint = FALSE;
		KillTimer(hWnd, Print_Timer);
	}
}

void SetEnemyTurnPrint(HWND hWnd)
{
	if (isEnemyTurnPrint == FALSE)
	{
		isEnemyTurnPrint = TRUE;
		isMyTurnPrint = FALSE;
		SetTimer(hWnd, Print_Timer, 2500, NULL);
	}
	else
	{
		isEnemyTurnPrint = FALSE;
		KillTimer(hWnd, Print_Timer);
	}
}

void SetEnemyDmgPrint(HWND hWnd)
{
	if (isEnemyDmgPrint == FALSE)
	{
		isEnemyDmgPrint = TRUE;
		isMyDmgPrint = FALSE;
		SetTimer(hWnd, DmgPrint_Timer, 1500, NULL);
	}
	else
	{
		isEnemyDmgPrint = FALSE;
		KillTimer(hWnd, DmgPrint_Timer);
	}
}

void SetMyDmgPrint(HWND hWnd)
{
	if (isMyDmgPrint == FALSE)
	{
		isMyDmgPrint = TRUE;
		isEnemyDmgPrint = FALSE;
		SetTimer(hWnd, DmgPrint_Timer, 1500, NULL);
	}
	else
	{
		isMyDmgPrint = FALSE;
		KillTimer(hWnd, DmgPrint_Timer);
	}
}

int GetDmgPrint()
{
	if (isMyDmgPrint)
	{
		return 1;
	}
	else if (isEnemyDmgPrint)
	{
		return 2;
	}

	return 0;
}

int GetPrint()
{
	if (isMyTurnPrint == TRUE)
	{
		return 1;
	}
	else if (isEnemyTurnPrint == TRUE)
	{
		return 2;
	}

	return 0;
}

void PlayerDefeat(HWND hWnd)
{
	
	KillTimer(hWnd, 1);
	MessageBox(hWnd, L"플레이어 패배", L"패배", MB_OK);
}

void PlayerWin(HWND hWnd)
{

	ChangeScreenNumber(1);
}

