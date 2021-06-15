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
void OS_Pause_LBUTTONDOWN(HWND hWnd, int mx, int my, Master* master, RECT cRect, BOOL* is_pause,int *screen_number,int* main_menu)
{
	int answer;

	// �ɼ�â �������� ���� 34 �κ��� ������ �κ��� ������ �ɼ� ���� ���Ḧ ������ �� ����
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

	// �������� ���ư����� ��� �κ�
	tmp.left = tmp.right - 215;
	tmp.top += 25;
	tmp.bottom = tmp.top + 35;
	if (is_in_rect(mx, my, tmp))
	{
		answer = MessageBox(hWnd, L"������?", L"����ȭ������ ���ư���", MB_YESNO);
		if (answer == IDYES)
		{
			*screen_number = 0;
			*is_pause = FALSE;
			*main_menu = 0;
		}
	}
		
}


// _is_over
// ���ھ� ȭ���� ���� ����� �ణ �帴�����ų� ��ο����� �� ���� �׳� ���� ��ϰ� ���� ���, ����ȭ������ ���� ��ư�� ����