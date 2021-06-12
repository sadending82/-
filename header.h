// ������� �Դϴ�.
// ���⿡ ���������� base�� �ƴ� �ٸ� �ҽ��ڵ忡�� ������ �Լ��� ��ȯ�� ���� �Է��� �θ� �ɰ� �����ϴ�.

// -*- ǥ�ð� �Ȱ��� �������� �ۼ��� ���Դϴ�.

#ifndef __HEADER_H__
#define __HEADER_H__
#include <windows.h>		
#include <tchar.h>
#include <time.h>
#include <atlimage.h>

#define WindowWidth 1280 // WindowWidth ������ ��
#define WindowHeight 860 // WindowHeight ������ ����


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

// ������ ��ü�� ���϶����� �ٲ�����մϴ�.
#define Number_of_characters 1

// �������� 1�� ������ �����Դϴ�. 
#define Number_of_Regular_Monsters_in_Stage_1 1
#define RMS1 Number_of_Regular_Monsters_in_Stage_1

#define Number_of_Elite_Monsters_in_Stage_1 0
#define EMS1 Number_of_Elite_Monsters_in_Stage_1

#define Number_of_Boss_Monsters_in_Stage_1 0
#define BMS1 Number_of_Boss_Monsters_in_Stage_1

//Room ����

#define Room_Start -1
#define Room_Basic_Enemy 0
#define Room_Elite_Enemy 1
#define Room_Rest 2
#define Room_Relics 3
#define Room_Random 4
#define Room_Merchant 5
#define Room_Boss 6
#define Number_of_Room_Types 6// ������ ����

#define Weight_of_Room_Basic_Enemy 10
#define Weight_of_Room_Elite_Enemy 1
#define Weight_of_Room_Rest 3
#define Weight_of_Room_Relics 1
#define Weight_of_Room_Random 3
#define Weight_of_Room_Merchant 2

//Monster ����

#define Monster_Type_Basic 0
#define Monster_Type_Elite 1
#define Monster_Type_Boss 2

//Card ����

#define Card_Occu_ALL -1
#define Card_Occu_Fisrt 0
#define Card_Type_None 0
#define Card_Type_Attack 1
#define Card_Type_Deffence 2

//Player ����

#define State_Idle 0
#define State_Attack 1
#define State_Deffence 2
#define State_Attacked 3

//Timer ����

#define Base_Timer 1
#define Player_Timer 2
#define Card_Timer 10

// �������� 2�� ���鶧 �Ʒ��� �߰����ּ���.
//...
// ��ü ���� ���� ��

typedef struct position{
	int x;
	int y;
}POS;

/*
������ �� ����ü�� �ʿ��ؼ� �߰���.
*/

typedef struct room {
	int room_type;
	RECT rect;
	struct room* next1[MNRF];
}Room;
/*
* ��
0 : �⺻ ��
1 : ����Ʈ ��
2 : �޽�
3 : ����(����)
4 : ���� �̺�Ʈ
5 : ����
6 : ���� -- ������ �������� ����

// -*- �̷� �κе� ������Ϸ� �߰��� �ֽø� ���� �� �� �ڵ带 �����ϱ� ���մϴ�!
// -*- �ϴ��� ���� �� �� �ִ� �κп� ���ؼ��� ���������� �߰��� �ξ����ϴ�.
// -*- �׸��� �׷��� ������ �����ϴ� ���� ���� ���� ����ε� �մϴ�.
// -*- ���, ���� �׸� �� ������� �������� ������ �غ��� �� �� �����ϴ�.
// -*- �Ƹ� �׷��� ������ �� �� ������ ���� �׷����� �ʹ� �����ϱ� ���� ����� ã�°� ���� ���� �𸣰ڳ׿�!

*/
typedef struct {
	//Room** All_room;
	//Room* Current_Room;
	//Room* Boss_Room;
	Room Start_Room;
	int num_of_rooms;
}Map;


typedef struct {
	int stage_num;
	Map map;
}Stage;

/*
������������ �ٸ� ������ ���� ����
���� ������ ��������Ʈ
...
*/


