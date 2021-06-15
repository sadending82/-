// 헤더파일 입니다.
// 여기에 전역변수나 base가 아닌 다른 소스코드에서 생성한 함수의 반환형 등을 입력해 두면 될것 같습니다.

// -*- 표시가 된것은 김혁동이 작성한 것입니다.

#ifndef __HEADER_H__
#define __HEADER_H__
#include <windows.h>		
#include <tchar.h>
#include <time.h>
#include <atlimage.h>

#define WindowWidth 1280 // WindowWidth 윈도우 폭
#define WindowHeight 860 // WindowHeight 윈도우 높이


#define Maximum_number_of_cards_on_deck 50
#define MNCD Maximum_number_of_cards_on_deck

#define Default_number_of_cards_on_deck 10
#define DNCD Default_number_of_cards_on_deck

//#define Default_number_of_rooms 10
//#define DNR Default_number_of_rooms
#define Default_number_of_floors 8
#define DNF Default_number_of_floors

//Maximum number of rooms per floor
#define Maximum_number_of_rooms_of_floor 3
#define MNRF Maximum_number_of_rooms_of_floor


#define Maximum_number_of_potions_on_player 3
#define MNPP Maximum_number_of_potions_on_player

#define Number_of_buffs 20
#define Number_of_relics 10

// 각각의 객체를 늘일때마다 바꿔줘야합니다.
#define Number_of_characters 1

// 스테이지 1의 몬스터의 종류입니다. 
#define Number_of_Regular_Monsters_in_Stage_1 1
#define RMS1 Number_of_Regular_Monsters_in_Stage_1

#define Number_of_Elite_Monsters_in_Stage_1 0
#define EMS1 Number_of_Elite_Monsters_in_Stage_1

#define Number_of_Boss_Monsters_in_Stage_1 0
#define BMS1 Number_of_Boss_Monsters_in_Stage_1

//In Game 관련

#define Out_of_game			-1
//Room 관련

#define Room_Start			-1
#define Room_Basic_Enemy	0
#define Room_Elite_Enemy	1
#define Room_Rest			2
#define Room_Relics			3
#define Room_Merchant		4
#define Room_Random			5
#define Room_Boss			6
#define Number_of_Room_Types 6// 보스룸 제외

#define Weight_of_Room_Basic_Enemy 10
#define Weight_of_Room_Elite_Enemy 1
#define Weight_of_Room_Rest 3
#define Weight_of_Room_Relics 1
#define Weight_of_Room_Random 3
#define Weight_of_Room_Merchant 2

//Monster 관련

#define Monster_Type_Basic 0
#define Monster_Type_Elite 1
#define Monster_Type_Boss 2

//Card 관련

#define Card_Occu_ALL -1
#define Card_Occu_Fisrt 0
#define Card_Type_None 0
#define Card_Type_Attack 1
#define Card_Type_Deffence 2

//Player 관련

#define State_Idle 0
#define State_Attack 1
#define State_Deffence 2
#define State_Attacked 3
#define State_Dead 4

//Timer 관련

#define Base_Timer 1
#define Player_Timer 2
#define Card_Timer 10
#define Print_Timer 17
#define TurnDelay_Timer 25
#define DmgPrint_Timer 30

// 스테이지 2를 만들때 아래도 추가해주세요.
//...
// 객체 개수 선언 끝

typedef struct position{
	int x;
	int y;
}POS;

/*
포지션 용 구조체가 필요해서 추가함.
*/

