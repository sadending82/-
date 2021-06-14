#include "header.h"

// 퍼즈, is_over, 옵션 화면



// _Pause
// 일시정지창을 제외한 곳을 누르면 일시정지가 풀리며
	// 메인 화면으로 나가는 버튼이 있다.
void print_OS_Pause(HDC hMemDC, RECT cRect, Master master)
{
	TCHAR str[20];
	wsprintf(str, L"일시정지");
	TextOut(hMemDC, cRect.right / 2, cRect.bottom / 2, str, _tcslen(str));

}
void OS_Pause_LBUTTONDOWN(HWND hWnd, int mx, int my, Master* master, RECT cRect, BOOL* is_pause)
{
	
}


// _is_over
