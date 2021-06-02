// 헤더파일 입니다.
// 여기에 전역변수나 base가 아닌 다른 소스코드에서 생성한 함수의 반환형 등을 입력해 두면 될것 같습니다.


#include <windows.h>		
#include <tchar.h>
#include <time.h>
#include <atlimage.h>

#define WindowWidth 1200 // WindowWidth 윈도우 폭
#define WindowHeight 800 // WindowHeight 윈도우 높이


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

// 각각의 객체를 늘일때마다 바꿔줘야합니다.
#define Number_of_characters 1
// 스테이지 1의 몬스터의 종류입니다. 
#define Number_of_Regular_Monsters_in_Stage_1 1
#define RMS1 Number_of_Regular_Monsters_in_Stage_1

#define Number_of_Elite_Monsters_in_Stage_1 0
#define EMS1 Number_of_Elite_Monsters_in_Stage_1

#define Number_of_Boss_Monsters_in_Stage_1 0
#define BMS1 Number_of_Boss_Monsters_in_Stage_1

// 스테이지 2를 만들때 아래도 추가해주세요.
//...
// 객체 개수 선언 끝

typedef struct room {
	int room_type;
	struct room* next1;
	struct room* next2;
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
*/
typedef struct {
	Room room[DNR];
}Map;
typedef struct {
	int stage_num;
	Map map;
}Stage;
/*
스테이지별로 다른 종류의 몬스터 생성
각각 고유의 스프라이트
...
*/
typedef struct {
	int stage_num;
	int type; // 0 : 일반, 1 : 엘리트, 2 : 보스
	int ob_num;
	int hp;
}Monster;


typedef struct {
	int occupation;
	int type; // 0 : 없음, 1 : 공격, 2 : 방어
	int number;
	BOOL is_enhanced;//기본값 FLASE
}Card;
/*
* 카드
* number 값에 따라서 다른 이미지로 출력
ALL, 1, 0 = 모든 직업의 0번째 공격 카드 = 6 + 힘의 데미지		힘과 민첩은 버프입니다. 아래 버프 목록 참고
ALL, 2, 0 = 모든 직업의 0번째 수비 카드 = 6 + 민첩의 방어도
0, 1, 1 = 0번 직업의 1번째 공격카드 = 8 + 공격력으로 전체 공격
...
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
	int hp;
	int monney;
	int occupation;
	Deck deck;
	Item item;
}Player;

typedef struct {
	Player player;
	int random_seed;
	Stage stage;
}Master;


void GamePlay(HDC hDC);

