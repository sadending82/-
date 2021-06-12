#include "header.h"

//screen_number == 1 에 사용될 것들


static POINT pRoom;//50,50
static POINT pBoss;//500,300

static CImage cBasic_Enemy;
static CImage cElite_Enemy;
static CImage cRest;
static CImage cRelics;
static CImage cRandom;
static CImage cMerchant;
static CImage cBoss;

static CImage cBasic_Enemy_;
static CImage cElite_Enemy_;
static CImage cRest_;
static CImage cRelics_;
static CImage cRandom_;
static CImage cMerchant_;
static CImage cBoss_;






//이미지 세팅
void Set_IG_Img()
{

}



// 맵생성시 나오는 맵의 가중치 함수
int get_random_type_of_room()
{
	int rand_num;
	int room_weight[Number_of_Room_Types];
	int Cumulative_weight = 0;//누적 가중치
	int total_weight = 0;
	room_weight[Room_Basic_Enemy] = Weight_of_Room_Basic_Enemy;
	room_weight[Room_Elite_Enemy] = Weight_of_Room_Elite_Enemy;
	room_weight[Room_Rest] = Weight_of_Room_Rest;
	room_weight[Room_Relics] = Weight_of_Room_Relics;
	room_weight[Room_Random] = Weight_of_Room_Random;
	room_weight[Room_Merchant] = Weight_of_Room_Merchant;

	for (int i = 0; i < Number_of_Room_Types; i++)
		total_weight = total_weight + room_weight[i];

	rand_num = rand() % total_weight;

	for (int i = 0; i < Number_of_Room_Types; i++)
	{
		Cumulative_weight = Cumulative_weight + room_weight[i];
		if (rand_num < Cumulative_weight)
			return i;
	}
	return Room_Random;
}