typedef struct room {
	int room_type;
	RECT rect;
	struct room* next[MNRF];
}Room;
/*
* 방
0 : 기본 적
1 : 엘리트 적
2 : 휴식
3 : 유물(상자)
4 : 랜덤 이벤트
5 : 상인
6 : 보스 -- 무조건 마지막에 나옴

// -*- 이런 부분도 헤더파일로 추가해 주시면 제가 볼 때 코드를 이해하기 편합니다!
// -*- 일단은 제가 알 수 있는 부분에 대해서는 임의적으로 추가해 두었습니다.
// -*- 그리고 그래프 구조로 구현하는 것은 아주 좋은 방법인듯 합니다.
// -*- 대신, 맵을 그릴 때 어떤식으로 구현할지 고민을 해봐야 할 것 같습니다.
// -*- 아마 그래프 형식이 될 것 같은데 랜덤 그래프는 너무 어려우니까 무언가 방법을 찾는게 좋을 지도 모르겠네요!

*/
typedef struct {
	Room** All_room;
	Room* Current_Room;
	Room* Boss_Room;
	Room Start_Room;
	int num_of_rooms;
}Map;


typedef struct {
	int stage_num;
	int floor_num;
	Map map;
}Stage;

/*
스테이지별로 다른 종류의 몬스터 생성
각각 고유의 스프라이트
...
*/
typedef struct {
	int Max_hp;			// 최대 체력
	int Current_hp;		// 현재 체력
	int Shield_figure;	// 방어도
}HP;


typedef struct {
	int x;
	int stage_num;
	int type; // 0 : 일반, 1 : 엘리트, 2 : 보스
	int ob_num; // -*- 이건 무엇인가요?
	int animation_state;
	int animation_num;
	int maxDmg;
	int minDmg;
	BOOL is_Active;
	HP hp;

}Monster;
/*
ob_num 는 몬스터 고유 번호로 사용할 변수입니다
 예를 들어 (3,2,0) 은 3스테이지의 0번 보스 입니다
 이 값에 따라서 다른 이미지를 출력하게 만들거나 생성을 할 때 체력을 정하고(지정된 범위에서 랜덤 or 그냥 고정)
 몬스터의 행동과 패턴이 정해집니다.

 몬스터는 이번 턴에 할 행동이 무엇인지 머리 위에 표시합니다.

ㅌ아래는 예시입니다.
속성					이름				가능 행동과 (패턴)
0, 0, 0 hp = 10 ~ 12	산성 슬라임 		(평상시)공격 : dmg 4~6,	디버프시전 : 가하는 피해 감소 1턴
0, 0, 1 hp = 10 ~ 12	강철 슬라임			(평상시)공격 : dmg 4~6,	디버프시전 : 얻는 방어도 감소 1턴
0, 1, 0 hp = 20 ~ 24	큰 산성 슬라임		(평상시)공격 : dmg 6~8,	디버프시전 : 가하는 피해 감소 2턴, (체력 1/2 이하시) 자신의 현재 체력을 가진 산성 슬라임 2마리 생성
0, 1, 1 hp = 20 ~ 24	큰 강철 슬라임		(평상시)공격 : dmg 6~8,	디버프시전 : 얻는 방어도 감소 2턴, (체력 1/2 이하시) 자신의 현재 체력을 가진 강철 슬라임 2마리 생성
0, 2, 0 hp = 40 ~ 48	많이 큰 슬라임		(평상시)(턴 1, 2)행동 없음,(턴 3)공격 : dmg 24~26, (체력 1/2 이하시) 자신의 현재 체력을 가진 큰 강철 슬라임과 큰 산성 생성
*/

