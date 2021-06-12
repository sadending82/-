#include "header.h"

//screen_number == 1 에 사용될 것들

//이미지 세팅
void Set_IG_Img()
{

}
// 버튼 세팅
void set_IG_Button(HWND hWnd, RECT cRect, HINSTANCE g_hInst)
{

}
//프린트 버튼은 가져와서 사용하자

//인 게임 - 스크린 넘버 2 출력화면
void print_IG(HDC hDC, RECT cRect, int main_menu, Master master)
{
	//지도를 알맞게 출력한다.
}
// 지도가 위 아래로 움직이는걸 구현할 함수



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
void make_map(Master master)
{
	// 시작 방에서 고정된 맵을 생성하고 랜덤한 타입값을 준다.
}

