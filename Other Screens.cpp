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
void OS_Pause_LBUTTONDOWN(HWND hWnd, int mx, int my, Master* master, RECT cRect, BOOL* is_pause)
{
	// 옵션창 영역에서 위의 34 부분을 포함한 부분을 누르면 옵션 꺼짐 종료를 누르면 겜 종료
}


// _is_over
// 스코어 화면은 전투 배경이 약간 흐릿해지거나 어두워지고 그 위에 그냥 점수 목록과 합을 출력, 메인화면으로 가는 버튼이 있음