typedef struct {
	int occupation;
	int type; // 0 : 없음, 1 : 공격, 2 : 방어
	int number;
	int left;
	int right;
	int top;
	int bottom;
	int cost;
	BOOL is_enhanced;//기본값 FALSE
	BOOL is_Active;
	BOOL is_inhand;
	BOOL is_Moving;
}Card;
/*
* 카드
* number 값에 따라서 다른 이미지로 출력
occupation, type, number
ALL, 1, 0 = 모든 직업의 0번째 공격 카드 = 6 + 힘의 데미지		기본 공격 카드(0번째 직업의 0번째 공격카드)		힘과 민첩은 버프입니다. 아래 버프 목록 참고
ALL, 2, 0 = 모든 직업의 0번째 수비 카드 = 6 + 민첩의 방어도		기본 수비 카드(0번째 직업의 0번째 수비카드)
0, 1, 1 = 0번 직업의 1번째 공격카드 = 8 + 공격력으로 전체 공격
...

// -*- ALL의 경우는 -1로 설정해 두겠습니다.
// -*- 그리고 이런 부분에 대해서는 저는 잘 모르기 때문에 전부 작성하거나, 카드나 유물 리스트 같은 것을 정리한 텍스트 파일을 리소스 파일에 추가해 주시면 감사하겠습니다.

//	ALL은 모든 직업들에 해당하는 경우라 모든 occupation 값 이라고 생각하시면 됩니다.
//	예를 들어 직업이 3종류가 있다면 (0,1,0) 과 (1,1,0) 과 (2,1,0)은 전부 위에 있는 기능을 하는 같은 카드입니다. 하지만 이미지는 다를 수 있습니다.

*/
typedef struct {
	Card card[MNCD];
	int num_of_cards; // 기본값 DNCD
}Deck;
typedef struct {

}Potion;
/*

...
*/
typedef struct {

}Relic;
/*

...
*/
typedef struct {
	int num;
	int duration; // 일부만 가지고 있음
	BOOL haveDuration; // 일부만 가지고 있다면 가지고 있는지 없는지를 판단하는 BOOL 함수가 필요합니다.
}Buff;
/*

* 버프는 플레이어의 buffs의 주소에 따라서 역할이 정해져있습니다. num 값이 버프의 크기입니다
* 힘, 민첩의 경우 num만큼 증가하며
* 10, 11, 12의 경우 duration이 존재하고 그 값이 0 이상이면 효과를 발휘합니다. (num 만큼 증가 감소 합니다.)
* duration은 턴이 지날때마다 1씩 줄어듭니다.따라서 해당 버프가 적용되는 남은 턴 수를 의미합니다.
* 
* 버프
0 : 힘 - 가하는 피해 증가
1 : 민첩 - 얻는 방어도 증가
...

10 : 가하는 피해 감소
11 : 얻는 방어도 감소
12 : 받는 피해 증가
...

// -*- 전부다 작성해 주시면 감사하겠습니다!

*/
typedef struct {
	Potion potions[MNPP];
	Relic relics[Number_of_relics]; // 소지 가능 제한 없음
	Buff buffs[Number_of_buffs];	// 소지 가능 제한 없음
	int num_of_potions;
	int num_of_relics;
	int num_of_buffs;
}Item;


typedef struct {
	int x; // 전투 화면에 나왔을 때의 위치. y는 고정인지 아닌지 모르지만 일단은 고정인 채로 구현해 봄.
	HP hp;
	int money;
	int occupation;
	int animation_num; // 어떤 애니메이션을 출력할 것인가
	int animation_state; // 어떤 애니메이션을 재생해야하나?
	int selectedCard; // 선택된 카드
	int amount_of_card_draw; // 카드 드로우 양
	int cost;
	Deck deck;
	Item item;
	BOOL isCharacterActive; // 화면에 캐릭터를 출력할 것인지 아닌지 확인하는 변수 (전투 화면에 출력할 때만 TRUE)
	BOOL isDragCard; // 카드 드래그 중인지 아닌지 확인하는 변수
	BOOL isMyTurn; // 자신의 턴인지 확인하는 변수
}Player;

/*
캐릭터 애니메이션 관련입니다.

animation_state가
0 : State_Idle
1 : State_Attack
2 : State_Deffence

정도로 설정하고 #define으로 설정해 두겠습니다.
*/
// 기본 상태, 공격카드 사용 모션, 수비 카드 사용 모션, 피격시 모션 등이 있으면 될 것 같습니다.

