#include "header.h"

// ����, is_over, �ɼ� ȭ��



// _Pause
// �Ͻ�����â�� ������ ���� ������ �Ͻ������� Ǯ����
	// ���� ȭ������ ������ ��ư�� �ִ�.
void print_OS_Pause(HDC hMemDC, RECT cRect, Master master)
{
	TCHAR str[20];
	wsprintf(str, L"�Ͻ�����");
	TextOut(hMemDC, cRect.right / 2, cRect.bottom / 2, str, _tcslen(str));

}
void OS_Pause_LBUTTONDOWN(HWND hWnd, int mx, int my, Master* master, RECT cRect, BOOL* is_pause)
{
	
}


// _is_over
