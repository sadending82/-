
#include "header.h"

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"2021-1 Windows Programming Term Project";

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

/* -*- winmain은 여기서 계속 돌기 때문에, Master, Player 구조체를 사용한 플레이어 데이터 변수는 이곳에 전역으로 설정해 두는 것이 좋을 것 같습니다.*/
/* -*- 다른 소스파일에서 이 변수를 필요로 할 경우에는 함수의 인자로서 소스코드로 들고 가도록 합시다*/

Master master = { 0 };
//Player player = { 0 };

static int count = 0;
static POS card_position = { 0 };
static int screen_number;

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
	HDC hMapDC;
	PAINTSTRUCT ps;

	HBITMAP hCompatibleBit;
	HBITMAP hMapBit;

	HFONT hFont, oldFont;



	static RECT cRect;

	//static Master master;

	static int main_menu;//메인 화면의 상태

	static BOOL is_over;
	static BOOL is_pause;

	static int map_yPos;

	int answer;

	static int room_print_count; // 방 노드 애니메이션용
	static int room_print_count_2; // 방 노드 애니메이션용2

	static POINT cursor;
	switch (iMessage) {

	case WM_CREATE:
	{
		srand((unsigned int)time(NULL));
		screen_number = 0; /* 저도 여러가지 실험을 해야하는지라 2번이 되어 있습니다!*/
		main_menu = 0;
		is_over = FALSE;
		is_pause = FALSE;
		
		SetTimer(hWnd, 1, 16, NULL);

		AddFontResource(L"휴면편지체.TTF");
		
		
		GetClientRect(hWnd, &cRect);
		set_MS_Button(hWnd, cRect, g_hInst);
		Set_IG_Img();
		set_IG_Button(cRect);

		map_yPos = 0;
		cursor.x = cursor.y = 0;

		room_print_count = room_print_count_2 = 0;
	}
		break;

	case WM_PAINT:
	{
		hDC = BeginPaint(hWnd, &ps);
		hCompatibleBit = CreateCompatibleBitmap(hDC, WindowWidth, WindowHeight);
		hMemDC = CreateCompatibleDC(hDC);
		SelectObject(hMemDC, hCompatibleBit); /* 셀렉트 안해서 안됐었습니다 ㅋㅋㅋㅋㅋㅋㅋㅋ */
		//screen_number == 1에서 사용할 DC
		hMapDC = CreateCompatibleDC(hMemDC);
		hMapBit = CreateCompatibleBitmap(hDC, cRect.right * 3 / 5, cRect.bottom * 2);
		SelectObject(hMapDC, hMapBit);
		SetBkMode(hMemDC, 1);
		SetTextColor(hMemDC, RGB(255, 255, 255));
		hFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, L"궁서");
		oldFont = (HFONT)SelectObject(hMemDC, hFont);

		// 더블 버퍼링을 위한 밑 준비 입니다.
		// WM_PAINT에서 출력해야할 것이 있다면 이 사이에 입력하시면 됩니다.

		//	아래 출력의 경우 각각의 case에 따라서 다른 함수로 만들어 출력하는것도 좋을 것 같습니다.
		// 이미지 불러오기 함수들
		Set_IG_Img();


		switch(screen_number)
		{
		case 0:
			//메인 화면
			print_MS(hMemDC,cRect,main_menu);
			break;
		case 1:
			//	in game 화면 - 게임 시작 후 지도 – 1, 2 참고
			//	배경 출력
			//	맵 타일 출력
			print_IG(hMemDC, hMapDC, cRect, master, map_yPos, room_print_count);
			print_Map(hMemDC, hMapDC, cRect, master, map_yPos, room_print_count);
			print_Status_Bar(hMemDC, cRect, master);
			break;
		case 2:
			//	전투 화면 - 전투 – 1, 2 참고
			//	전투시 screen_number 값도 같이 바꾸고 전투가 끝나면 다시 1로 바꾼다.
			//	배경 출력
			//	플레이어와 플레이어손의 카드, 적 출력
			//	각종 효과 출력
			//	승리시 보상선택 화면 출력 - 선택시 전투 종료 - 1로 돌아감
			//	패배시 is_over 값 수정

			// screen_number == 1인 상태에서 맵 타일중 전투인 경우를 선택하면 해당 스테이지에 랜덤한 몬스터를 지정해서 전투를 진행합니다.
			// 몬스터가 정해지면 screen_number = 2;를 하고 화면에 위 순서대로 출력해야할겁니다.
			// 전투가 끝나면 ==(플레이어의 체력or 몬스터의 체력 이 0이되면) 다시 1로 돌아갑니다. 위의 설명처럼 패배의 경우는 아래의 게임 오버 화면이 나와야합니다.
			DisplayGame(hWnd, hMemDC, &master.player);
			print_Map(hMemDC, hMapDC, cRect, master, map_yPos, room_print_count);
			print_Status_Bar(hMemDC, cRect, master);


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
			print_OS_Pause(hMemDC, cRect, master);
		}

		//--
		RECT rect;
		rect.left = 0;
		rect.top = 0;

		
		// 더블 버퍼링 이후 BitBlt 및 오브젝트 삭제 입니다. 
		BitBlt(hDC, 0, 0, WindowWidth, WindowHeight, hMemDC, 0, 0, SRCCOPY);
		SelectObject(hMemDC, oldFont);
		DeleteObject(hFont);
		DeleteObject(hCompatibleBit);
		DeleteDC(hMemDC);
		DeleteObject(hMapBit);
		DeleteDC(hMapDC);
		EndPaint(hWnd, &ps);
	}
		break;
	case WM_TIMER:
	{
		switch (wParam)
		{
		case Base_Timer:
		{
			if(!is_pause&&screen_number == -1&& screen_number == -2)
				IG_Timer(cursor, &map_yPos, cRect, &master);

			room_print_count_2++;
			if (room_print_count_2 % 10 == 0)// 속도 배율
				room_print_count++;
			if (room_print_count == 4)
				room_print_count = 0;

			InvalidateRect(hWnd, NULL, FALSE);
		}
			break;
		case Card_Timer:
		{
			int num = 0;
			for (int i = 0; i < 50; ++i)
			{
				if (master.player.deck.card[i].is_Active)
				{
					if (master.player.deck.card[i].is_Moving)
					{
						CardAnimToXy(hWnd, card_position.x + (num * 150), card_position.y, 10, &(master.player.deck.card[i]), i);
						num++;
					}
				}
			}
		}
		case 16:
		{

		}
			break;
		case Print_Timer:
		{
			int printNum = GetPrint();
			switch (printNum)
			{
			case 1:
				SetMyTurnPrint(hWnd);
				break;
			case 2:
				SetEnemyTurnPrint(hWnd);
				break;
			default:
				break;
			}
		}
		break;
		case TurnDelay_Timer:
		{
			KillTimer(hWnd, 25);
			GetTurnChangeTimer(hWnd, &master.player);

		}
			break;
		case DmgPrint_Timer:
		{
			int printNum = GetDmgPrint();

			switch (printNum)
			{
			case 1:
				SetMyDmgPrint(hWnd);
				break;
			case 2:
				SetEnemyDmgPrint(hWnd);
				break;
			default:
				break;
			}
		}
			break;
		default:
			break;
		}

	}

		break;
	case WM_LBUTTONDOWN:
	{
		int mx = LOWORD(lParam);
		int my = HIWORD(lParam);
		switch (screen_number)
		{
		case 0:
			MS_LBUTTONDOWN(hWnd, mx, my, &main_menu, &screen_number, &master.player, &master, cRect,&map_yPos);
			break;
		case 1:
			if (!is_pause)
			{
				IG_LBUTTONDOWN(hWnd, mx, my, &master, cRect, &is_pause, &map_yPos, &screen_number);
				Pause_LBUTTONDOWN(mx, my, cRect, &is_pause);
			}
			else
				OS_Pause_LBUTTONDOWN(hWnd, mx, my, &master, cRect, &is_pause, &screen_number, &main_menu);
			break;
		case 2:
			if (!is_pause)
			{
				card_position = GP_LBUTTONDOWN(hWnd, mx, my, &master.player, card_position.x, card_position.y);
				Pause_LBUTTONDOWN(mx, my, cRect, &is_pause);
			}
			else
				OS_Pause_LBUTTONDOWN(hWnd, mx, my, &master, cRect, &is_pause, &screen_number, &main_menu);
			break;
		} 
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
		switch (screen_number)
		{
		case 0:
			MS_MOUSEMOVE(mx, my, main_menu);
			break;
		case 1:

			IG_MOUSEMOVE(mx, my, &cursor, master, cRect);
			Map_MOUSEMOVE(mx, my, &cursor);
			break;
		case 2:
			GP_MOUSEMOVE(mx, my, &master.player);
			Map_MOUSEMOVE(mx, my, &cursor);
			break;
		}
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
				switch (main_menu)
				{
				case 0:
					answer = MessageBox(hWnd, L"정말로?", L"게임 종료", MB_YESNO);
					if (answer == IDYES)
						DestroyWindow(hWnd);
					break;
				case 1:
					main_menu = 0;
					break;
				}
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
		case '1':
			switch (screen_number)
			{
			case 0:
				switch (main_menu)
				{
				case 0:
					main_menu = 1;
					break;
				case 1:
					// 0번째 캐릭터로 게임 시작
					Set_player(0, &master);
					make_map(&master, cRect);
					screen_number = 1;
					master.screen_numbers.In_Game_Screen_num = Out_of_game;
					master.booleans.Is_print_map = TRUE;
					map_yPos = 0;
					break;
				case 2:
					//아래에서 처리
					break;
				}
				break;
			case 1:
				// 커런트 룸의 0번 노드 선택
				break;
			}
			break;
		case '2':
			switch (screen_number)
			{
			case 0:
				switch (main_menu)
				{
				case 0:
					MessageBox(hWnd, L"미구현", L"백과사전", MB_OK);
					break;
				case 1:
					Set_player(1, &master);
					make_map(&master, cRect);
					screen_number = 1;
					master.screen_numbers.In_Game_Screen_num = Out_of_game;
					master.booleans.Is_print_map = TRUE;
					map_yPos = 0;
					break;
				}
				break;
			case 1:
				// 커런트 룸의 1번 노드 선택
				break;
			}
			break;
		case '3':
			switch(screen_number)
			{
			case 0:
				switch (main_menu)
				{
				case 0:
					answer = MessageBox(hWnd, L"정말로?", L"게임 종료", MB_YESNO);
					if (answer == IDYES)
						DestroyWindow(hWnd);
					break;
				case 1:
					break;
				}
				break;
			case 1:
				// 커런트 룸의 2번 노드 선택
				break;
			}
			break;
		case 'E':
		case 'e':
			switch (screen_number)
			{
			case 2:
				// 턴 종료
				GP_E(hWnd, &(master.player));
				break;
			}
			break;
		case 'm':
		case 'M':
			switch (screen_number)
			{
			case 1:
			case 2:
				if (master.screen_numbers.In_Game_Screen_num != Out_of_game)
				{
					if (master.booleans.Is_print_map)
						master.booleans.Is_print_map = FALSE;
					else
						master.booleans.Is_print_map = TRUE;
				}
				break;
			}
			break;
		case VK_UP:
			if (screen_number == 1)
			{
				if (map_yPos > -30)
				{
					map_yPos = map_yPos - 30;
					if (master.stage.map.Boss_Room != NULL)
					{
						for (int i = 0; i < 13; i++)
						{
							OffsetRect(&master.stage.map.All_room[i]->rect, 0, 30);
						}
						OffsetRect(&master.stage.map.Boss_Room->rect, 0, 30);
					}
				}
				if (map_yPos < -30)
					map_yPos = -30;
			}
			break;
		case VK_DOWN:
			if (screen_number == 1)
			{
				if (map_yPos < cRect.bottom + 30)
				{
					map_yPos = map_yPos + 30;
					if (master.stage.map.Boss_Room != NULL)
					{
						for (int i = 0; i < 13; i++)
						{
							OffsetRect(&master.stage.map.All_room[i]->rect, 0, -30);
						}
						OffsetRect(&master.stage.map.Boss_Room->rect, 0, -30);
					}
				}
				if (map_yPos > cRect.bottom + 30)
					map_yPos = cRect.bottom + 30;
			}
			break;
		}
		if (screen_number == 2 && !is_pause)	//  전투중 키 사용
		{
			if (wParam >= '0' && wParam <= '9')
			{
				//해당하는 카드를 선택 상태로 만든다.
				GP_NUMBER(hWnd, &(master.player), wParam);
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


POS* GetPosPointer()
{
	return &(card_position);
}

void ChangeScreenNumber(int num)
{
	screen_number = num;
}

Master* GetMaster()
{
	return &master;
}