//	지도를 랜덤 생성할 함수
void make_random_map(Master master)
{
	////int seed = master.game_seed;
	////srand(seed);
	//int stage_num = master.stage.stage_num;
	//int num_of_rooms[DNF] = { 0 };
	//master.stage.map.num_of_rooms = 0;
	//for (int i = 0; i < DNF; i++)
	//{
	//	num_of_rooms[i] = (rand() % MNRF) + 1;// 1 ~ 'MNRF' 개 생성
	//	master.stage.map.num_of_rooms += num_of_rooms[i];
	//}
	//
	//
	//master.stage.map.All_room = (Room**)malloc(sizeof(Room*) * master.stage.map.num_of_rooms);
	////실행이 안 되면 위 방들을 초기화해줘라
	///*
	//
	//*/
	//
	//Room start_room;// 시작 방 
	//start_room.room_type = Room_Start;
	//int room_count = 0;
	//for (int i = 0; i < DNF; i++)
	//{
	//	//층별로 방의 개수를 파악해 위치RECT를 설정
	//	//방 별로 type 설정
	//	switch (num_of_rooms[i])//층별 방의 개수
	//	{
	//	case 3:
	//		master.stage.map.All_room[room_count]->rect.left;
	//		master.stage.map.All_room[room_count]->rect.left;
	//		master.stage.map.All_room[room_count]->rect.left;
	//		master.stage.map.All_room[room_count]->rect.left;
	//		master.stage.map.All_room[room_count++]->room_type = get_random_type_of_room();
	//	case 2:
	//		master.stage.map.All_room[room_count]->rect.left;
	//		master.stage.map.All_room[room_count]->rect.left;
	//		master.stage.map.All_room[room_count]->rect.left;
	//		master.stage.map.All_room[room_count]->rect.left;
	//		master.stage.map.All_room[room_count++]->room_type = get_random_type_of_room();
	//	case 1:
	//		master.stage.map.All_room[room_count]->rect.left;
	//		master.stage.map.All_room[room_count]->rect.left;
	//		master.stage.map.All_room[room_count]->rect.left;
	//		master.stage.map.All_room[room_count]->rect.left;
	//		master.stage.map.All_room[room_count++]->room_type = get_random_type_of_room();
	//		break;
	//	}
	//}
	////어떻게 이을건지 설정
	////1이면 위 아래로 전부 다 연결해야함
	//// 2 이면 나눠서 연결
	//// 3 이면 나눠서 연결 알아서 잘 해봐
	//room_count = 0;
	//for (int i = 0; i < num_of_rooms[0]; i++)
	//{
	//	start_room.next1[i] = master.stage.map.All_room[room_count++];
	//}
	//master.stage.map.Start_Room = start_room;
	//
	//// 보스룸 선언과 생성
	//Room* boss_room = (Room*)malloc(sizeof(Room));// 시작 방 
	//boss_room->room_type = Room_Boss;
	//// 위치도 설정해야함
	//
	//for (int i = 1; i < DNF - 1; i++)
	//{
	//	//이전 층의 방의 개수와 현재 층의 방의 개수를 비교해 연결해준다
	//	/*
	//	
	//	11
	//	12
	//	13
	//	-- 그냥 다 연결하고 끝
	//	21
	//	-- 하나로 모아줌
	//	22
	//	-- 1:1 대응으로 만든다
	//	23
	//	31
	//	-- 하나로 모아줌
	//	32
	//	33
	//	-- 1:1 대응으로 만든다
	//
	//	의 경우로 나눠야함
	//	전이나 후가 1인 경우는 몰아줘야한다
	//	*/
	//	if (num_of_rooms[i] == 1)
	//	{
	//		
	//	}
	//	else if (num_of_rooms[i] == num_of_rooms[i - 1])
	//	{
	//		for (int i = 0; i < num_of_rooms[i]; i++)
	//		{
	//			master.stage.map.All_room[room_count - (1 + i)]->next1[i] = master.stage.map.All_room[room_count++];
	//		}
	//	}
	//	else if (num_of_rooms[i - 1] == 1)
	//	{
	//		for (int i = 0; i < num_of_rooms[i]; i++)
	//		{
	//			master.stage.map.All_room[room_count - (1 + i) ]->next1[i] = master.stage.map.All_room[room_count++];
	//		}
	//	}
	//	else
	//	{
	//		//불균형 패턴의 경우는 어떻게 할 지 생각해야함
	//		//값을 수정해도 함수를 수정하지 않도록 모든 MNRF에 적용 가능하도록 작성
	//		if (num_of_rooms[i] > num_of_rooms[i - 1])
	//		{
	//			//가운데 하나를 제외하고는 그대로 갈라져 나간다
	//			//가운데 하나는 양쪽으로 연결된다.
	//		}
	//		else if (num_of_rooms[i] < num_of_rooms[i - 1])
	//		{
	//
	//		}
	//	}
	//}
	// 마지막 방 들은 전부 다 보스룸과 연결한다.
}
//	고정지도에 랜덤 타입만 주는 함수
void make_map(Master* master, RECT cRect)
{
	// 시작 방에서 고정된 맵을 생성하고 랜덤한 타입값을 준다.
	master->stage.map.num_of_rooms = 13;
	
	master->stage.map.All_room = (Room**)malloc(sizeof(Room*) * master->stage.map.num_of_rooms);
	//실행이 안 되면 위 방들을 초기화해줘라
	for (int i = 0; i < master->stage.map.num_of_rooms; i++)
	{
		master->stage.map.All_room[i] = (Room*)malloc(sizeof(Room));
		for (int j = 0; j < MNRF; j++)
			master->stage.map.All_room[i]->next[j] = NULL;
		master->stage.map.All_room[i]->room_type = rand() % 6;
	}
	
	
	Room start_room;// 시작 방 
	start_room.room_type = Room_Start;

	Room* boss_room = (Room*)malloc(sizeof(Room));
	boss_room->room_type = Room_Boss;

	start_room.next[0] = master->stage.map.All_room[0];
	start_room.next[1] = master->stage.map.All_room[1];
	start_room.next[2] = master->stage.map.All_room[2];
	//						여기나    여기가 증가하고				여기도 증가 - 랜덤 생성 함수 만들때 고려해볼걸
	master->stage.map.All_room[0]->next[0] = master->stage.map.All_room[3];
	master->stage.map.All_room[0]->next[1] = master->stage.map.All_room[4];
	master->stage.map.All_room[1]->next[0] = master->stage.map.All_room[4];
	master->stage.map.All_room[2]->next[0] = master->stage.map.All_room[5];
	master->stage.map.All_room[3]->next[0] = master->stage.map.All_room[6];
	master->stage.map.All_room[4]->next[0] = master->stage.map.All_room[7];
	master->stage.map.All_room[5]->next[0] = master->stage.map.All_room[7];
	master->stage.map.All_room[6]->next[0] = master->stage.map.All_room[8];
	master->stage.map.All_room[6]->next[1] = master->stage.map.All_room[9];
	master->stage.map.All_room[7]->next[0] = master->stage.map.All_room[10];
	master->stage.map.All_room[8]->next[0] = master->stage.map.All_room[11];
	master->stage.map.All_room[9]->next[0] = master->stage.map.All_room[12];
	master->stage.map.All_room[10]->next[0] = master->stage.map.All_room[12];
	master->stage.map.All_room[11]->next[0] = boss_room;
	master->stage.map.All_room[12]->next[0] = boss_room;
	// 지도DC의 크기는 cRect에서 세로 2배,가로 3/5배
	for (int i = 0; i < 13; i++)
	{
		switch (i)
		{
		case 0:
		case 3:
		case 8:
			master->stage.map.All_room[i]->rect.left = cRect.right / 4;
			break;
		case 1:
		case 4:
		case 9:
			master->stage.map.All_room[i]->rect.left = cRect.right / 4 * 2;
			break;
		case 2:
		case 5:
		case 10:
			master->stage.map.All_room[i]->rect.left = cRect.right / 4 * 3;
			break;
		case 6:
		case 11:
			master->stage.map.All_room[i]->rect.left = cRect.right / 3;
			break;
		case 7:
		case 12:
			master->stage.map.All_room[i]->rect.left = cRect.right / 3 * 2;
			break;
		}
	}


	for (int i = 0; i < 3; i++)
		master->stage.map.All_room[i]->rect.top = (cRect.bottom * 2) / 8 * 7;
	for (int i = 3; i < 6; i++)
		master->stage.map.All_room[i]->rect.top = (cRect.bottom * 2) / 8 * 6;
	for (int i = 6; i < 8; i++)
		master->stage.map.All_room[i]->rect.top = (cRect.bottom * 2) / 8 * 5;
	for (int i = 8; i < 11; i++)
		master->stage.map.All_room[i]->rect.top = (cRect.bottom * 2) / 8 * 4;
	for (int i = 11; i < 13; i++)
		master->stage.map.All_room[i]->rect.top = (cRect.bottom * 2) / 8 * 3;

	boss_room->rect.left = (cRect.right * 3 / 5) / 2 - 250;
	boss_room->rect.right = boss_room->rect.left + 500;
	boss_room->rect.top = (cRect.bottom * 2) / 8 * 1;
	boss_room->rect.bottom = boss_room->rect.top + 300;

	for (int i = 0; i < 13; i++)
	{
		master->stage.map.All_room[i]->rect.right = master->stage.map.All_room[i]->rect.left + 50;
		master->stage.map.All_room[i]->rect.bottom = master->stage.map.All_room[i]->rect.top + 50;
	}
	master->stage.map.Boss_Room = boss_room;
	master->stage.map.Start_Room = start_room;

}
// 지도에 방을 출력할 함수
void print_room(HDC hMapDC)
{

}
//인 게임 - 스크린 넘버 2 출력화면
void print_IG(HDC hMemDC, HDC hMapDC, RECT cRect, int main_menu, Master master)
{
	//지도를 알맞게 출력한다.
}
// 지도가 위 아래로 움직이는걸 구현할 함수
