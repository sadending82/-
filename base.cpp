
#include "header.h"

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"2021-1 Windows Programming Term Project";

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;
	g_hInst = hInstance;

	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, WindowWidth, WindowHeight, NULL, (HMENU)NULL, hInstance, NULL);
	// WindowWidth와 WindowHeight는 헤더파일에 적어 두었습니다.
	// 1280 1024로 변경했습니다.

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hDC, hMemDC;
	PAINTSTRUCT ps;

	HBITMAP hCompatibleBit;

	RECT cRect;

	static Master master;
	static int screen_number;
	static int main_menu;//메인 화면의 상태

	static BOOL is_over;
	static BOOL is_pause;

	int answer;
	switch (iMessage) {
	case WM_CREATE:
	{
		screen_number = 2; // 저도 여러가지 실험을 해야하는지라 2번이 되어 있습니다!
		main_menu = 0;
		is_over = FALSE;
		is_pause = FALSE;
		SetTimer(hWnd, 1, 16, NULL);
	}
		break;
	case WM_PAINT:
	{
		hDC = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &cRect);
		hCompatibleBit = CreateCompatibleBitmap(hDC, WindowWidth, WindowHeight);
		hMemDC = CreateCompatibleDC(hDC);
		// 더블 버퍼링을 위한 밑 준비 입니다.
		// WM_PAINT에서 출력해야할 것이 있다면 이 사이에 입력하시면 됩니다.

		//	아래 출력의 경우 각각의 case에 따라서 다른 함수로 만들어 출력하는것도 좋을 것 같습니다.
		switch(screen_number)
		{
		case 0:
			//메인 화면
			Rectangle(hMemDC, 0, 0, cRect.right, cRect.bottom);//메인화면의 배경 출력 - 비트맵 이미지로 대체할것
			switch (main_menu)
			{
			case 0:
				//선택지 화면
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
			// 키보드 1,2,3 과 '차일드 윈도우'등으로 구현.
			/* 차일드 윈도우를 이용할 필요는 없을 듯 합니다 PNG파일로 들고와서 클릭으로 충분히 대체 가능합니다.*/
			break;
		case 1:
			//	in game 화면 - 게임 시작 후 지도 – 1, 2 참고
			//	배경 출력
			//	맵 타일 출력
			break;
		case 2:
			//	전투 화면 - 전투 – 1, 2 참고
			//	전투시 screen_number 값도 같이 바꾸고 전투가 끝나면 다시 1로 바꾼다.
			//	배경 출력
			//	플레이어 적 카드 출력
			//	각종 효과 출력
			//	승리시 보상선택 화면 출력 - 선택시 전투 종료 - 1로 돌아감
			//	패배시 is_over 값 수정

			GamePlay(hMemDC);
			break;
		}
		if (is_over)
		{
			//게임이 끝나면 스코어와 승패여부(마지막 보스 처시치 승리, 어디서든 체력이 0 이하로 내려가면 패배)출력
			//메인 화면으로 돌아간다.
			

		}
		if (is_pause)
		{
			// ESC를 누르면 나오는 화면으로 메인 화면으로 돌아갈 수 있다.
			// 이 상태가 되면 아무런 조작이 불가능해야함 - 키 입력시 is_pause 조건 추가
			/**/
		}

		//--
		RECT rect;
		rect.left = 0;
		rect.top = 0;

		
		// 더블 버퍼링 이후 BitBlt 및 오브젝트 삭제 입니다. 
		BitBlt(hDC, 0, 0, WindowWidth, WindowHeight, hMemDC, 0, 0, SRCCOPY);
		DeleteObject(hCompatibleBit);
		DeleteObject(hMemDC);
		EndPaint(hWnd, &ps);
	}
		break;
	case WM_TIMER:
	{
		switch (wParam)
		{
		default:
			break;
		}
		InvalidateRect(hWnd, NULL, FALSE);
	}

		break;
	case WM_LBUTTONDOWN:
	{
		int mx = LOWORD(lParam);
		int my = HIWORD(lParam);
	}
		break;
	case WM_LBUTTONUP:
	{
		int mx = LOWORD(lParam);
		int my = HIWORD(lParam);
	}
		break;
	case WM_MOUSEMOVE:
	{
		int mx = LOWORD(lParam);
		int my = HIWORD(lParam);
	}
		break;
	case WM_CHAR:
	{
		switch (wParam)
		{
		default:
			break;
		}
	}
		break;
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_ESCAPE:
			switch (screen_number)
			{
			case 0:
				//게임을 종료할건지 묻는 화면 출력
				answer = MessageBox(hWnd, L"정말로?", L"게임 종료", MB_YESNO);
				if (answer == IDYES)
					DestroyWindow(hWnd);
				break;
			case 1:
			case 2:
				if (is_pause)
					is_pause = FALSE;
				else
					is_pause = TRUE;
				break;
			}
			break;
		case '3':
			if(screen_number == 0)
			{
				answer = MessageBox(hWnd, L"정말로?", L"게임 종료", MB_YESNO);
				if (answer == IDYES)
					DestroyWindow(hWnd);
			}
			break;
		}
		if (screen_number == 2 && !is_pause)	//  전투중 키 사용
		{
			if (wParam <= '0' && wParam <= '9')
			{
				//해당하는 카드를 선택 상태로 만든다.
			}
		}
	}
		break;
	case WM_KEYUP:
	{
		switch (wParam)
		{
		default:
			break;
		}
	}
		break;
	case WM_COMMAND:
	{

	}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}


