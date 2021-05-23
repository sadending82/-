#include "header.cpp"

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
	// 일단 시작은 1200 800으로 시작하겠습니다.

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}
// 주석변경
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{

	HDC hDC, hMemDC;
	PAINTSTRUCT ps;

	HBITMAP hCompatibleBit;

	RECT cRect;

	switch (iMessage) {
	case WM_CREATE:
	{

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
		//--


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
		default:
			break;
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