//- slay the spire에서게임을 시작하면 그 시점의 시드값이 정해져서 세이브 로드를 해도 모든 랜덤의 결과가 달라지지 않습니다. 그를 위한 값 입니다. 
//	다른 게임들에도 있는 시드를 입력하고 시작하는 기능도 있기는 합니다.
//	만약 구현할거라면 필요하고 아니면 필요 없습니다.
//	이름이 부적절해보여서 수정합니다.
//	값은 게임을 실행하고 케릭터를 설정할때 정해집니다.
typedef struct {
	// 정리할때 각종BOOL 변수를 여기에 추가
	BOOL Is_print_map;
}Booleans;
/*
Is_print_map == TRUE이면 지도를 출력한다.

*/
typedef struct {
	// 정리할때 각종 화면 구분용 변수를 여기에 추가
	int In_Game_Screen_num;
}Screen_Numbers;
/*
In_Game_Screen_num
nomal			0
Rest			2
Relics			3
Merchant		4
Random			5
*/
typedef struct {
	Player player;
	int game_seed; // -*- 이것도 무엇인가요? 
	Stage stage;
	Booleans booleans;	//	나중에 윈도으프로시져 정리용
	Screen_Numbers screen_numbers;
}Master;


// -*- base에서 가지고 와야할 정보가 있어 Get 함수를 만들겠습니다.

POS* GetPosPointer();
void ChangeScreenNumber(int num);

// -*- 아래부터는 GamePlay에 관한 함수입니다.
void DisplayGame(HWND hWnd, HDC hDC, Player* player);
void SetCard(Player* player);
POS GP_LBUTTONDOWN(HWND hWnd, int x, int y, Player* player, int Lx, int Ly);

void CardAnimToXy(HWND hWnd, int x, int y, int animNum, Card* card, int cardNum);
void StartStage(HWND hWnd, Player* player, int monsterNum);
void GP_MOUSEMOVE(int, int, Player*);
void GetTurnChangeTimer(HWND hWnd, Player* player);
void SetMyTurnPrint(HWND hWnd);
void SetEnemyTurnPrint(HWND hWnd);
int GetPrint();
int GetDmgPrint();


// From Main Screen


void set_MS_Button(HWND hWnd, RECT cRect, HINSTANCE g_hInst);
void print_MS(HDC hMemDC, RECT cRect, int main_menu);
void MS_LBUTTONDOWN(HWND hWnd, int mx, int my, int* main_menu, int* screen_number, Player* player, Master* master, RECT cRect);
void MS_MOUSEMOVE(int mx, int my, int main_menu);
void Set_MS_Img();
void MS_MENU_1(HWND hWnd, int answer, int* screen_number);// 현재 비어잇음
void Set_player(int occupation, Master* master);
void SetMyDmgPrint(HWND hWnd);
void SetEnemyDmgPrint(HWND hWnd);

// From In Game

void Set_IG_Img(); 
void Set_IG_POINT(RECT cRect);
void print_IG(HDC hMemDC, HDC hMapDC, RECT cRect, Master master, int map_yPos, int room_print_count);
void make_random_map(Master master);
void make_map(Master* master, RECT cRect);
void print_room(HDC hMapDC, Master master, RECT cRect, int room_print_count);
void IG_MOUSEMOVE(int mx, int my, POINT* cursor);
void IG_Timer(POINT cursor, int* map_yPos, RECT cRect, Master* master);
void IG_LBUTTONDOWN(HWND hWnd, int mx, int my, Master* master, RECT cRect, BOOL* is_pause, int* map_yPos, int* screen_number);
void print_Status_Bar(HDC hMemDC, RECT cRect, Master master);

void Event_Rest(HWND hWnd, int mx, int my, Master* master, RECT cRect, BOOL* is_pause);


void print_OS_Pause(HDC hMemDC, RECT cRect, Master master);
void OS_Pause_LBUTTONDOWN(HWND hWnd, int mx, int my, Master* master, RECT cRect, BOOL* is_pause, int* screen_number, int* main_menu);


// 많이 사용하는 함수
void print_button(HDC hDC, BOOL is_on, CImage* cButton, CImage* cButton_, RECT rButton);
BOOL is_in_rect(int x, int y, RECT rect);


#endif