#include "header.h"

// ����, is_over(���ھ�), �ɼ� ȭ��

static CImage cPause;


void Set_OS_Img()
{
	// ���ӿ� �°� ������ ����
	if (cPause.IsNull())
		cPause.Load(L"Pause.png");
}

// _Pause
// �Ͻ�����â�� ������ ���� ������ �Ͻ������� Ǯ����
	// ���� ȭ������ ������ ��ư�� �ִ�.
void print_OS_Pause(HDC hMemDC, RECT cRect, Master master)
{
	Set_OS_Img();

	TCHAR str[20];
	wsprintf(str, L"�Ͻ�����");// �������� ���
	TextOut(hMemDC, cRect.right / 2, cRect.bottom / 2, str, _tcslen(str));
	int pw = cPause.GetWidth();
	int ph = cPause.GetHeight();
	cPause.Draw(hMemDC, (cRect.right - pw) / 2, (cRect.bottom - ph) / 2, pw, ph, 0, 0, pw, ph);
}
void OS_Pause_LBUTTONDOWN(HWND hWnd, int mx, int my, Master* master, RECT cRect, BOOL* is_pause)
{
	// �ɼ�â �������� ���� 34 �κ��� ������ �κ��� ������ �ɼ� ���� ���Ḧ ������ �� ����
}


// _is_over
// ���ھ� ȭ���� ���� ����� �ణ �帴�����ų� ��ο����� �� ���� �׳� ���� ��ϰ� ���� ���, ����ȭ������ ���� ��ư�� ����