typedef struct {
	int stage_num;
	int type; // 0 : �Ϲ�, 1 : ����Ʈ, 2 : ����
	int ob_num; // -*- �̰� �����ΰ���?
	int hp;
}Monster;
/*
ob_num �� ���� ���� ��ȣ�� ����� �����Դϴ�
 ���� ��� (3,2,0) �� 3���������� 0�� ���� �Դϴ�
 �� ���� ���� �ٸ� �̹����� ����ϰ� ����ų� ������ �� �� ü���� ���ϰ�(������ �������� ���� or �׳� ����)
 ������ �ൿ�� ������ �������ϴ�.

 ���ʹ� �̹� �Ͽ� �� �ൿ�� �������� �Ӹ� ���� ǥ���մϴ�.

���Ʒ��� �����Դϴ�.
�Ӽ�					�̸�				���� �ൿ�� (����)
0, 0, 0 hp = 10 ~ 12	�꼺 ������ 		(����)���� : dmg 4~6,	��������� : ���ϴ� ���� ���� 1��
0, 0, 1 hp = 10 ~ 12	��ö ������			(����)���� : dmg 4~6,	��������� : ��� �� ���� 1��
0, 1, 0 hp = 20 ~ 24	ū �꼺 ������		(����)���� : dmg 6~8,	��������� : ���ϴ� ���� ���� 2��, (ü�� 1/2 ���Ͻ�) �ڽ��� ���� ü���� ���� �꼺 ������ 2���� ����
0, 1, 1 hp = 20 ~ 24	ū ��ö ������		(����)���� : dmg 6~8,	��������� : ��� �� ���� 2��, (ü�� 1/2 ���Ͻ�) �ڽ��� ���� ü���� ���� ��ö ������ 2���� ����
0, 2, 0 hp = 40 ~ 48	���� ū ������		(����)(�� 1, 2)�ൿ ����,(�� 3)���� : dmg 24~26, (ü�� 1/2 ���Ͻ�) �ڽ��� ���� ü���� ���� ū ��ö �����Ӱ� ū �꼺 ����
*/

typedef struct {
	int occupation;
	int type; // 0 : ����, 1 : ����, 2 : ���
	int number;
	int left;
	int right;
	int top;
	int bottom;
	BOOL is_enhanced;//�⺻�� FALSE
	BOOL is_Active;
	BOOL is_inhand;
}Card;
/*
* ī��
* number ���� ���� �ٸ� �̹����� ���
occupation, type, number
ALL, 1, 0 = ��� ������ 0��° ���� ī�� = 6 + ���� ������		�⺻ ���� ī��(0��° ������ 0��° ����ī��)		���� ��ø�� �����Դϴ�. �Ʒ� ���� ��� ����
ALL, 2, 0 = ��� ������ 0��° ���� ī�� = 6 + ��ø�� ��		�⺻ ���� ī��(0��° ������ 0��° ����ī��)
0, 1, 1 = 0�� ������ 1��° ����ī�� = 8 + ���ݷ����� ��ü ����
...

// -*- ALL�� ���� -1�� ������ �ΰڽ��ϴ�.
// -*- �׸��� �̷� �κп� ���ؼ��� ���� �� �𸣱� ������ ���� �ۼ��ϰų�, ī�峪 ���� ����Ʈ ���� ���� ������ �ؽ�Ʈ ������ ���ҽ� ���Ͽ� �߰��� �ֽø� �����ϰڽ��ϴ�.

//	ALL�� ��� �����鿡 �ش��ϴ� ���� ��� occupation �� �̶�� �����Ͻø� �˴ϴ�.
//	���� ��� ������ 3������ �ִٸ� (0,1,0) �� (1,1,0) �� (2,1,0)�� ���� ���� �ִ� ����� �ϴ� ���� ī���Դϴ�. ������ �̹����� �ٸ� �� �ֽ��ϴ�.

*/
typedef struct {
	Card card[MNCD];
	int num_of_cards; // �⺻�� DNCD
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
	int duration; // �Ϻθ� ������ ����
	BOOL haveDuration; // �Ϻθ� ������ �ִٸ� ������ �ִ��� �������� �Ǵ��ϴ� BOOL �Լ��� �ʿ��մϴ�.
}Buff;
/*

* ������ �÷��̾��� buffs�� �ּҿ� ���� ������ �������ֽ��ϴ�. num ���� ������ ũ���Դϴ�
* ��, ��ø�� ��� num��ŭ �����ϸ�
* 10, 11, 12�� ��� duration�� �����ϰ� �� ���� 0 �̻��̸� ȿ���� �����մϴ�. (num ��ŭ ���� ���� �մϴ�.)
* duration�� ���� ���������� 1�� �پ��ϴ�.���� �ش� ������ ����Ǵ� ���� �� ���� �ǹ��մϴ�.
* 
* ����
0 : �� - ���ϴ� ���� ����
1 : ��ø - ��� �� ����
...

10 : ���ϴ� ���� ����
11 : ��� �� ����
12 : �޴� ���� ����
...

// -*- ���δ� �ۼ��� �ֽø� �����ϰڽ��ϴ�!

*/
typedef struct {
	Potion potions[MNPP];
	Relic relics[Number_of_relics]; // ���� ���� ���� ����
	Buff buffs[Number_of_buffs];	// ���� ���� ���� ����
	int num_of_potions;
	int num_of_relics;
	int num_of_buffs;
}Item;

