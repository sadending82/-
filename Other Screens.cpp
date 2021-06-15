#include "header.h"

// 퍼즈, is_over(스코어), 옵션 화면

static CImage cPause;


void Set_OS_Img()
{
	// 게임에 맞게 수정할 예정
	if (cPause.IsNull())
		cPause.Load(L"Pause.png");
}

// _Pause
// 일시정지창을 제외한 곳을 누르면 일시정지가 풀리며
	// 메인 화면으로 나가는 버튼이 있다.
void print_OS_Pause(HDC hMemDC, RECT cRect, Master master)
{
	Set_OS_Img();

	TCHAR str[20];
	wsprintf(str, L"일시정지");// 왼쪽위로 출력 
	TextOut(hMemDC, cRect.right / 2, cRect.bottom / 2, str, _tcslen(str));
	int pw = cPause.GetWidth();
	int ph = cPause.GetHeight();
	cPause.Draw(hMemDC, (cRect.right - pw) / 2, (cRect.bottom - ph) / 2, pw, ph, 0, 0, pw, ph);
}
void OS_Pause_LBUTTONDOWN(HWND hWnd, int mx, int my, Master* master, RECT cRect, BOOL* is_pause,int *screen_number,int* main_menu)
{
	int answer;

	// 옵션창 영역에서 위의 34 부분을 포함한 부분을 누르면 옵션 꺼짐 종료를 누르면 겜 종료
	RECT tmp;
	int pw = cPause.GetWidth();
	int ph = cPause.GetHeight();
	tmp.left = (cRect.right - pw) / 2;
	tmp.right = tmp.left+ pw;
	tmp.top = (cRect.bottom - ph) / 2;
	tmp.bottom = tmp.top + ph;
	if (is_in_rect(mx, my, tmp))
		;
	else
		*is_pause = FALSE;

	// 메인으로 돌아갈건지 물어볼 부분
	tmp.left = tmp.right - 215;
	tmp.top += 25;
	tmp.bottom = tmp.top + 35;
	if (is_in_rect(mx, my, tmp))
	{
		answer = MessageBox(hWnd, L"정말로?", L"메인화면으로 돌아가기", MB_YESNO);
		if (answer == IDYES)
		{
			*screen_number = 0;
			*is_pause = FALSE;
			*main_menu = 0;
		}
	}
		
}


// _is_over
// 스코어 화면은 전투 배경이 약간 흐릿해지거나 어두워지고 그 위에 그냥 점수 목록과 합을 출력, 메인화면으로 가는 버튼이 있음