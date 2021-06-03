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
#define WindowHeight 1024 // WindowHeight 윈도우 높이


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

//Room 관련

#define Room_Basic_Enemy 0
#define Room_Elite_Enemy 1
#define Room_Rest 2
#define Room_Relics 3
#define Room_Random 4
#define Room_Merchant 5
#define Room_Boss 6

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

// -*- 이런 부분도 헤더파일로 추가해 주시면 제가 볼 때 코드를 이해하기 편합니다!
// -*- 일단은 제가 알 수 있는 부분에 대해서는 임의적으로 추가해 두었습니다.
// -*- 그리고 그래프 구조로 구현하는 것은 아주 좋은 방법인듯 합니다.
// -*- 대신, 맵을 그릴 때 어떤식으로 구현할지 고민을 해봐야 할 것 같습니다.

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
	int ob_num; // -*- 이건 무엇인가요?
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

// -*- ALL의 경우는 -1로 설정해 두겠습니다.
// -*- 그리고 이런 부분에 대해서는 저는 잘 모르기 때문에 전부 작성하거나, 카드나 유물 리스트 같은 것을 정리한 텍스트 파일을 리소스 파일에 추가해 주시면 감사하겠습니다.


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
	int hp;
	int money;
	int occupation;
	Deck deck;
	Item item;
	BOOL isCharacterActive; // 화면에 캐릭터를 출력할 것인지 아닌지 확인하는 변수 (전투 화면에 출력할 때만 TRUE)
}Player;

typedef struct {
	Player player;
	int random_seed; // -*- 이것도 무엇인가요?
	Stage stage;
}Master;


// -*- 아래부터는 GamePlay에 관한 함수입니다.
void DisplayGame(HDC hDC);

#endif