typedef struct {
	int x; // ���� ȭ�鿡 ������ ���� ��ġ. y�� �������� �ƴ��� ������ �ϴ��� ������ ä�� ������ ��.
	int hp;
	int money;
	int occupation;
	int animation_num; // � �ִϸ��̼��� ����� ���ΰ�
	int animation_state; // � �ִϸ��̼��� ����ؾ��ϳ�?
	int selectedCard; // ���õ� ī��
	int amount_of_card_draw; // ī�� ��ο� ��
	Deck deck;
	Item item;
	BOOL isCharacterActive; // ȭ�鿡 ĳ���͸� ����� ������ �ƴ��� Ȯ���ϴ� ���� (���� ȭ�鿡 ����� ���� TRUE)
	BOOL isDragCard; // ī�� �巡�� ������ �ƴ��� Ȯ���ϴ� ����
	BOOL isMyTurn; // �ڽ��� ������ Ȯ���ϴ� ����
}Player;

/*
ĳ���� �ִϸ��̼� �����Դϴ�.

animation_state��
0 : State_Idle
1 : State_Attack
2 : State_Deffence

������ �����ϰ� #define���� ������ �ΰڽ��ϴ�.
*/
// �⺻ ����, ����ī�� ��� ���, ���� ī�� ��� ���, �ǰݽ� ��� ���� ������ �� �� �����ϴ�.

//- slay the spire���������� �����ϸ� �� ������ �õ尪�� �������� ���̺� �ε带 �ص� ��� ������ ����� �޶����� �ʽ��ϴ�. �׸� ���� �� �Դϴ�. 
//	�ٸ� ���ӵ鿡�� �ִ� �õ带 �Է��ϰ� �����ϴ� ��ɵ� �ֱ�� �մϴ�.
//	���� �����ҰŶ�� �ʿ��ϰ� �ƴϸ� �ʿ� �����ϴ�.
//	�̸��� �������غ����� �����մϴ�.
//	���� ������ �����ϰ� �ɸ��͸� �����Ҷ� �������ϴ�.
typedef struct {
	Player player;
	int game_seed; // -*- �̰͵� �����ΰ���? 
	Stage stage;
}Master;


// -*- �Ʒ����ʹ� GamePlay�� ���� �Լ��Դϴ�.
void DisplayGame(HDC hDC, Player* player);
void SetCard(Player* player);
POS GP_LBUTTONDOWN(HWND hWnd, int x, int y, Player* player);
void CheckState();
void CardAnimToXy(HWND hWnd, int x, int y, int animNum, Card* card, int cardNum);
POS StartStage(HWND hWnd, Player* player);


// From Main Screen


void set_MS_Button(HWND hWnd, RECT cRect, HINSTANCE g_hInst);
void print_MS(HDC hDC, RECT cRect, int main_menu);
void MS_LBUTTONDOWN(HWND hWnd, int mx, int my, int* main_menu, int* screen_number, Player* player, Master* master);
void MS_MOUSEMOVE(int mx, int my, int main_menu);
void Set_MS_Img();
void MS_MENU_1(HWND hWnd, int answer, int* screen_number);// ���� �������

// From In Game

void Set_IG_Img();
void set_IG_Button(HWND hWnd, RECT cRect, HINSTANCE g_hInst);
void print_IG(HDC hDC, RECT cRect, int main_menu, Master master);
void make_random_map(Master master);
void make_map(Master master);




// ���� ����ϴ� �Լ�
BOOL is_in_rect(int x, int y, RECT rect);
void print_button(HDC hDC, BOOL is_on, CImage* cButton, RECT rButton);

#endif