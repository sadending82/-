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
#define WindowHeight 1024 // WindowHeight ������ ����


#define Maximum_number_of_cards_on_deck 50
#define MNCD Maximum_number_of_cards_on_deck

#define Default_number_of_cards_on_deck 10
#define DNCD Default_number_of_cards_on_deck

#define Default_number_of_rooms 10
#define DNR Default_number_of_rooms

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

#define Room_Basic_Enemy 0
#define Room_Elite_Enemy 1
#define Room_Rest 2
#define Room_Relics 3
#define Room_Random 4
#define Room_Merchant 5
#define Room_Boss 6

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

// �������� 2�� ���鶧 �Ʒ��� �߰����ּ���.
//...
// ��ü ���� ���� ��

typedef struct room {
	int room_type;
	struct room* next1;
	struct room* next2;
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
// -*- ���, ���� �׸� �� ������� �������� ����� �غ��� �� �� �����ϴ�.

*/
typedef struct {

	Room room[DNR];

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


typedef struct {
	int occupation;
	int type; // 0 : ����, 1 : ����, 2 : ���
	int number;
	BOOL is_enhanced;//�⺻�� FLASE
}Card;
/*
* ī��
* number ���� ���� �ٸ� �̹����� ���
ALL, 1, 0 = ��� ������ 0��° ���� ī�� = 6 + ���� ������		���� ��ø�� �����Դϴ�. �Ʒ� ���� ��� ����
ALL, 2, 0 = ��� ������ 0��° ���� ī�� = 6 + ��ø�� ��
0, 1, 1 = 0�� ������ 1��° ����ī�� = 8 + ���ݷ����� ��ü ����
...

// -*- ALL�� ���� -1�� ������ �ΰڽ��ϴ�.
// -*- �׸��� �̷� �κп� ���ؼ��� ���� �� �𸣱� ������ ���� �ۼ��ϰų�, ī�峪 ���� ����Ʈ ���� ���� ������ �ؽ�Ʈ ������ ���ҽ� ���Ͽ� �߰��� �ֽø� �����ϰڽ��ϴ�.


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
	Deck deck;
	Item item;
	BOOL isCharacterActive; // ȭ�鿡 ĳ���͸� ����� ������ �ƴ��� Ȯ���ϴ� ���� (���� ȭ�鿡 ����� ���� TRUE)
}Player;

typedef struct {
	Player player;
	int random_seed; // -*- �̰͵� �����ΰ���?
	Stage stage;
}Master;


// -*- �Ʒ����ʹ� GamePlay�� ���� �Լ��Դϴ�.
void DisplayGame(HDC hDC);

#endif