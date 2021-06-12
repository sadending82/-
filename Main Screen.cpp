#include "header.h"


//	main_menu == 0
static RECT rStart_game;//���ӽ���
static RECT rDictionary;//�������
static RECT rExit;//����

static CImage cStart_game;
static CImage cDictionary;
static CImage cExit;

static BOOL is_on_start_game;
static BOOL is_on_Dictionary;
static BOOL is_on_Exit;

//	main_menu == 1
static RECT rCharacter1;
static RECT rCharacter2;

static CImage cCharacter1;
static CImage cCharacter2;

static BOOL is_on_Character1;
static BOOL is_on_Character2;


void Set_MS_Img()
{
	//	main_menu == 0
	if (cStart_game.IsNull())
		cStart_game.Load(L"Start_game.png");
	if (cDictionary.IsNull())
		cDictionary.Load(L"Dictionary.png");
	if (cExit.IsNull())
		cExit.Load(L"Exit.png");
	// 3���� �߰��� ����

	//	main_menu == 1
	if (cCharacter1.IsNull())
		cCharacter1.Load(L"Character1.png");
	if (cCharacter2.IsNull())
		cCharacter2.Load(L"Character2.png");
}

void set_MS_Button(HWND hWnd, RECT cRect, HINSTANCE g_hInst)
{
	//	main_menu == 0
	rStart_game.left = 100;
	rStart_game.right = 300;
	rStart_game.top = cRect.bottom / 2;
	rStart_game.bottom = cRect.bottom / 2 + 50;

	rDictionary.left = 100;
	rDictionary.right = 300;
	rDictionary.top = cRect.bottom / 2 + 70;;
	rDictionary.bottom = cRect.bottom / 2 + 120;

	rExit.left = 100;
	rExit.right = 300;
	rExit.top = cRect.bottom / 2 + 140;
	rExit.bottom = cRect.bottom / 2 + 190;
	//	main_menu == 1
	rCharacter1.left = 100;
	rCharacter1.right = rCharacter1.left + (cRect.right - 300) / 3;
	rCharacter1.top = 100;
	rCharacter1.bottom = cRect.bottom - 200;

	rCharacter2.left = rCharacter1.right + 50;
	rCharacter2.right = rCharacter2.left + (cRect.right - 300) / 3;
	rCharacter2.top = 100;
	rCharacter2.bottom = cRect.bottom - 200;
}

void print_button(HDC hDC,BOOL is_on, CImage* cButton,RECT rButton)
{
	if (!is_on)
	{
		int pw = cButton->GetWidth();
		int ph = cButton->GetHeight();
		cButton->Draw(hDC, rButton.left, rButton.top, rButton.right - rButton.left, rButton.bottom - rButton.top, 0, 0, pw, ph);
	}
	else
		Rectangle(hDC, rButton.left, rButton.top, rButton.right, rButton.bottom);
	//���⵵ �̹��� ���Ϸ� �ٲ� ����
}

void print_MS(HDC hDC, RECT cRect,int main_menu)
{
	Set_MS_Img();
	Rectangle(hDC, 0, 0, cRect.right, cRect.bottom);//����ȭ���� ��� ��� - ��Ʈ�� �̹����� ��ü�Ұ�
			// ���ϵ� ������ ��ư 3�� ����
	switch (main_menu)
	{
	case 0:
		//������ ȭ��
		//����ȭ���� ��ư ��� - ��Ʈ�� �̹����� ��ü�Ұ�
		print_button(hDC, is_on_start_game, &cStart_game, rStart_game);
		print_button(hDC, is_on_Dictionary, &cDictionary, rDictionary);
		print_button(hDC, is_on_Exit, &cExit, rExit);
		break;
	case 1:
		//���� ���� -> ĳ���� ����
		//���� �����ϴ� ĳ���͸� ȭ�鿡 ���
		//Ű���� 1, 2, 3 or ĳ���� Ŭ���� ���� �����ϰ� ���� ���� ���� �� ���� ���� -- screen_number = 1;
		print_button(hDC, is_on_Character1, &cCharacter1, rCharacter1);
		print_button(hDC, is_on_Character2, &cCharacter2, rCharacter2);
		break;
	case 2:
		// ������� -> ī��, ���� �������
		break;
	case 3:
		// �� �״�� Ŭ���� ���� ����
		break;
	}
}

BOOL is_in_rect(int x, int y, RECT rect)
{
	if (x > rect.left && x<rect.right && y>rect.top && y < rect.bottom)
		return TRUE;
	else
		return FALSE;
}

void MS_LBUTTONDOWN(HWND hWnd, int mx, int my, int* main_menu, int* screen_number, Player* player, Master* master)
{
	int answer;
	switch (*main_menu)
	{
	case 0:
		if (is_in_rect(mx, my, rStart_game))
		{
			*main_menu = 1;
		}
		if (is_in_rect(mx, my, rDictionary))
		{
			MessageBox(hWnd, L"�̱���", L"�������", MB_OK);
		}
		if (is_in_rect(mx, my, rExit))
		{
			answer = MessageBox(hWnd, L"������?", L"���� ����", MB_YESNO);
			if (answer == IDYES)
				DestroyWindow(hWnd);
		}
		break;
	case 1:
		// ĳ���͸� ������ ���� ����
		if (is_in_rect(mx, my, rCharacter1))
		{
			 //0��° ĳ���ͷ� ���� ����
			player->x = 200;
			player->hp = 80; // -*- ��� ���� �ϴ� �̷��� �������ϴ�.
			player->money = 0;
			player->occupation = 0;
			player->isCharacterActive = TRUE;
			player->animation_num = 0;
			player->animation_state = 0;
			master->player = *player;
			master->game_seed = rand();
			
			*screen_number = 1;
		}

		if (is_in_rect(mx, my, rCharacter2))
		{
			// 1��° ĳ���ͷ� ���� ���� - ���� 0�� ĳ���ͱ����ۿ� �����ϴ�.
			player->x = 200;
			player->hp = 70; // -*- ��� ���� �ϴ� �̷��� �������ϴ�.
			player->money = 0;
			player->occupation = 1;
			player->isCharacterActive = TRUE;
			player->animation_num = 0;
			player->animation_state = 0;
			master->player = *player;
			master->game_seed = rand();

			*screen_number = 2;
		}
		break;
	case 2:
		// ������� ���
		break;
	}
}

void MS_MOUSEMOVE(int mx, int my, int main_menu)
{
	is_on_start_game = FALSE;
	is_on_Dictionary = FALSE;
	is_on_Exit = FALSE;
	is_on_Character1 = FALSE;
	is_on_Character2 = FALSE;

	switch (main_menu)
	{
	case 0:
		if (is_in_rect(mx, my, rStart_game))
			is_on_start_game = TRUE;
		if (is_in_rect(mx, my, rDictionary))
			is_on_Dictionary = TRUE;
		if (is_in_rect(mx, my, rExit))
			is_on_Exit = TRUE;
		break;
	case 1:
		//���� ����ϰ� ���� ȿ��
		if (is_in_rect(mx, my, rCharacter1))
			is_on_Character1 = TRUE;
		if (is_in_rect(mx, my, rCharacter2))
			is_on_Character2 = TRUE;
		break;
	case 2:
		//���� ����ϰ� ���� ȿ��
		break;
	}
	

}

//??
void MS_MENU_1(HWND hWnd,int answer, int *screen_number)
{

}