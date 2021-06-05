#include "header.h"

//static HWND hButton_Start_game;
//static HWND hButton_Dictionary;
//static HWND hButton_Exit;
//

static RECT rStart_game;//게임시작
static RECT rDictionary;//백과사전
static RECT rExit;//종료

static CImage cStart_game;
static CImage cDictionary;
static CImage cExit;

static BOOL is_on_start_game;
static BOOL is_on_Dictionary;
static BOOL is_on_Exit;

void Set_MS_Img()
{
	if (cStart_game.IsNull())
		cStart_game.Load(L"Start_game.png");
	if (cDictionary.IsNull())
		cDictionary.Load(L"Dictionary.png");
	if (cExit.IsNull())
		cExit.Load(L"Exit.png");
}

void set_MS_Button(HWND hWnd, RECT cRect, HINSTANCE g_hInst)
{
//	hButton_Start_game = CreateWindow(L"button", L"Select", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, cRect.bottom + 150, cRect.bottom - 280, 120, 50, hWnd, (HMENU)MAIN_BUTTON_Start_game, g_hInst, NULL);
//	hButton_Dictionary = CreateWindow(L"button", L"Done", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, cRect.bottom + 150, cRect.bottom - 210, 200, 50, hWnd, (HMENU)MAIN_BUTTON_Dictionary, g_hInst, NULL);
//	hButton_Exit = CreateWindow(L"button", L"Move", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, cRect.bottom + 150, cRect.bottom - 140, 200, 50, hWnd, (HMENU)MAIN_BUTTON_Exit, g_hInst, NULL);

	rStart_game.left = 100;
	rStart_game.right = 300;
	rStart_game.top = cRect.bottom / 2;
	rStart_game.bottom = cRect.bottom / 2 + 50;

	rDictionary.left = 100;
	rDictionary.right = 300;
	rDictionary.top = cRect.bottom / 2 + 70;;
	rDictionary.bottom = cRect.bottom / 2 + 120;

	rExit.left = 100;
	rExit.right = 200;
	rExit.top = cRect.bottom / 2 + 140;
	rExit.bottom = cRect.bottom / 2 + 190;
}


void print_MS(HDC hDC, RECT cRect,int main_menu)
{
	Set_MS_Img();
	Rectangle(hDC, 0, 0, cRect.right, cRect.bottom);//메인화면의 배경 출력 - 비트맵 이미지로 대체할것
			// 차일드 윈도우 버튼 3개 생성
	switch (main_menu)
	{
	case 0:
		//선택지 화면
		//메인화면의 버튼 출력 - 비트맵 이미지로 대체할것
		if (!is_on_start_game)
		{
			int pw = cStart_game.GetWidth();
			int ph = cStart_game.GetHeight();
			cStart_game.Draw(hDC, rStart_game.left, rStart_game.top, pw, ph, 0, 0, pw, ph);
		}
		else
			Rectangle(hDC, rStart_game.left, rStart_game.top, rStart_game.right, rStart_game.bottom);
		if (!is_on_Dictionary)
		{
			int pw = cDictionary.GetWidth();
			int ph = cDictionary.GetHeight();
			cDictionary.Draw(hDC, rDictionary.left, rDictionary.top, pw, ph, 0, 0, pw, ph);
		}
		else
			Rectangle(hDC, rDictionary.left, rDictionary.top, rDictionary.right, rDictionary.bottom);
		if (!is_on_Exit)
		{
			int pw = cExit.GetWidth();
			int ph = cExit.GetHeight();
			cExit.Draw(hDC, rExit.left, rExit.top, pw, ph, 0, 0, pw, ph);
		}
		else
			Rectangle(hDC, rExit.left, rExit.top, rExit.right, rExit.bottom);

		break;
	case 1:
		//게임 시작 -> 캐릭터 선택
		//현재 존재하는 캐릭터를 화면에 출력
		//키보드 1, 2, 3 or 캐릭터 클릭을 통해 선택하고 게임 시작 누를 시 게임 시작 -- screen_number = 1;
		break;
	case 2:
		// 백과사전 -> 카드, 유물 열람기능
		break;
	case 3:
		// 말 그대로 클릭시 게임 종료
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

void MS_LBUTTONDOWN(HWND hWnd, int mx, int my, int* main_menu, int* screen_number)
{
	int answer;
	switch (*main_menu)
	{
	case 0:
		if (is_in_rect(mx, my, rStart_game))
		{
			answer = MessageBox(hWnd, L"미완성이므로 바로 전투 화면이로 이동", L"게임 시작", MB_YESNO);
			if (answer == IDYES)
				*screen_number = 2;
		}// 메뉴가 완성되면 수정
			//*main_menu = 1;
		if (is_in_rect(mx, my, rDictionary))
		{
			MessageBox(hWnd, L"미구현", L"백과사전", MB_OK);
		}
		if (is_in_rect(mx, my, rExit))
		{
			answer = MessageBox(hWnd, L"정말로?", L"게임 종료", MB_YESNO);
			if (answer == IDYES)
				DestroyWindow(hWnd);
		}
		break;
	case 1:
		// 캐릭터를 누르면 게임 시작
		break;
	case 2:
		// 백과사전 출력
		break;
	}
}
void MS_MOUSEMOVE(int mx, int my, int main_menu)
{
	is_on_start_game = FALSE;
	is_on_Dictionary = FALSE;
	is_on_Exit = FALSE;

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
		//위랑 비슷하게 볼드 효과
		break;
	case 2:
		//위랑 비슷하게 볼드 효과
		break;
	}
	

}