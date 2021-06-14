#include "header.h"

//screen_number == 1 에 사용될 것들


static POINT pRoom;//50,50
static POINT pBoss;//500,300
static POINT pIG_Map;

static CImage cIG_Map;
static CImage cLegend;
static CImage cStatus_Bar;

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

static CImage cBasic_Enemy_2;
static CImage cElite_Enemy_2;
static CImage cRest_2;
static CImage cRelics_2;
static CImage cRandom_2;
static CImage cMerchant_2;
static CImage cBoss_2;




//이미지 세팅
void Set_IG_Img()
{
	if (cIG_Map.IsNull())
		cIG_Map.Load(L"IG_Map.png");
	if (cLegend.IsNull())
		cLegend.Load(L"Legend.png");
	if (cStatus_Bar.IsNull())
		cStatus_Bar.Load(L"Status_Bar.png");

	if (cBasic_Enemy.IsNull())
		cBasic_Enemy.Load(L"Basic_Enemy.png");
	if (cElite_Enemy.IsNull())
		cElite_Enemy.Load(L"Elite_Enemy.png");
	if (cRest.IsNull())
		cRest.Load(L"Rest.png");
	if (cRelics.IsNull())
		cRelics.Load(L"Relics.png");
	if (cRandom.IsNull())
		cRandom.Load(L"Random.png");
	if (cMerchant.IsNull())
		cMerchant.Load(L"Merchant.png");
	if (cBoss.IsNull())
		cBoss.Load(L"Boss.png");

	if (cBasic_Enemy_.IsNull())
		cBasic_Enemy_.Load(L"Basic_Enemy_.png");
	if (cElite_Enemy_.IsNull())
		cElite_Enemy_.Load(L"Elite_Enemy_.png");
	if (cRest_.IsNull())
		cRest_.Load(L"Rest_.png");
	if (cRelics_.IsNull())
		cRelics_.Load(L"Relics_.png");
	if (cRandom_.IsNull())
		cRandom_.Load(L"Random_.png");
	if (cMerchant_.IsNull())
		cMerchant_.Load(L"Merchant_.png");
	if (cBoss_.IsNull())
		cBoss_.Load(L"Boss_.png");
	if (cBasic_Enemy_2.IsNull())
		cBasic_Enemy_2.Load(L"Basic_Enemy_2.png");
	if (cElite_Enemy_2.IsNull())
		cElite_Enemy_2.Load(L"Elite_Enemy_2.png");
	if (cRest_2.IsNull())
		cRest_2.Load(L"Rest_2.png");
	if (cRelics_2.IsNull())
		cRelics_2.Load(L"Relics_2.png");
	if (cRandom_2.IsNull())
		cRandom_2.Load(L"Random_2.png");
	if (cMerchant_2.IsNull())
		cMerchant_2.Load(L"Merchant_2.png");
	if (cBoss_2.IsNull())
		cBoss_2.Load(L"Boss_2.png");
}

void Set_IG_POINT(RECT cRect)
{
	pRoom.x = pRoom.y = 50;

	pBoss.x = 500;
	pBoss.y = 300;

	pIG_Map.x = cRect.right * 3 / 5;
	pIG_Map.y = cRect.bottom * 2;
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

// 휴대폰 메모 참고
}
//	고정지도에 랜덤 타입만 주는 함수
void make_map(Master* master, RECT cRect)
{
	Set_IG_POINT(cRect);
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
	//X축
	int error = cRect.right / 5;// 오차
	for (int i = 0; i < 13; i++)
	{
		switch (i)
		{
		case 0:
		case 3:
		case 8:
			master->stage.map.All_room[i]->rect.left = pIG_Map.x / 4 + error;
			break;
		case 1:
		case 4:
		case 9:
			master->stage.map.All_room[i]->rect.left = pIG_Map.x / 4 * 2 + error;
			break;
		case 2:
		case 5:
		case 10:
			master->stage.map.All_room[i]->rect.left = pIG_Map.x / 4 * 3 + error;
			break;
		case 6:
		case 11:
			master->stage.map.All_room[i]->rect.left = pIG_Map.x / 3 + error;
			break;
		case 7:
		case 12:
			master->stage.map.All_room[i]->rect.left = pIG_Map.x / 3 * 2 + error;
			break;
		}
	}

	//Y 축
	for (int i = 0; i < 3; i++)
		master->stage.map.All_room[i]->rect.top = pIG_Map.y / 8 * 7;
	for (int i = 3; i < 6; i++)
		master->stage.map.All_room[i]->rect.top = pIG_Map.y / 8 * 6;
	for (int i = 6; i < 8; i++)
		master->stage.map.All_room[i]->rect.top = pIG_Map.y / 8 * 5;
	for (int i = 8; i < 11; i++)
		master->stage.map.All_room[i]->rect.top = pIG_Map.y / 8 * 4;
	for (int i = 11; i < 13; i++)
		master->stage.map.All_room[i]->rect.top = pIG_Map.y / 8 * 3;

	boss_room->rect.left = pIG_Map.x / 2 - 250 + error;
	boss_room->rect.right = boss_room->rect.left + 500;
	boss_room->rect.top = pIG_Map.y / 8 * 1;
	boss_room->rect.bottom = boss_room->rect.top + 300;

	for (int i = 0; i < 13; i++)
	{
		master->stage.map.All_room[i]->rect.right = master->stage.map.All_room[i]->rect.left + 50;
		master->stage.map.All_room[i]->rect.bottom = master->stage.map.All_room[i]->rect.top + 50;
	}
	master->stage.map.Boss_Room = boss_room;
	master->stage.map.Start_Room = start_room;

	master->stage.map.Current_Room = &master->stage.map.Start_Room;
}
// 지도에 방을 출력할 함수
void print_room(HDC hMapDC, Master master, RECT cRect,int room_print_count)
{
	POINT error;// 오차
	error.x = cRect.right / 5;
	error.y = -30;
	RECT tmp_rect;
	//tmp_rect = master.stage.map.Current_Room->rect;
	//InflateRect(&tmp_rect, 10, 10);
	//Ellipse(hMapDC, tmp_rect.left, tmp_rect.top, tmp_rect.right, tmp_rect.bottom);


	
	// 방 출력
	for (int i = 0; i < 13; i++)
	{
		if(master.stage.map.All_room[i]!= master.stage.map.Current_Room->next[0]&& master.stage.map.All_room[i] != master.stage.map.Current_Room->next[1]&& master.stage.map.All_room[i] != master.stage.map.Current_Room->next[2])
			switch (master.stage.map.All_room[i]->room_type)
			{
			case Room_Basic_Enemy:
				//해당 좌표에 해당 이미지 출력
				cBasic_Enemy.Draw(hMapDC, master.stage.map.All_room[i]->rect.left, master.stage.map.All_room[i]->rect.top, 50, 50, 0, 0, 50, 50);
				break;
			case Room_Elite_Enemy:
				cElite_Enemy.Draw(hMapDC, master.stage.map.All_room[i]->rect.left, master.stage.map.All_room[i]->rect.top, 50, 50, 0, 0, 50, 50);
				break;
			case Room_Rest:
				cRest.Draw(hMapDC, master.stage.map.All_room[i]->rect.left, master.stage.map.All_room[i]->rect.top, 50, 50, 0, 0, 50, 50);
				break;
			case Room_Relics:
				cRelics.Draw(hMapDC, master.stage.map.All_room[i]->rect.left, master.stage.map.All_room[i]->rect.top, 50, 50, 0, 0, 50, 50);
				break;
			case Room_Merchant:
				cMerchant.Draw(hMapDC, master.stage.map.All_room[i]->rect.left, master.stage.map.All_room[i]->rect.top, 50, 50, 0, 0, 50, 50);
				break;
			case Room_Random:
				cRandom.Draw(hMapDC, master.stage.map.All_room[i]->rect.left, master.stage.map.All_room[i]->rect.top, 50, 50, 0, 0, 50, 50);
				break;
			}
		else	// 선택 가능한 노드 출력 방식 - 애니메이션으로 변경할것
			for (int j = 0; j < MNRF; j++)
				if (master.stage.map.Current_Room->next[j] != NULL && master.stage.map.Current_Room != master.stage.map.Boss_Room)
				{
					//tmp_rect = master.stage.map.Current_Room->next[j]->rect;
					//InflateRect(&tmp_rect, 10, 10);
					//Ellipse(hMapDC, tmp_rect.left, tmp_rect.top, tmp_rect.right, tmp_rect.bottom);
					switch (room_print_count)
					{
					case 0:
						switch (master.stage.map.All_room[i]->room_type)
						{
						case Room_Basic_Enemy:
							//해당 좌표에 해당 이미지 출력
							cBasic_Enemy.Draw(hMapDC, master.stage.map.All_room[i]->rect.left, master.stage.map.All_room[i]->rect.top, 50, 50, 0, 0, 50, 50);
							break;
						case Room_Elite_Enemy:
							cElite_Enemy.Draw(hMapDC, master.stage.map.All_room[i]->rect.left, master.stage.map.All_room[i]->rect.top, 50, 50, 0, 0, 50, 50);
							break;
						case Room_Rest:
							cRest.Draw(hMapDC, master.stage.map.All_room[i]->rect.left, master.stage.map.All_room[i]->rect.top, 50, 50, 0, 0, 50, 50);
							break;
						case Room_Relics:
							cRelics.Draw(hMapDC, master.stage.map.All_room[i]->rect.left, master.stage.map.All_room[i]->rect.top, 50, 50, 0, 0, 50, 50);
							break;
						case Room_Merchant:
							cMerchant.Draw(hMapDC, master.stage.map.All_room[i]->rect.left, master.stage.map.All_room[i]->rect.top, 50, 50, 0, 0, 50, 50);
							break;
						case Room_Random:
							cRandom.Draw(hMapDC, master.stage.map.All_room[i]->rect.left, master.stage.map.All_room[i]->rect.top, 50, 50, 0, 0, 50, 50);
							break;
						}
						break;
					case 1:
					case 3:
						switch (master.stage.map.All_room[i]->room_type)
						{
						case Room_Basic_Enemy:
							//해당 좌표에 해당 이미지 출력
							cBasic_Enemy_.Draw(hMapDC, master.stage.map.All_room[i]->rect.left, master.stage.map.All_room[i]->rect.top, 50, 50, 0, 0, 50, 50);
							break;
						case Room_Elite_Enemy:
							cElite_Enemy_.Draw(hMapDC, master.stage.map.All_room[i]->rect.left, master.stage.map.All_room[i]->rect.top, 50, 50, 0, 0, 50, 50);
							break;
						case Room_Rest:
							cRest_.Draw(hMapDC, master.stage.map.All_room[i]->rect.left, master.stage.map.All_room[i]->rect.top, 50, 50, 0, 0, 50, 50);
							break;
						case Room_Relics:
							cRelics_.Draw(hMapDC, master.stage.map.All_room[i]->rect.left, master.stage.map.All_room[i]->rect.top, 50, 50, 0, 0, 50, 50);
							break;
						case Room_Merchant:
							cMerchant_.Draw(hMapDC, master.stage.map.All_room[i]->rect.left, master.stage.map.All_room[i]->rect.top, 50, 50, 0, 0, 50, 50);
							break;
						case Room_Random:
							cRandom_.Draw(hMapDC, master.stage.map.All_room[i]->rect.left, master.stage.map.All_room[i]->rect.top, 50, 50, 0, 0, 50, 50);
							break;
						}
						break;
					case 2:
						switch (master.stage.map.All_room[i]->room_type)
						{
						case Room_Basic_Enemy:
							//해당 좌표에 해당 이미지 출력
							cBasic_Enemy_2.Draw(hMapDC, master.stage.map.All_room[i]->rect.left, master.stage.map.All_room[i]->rect.top, 50, 50, 0, 0, 50, 50);
							break;
						case Room_Elite_Enemy:
							cElite_Enemy_2.Draw(hMapDC, master.stage.map.All_room[i]->rect.left, master.stage.map.All_room[i]->rect.top, 50, 50, 0, 0, 50, 50);
							break;
						case Room_Rest:
							cRest_2.Draw(hMapDC, master.stage.map.All_room[i]->rect.left, master.stage.map.All_room[i]->rect.top, 50, 50, 0, 0, 50, 50);
							break;
						case Room_Relics:
							cRelics_2.Draw(hMapDC, master.stage.map.All_room[i]->rect.left, master.stage.map.All_room[i]->rect.top, 50, 50, 0, 0, 50, 50);
							break;
						case Room_Merchant:
							cMerchant_2.Draw(hMapDC, master.stage.map.All_room[i]->rect.left, master.stage.map.All_room[i]->rect.top, 50, 50, 0, 0, 50, 50);
							break;
						case Room_Random:
							cRandom_2.Draw(hMapDC, master.stage.map.All_room[i]->rect.left, master.stage.map.All_room[i]->rect.top, 50, 50, 0, 0, 50, 50);
							break;
						}
						break;
					}
				}
	}
	//보스룸 출력
	if (master.stage.map.Current_Room->next[0] == master.stage.map.Boss_Room)
	{
		switch (room_print_count)
		{
		case 0:
			cBoss.Draw(hMapDC, master.stage.map.Boss_Room->rect.left, master.stage.map.Boss_Room->rect.top, 500, 300, 0, 0, 500, 300);
			break;
		case 1:
		case 3:
			cBoss_.Draw(hMapDC, master.stage.map.Boss_Room->rect.left, master.stage.map.Boss_Room->rect.top, 500, 300, 0, 0, 500, 300);
			break;
		case 2:
			cBoss_2.Draw(hMapDC, master.stage.map.Boss_Room->rect.left, master.stage.map.Boss_Room->rect.top, 500, 300, 0, 0, 500, 300);
			break;
		}
	}
	else
		cBoss.Draw(hMapDC, master.stage.map.Boss_Room->rect.left, master.stage.map.Boss_Room->rect.top, 500, 300, 0, 0, 500, 300);


}
//인 게임 - 스크린 넘버 2 출력화면
void print_IG(HDC hMemDC, HDC hMapDC, RECT cRect, Master master, int map_yPos, int room_print_count)
{
	Set_IG_Img();
	Set_IG_POINT(cRect);
	//지도를 알맞게 출력한다.
	int pw = cIG_Map.GetWidth();
	int ph = cIG_Map.GetHeight();
	cIG_Map.Draw(hMapDC, 0, 0, pIG_Map.x, pIG_Map.y, 0, 0, pw, ph);
	BitBlt(hMemDC, cRect.right / 5, 0, pIG_Map.x, cRect.bottom, hMapDC, 0, map_yPos, SRCCOPY);
	// 방 출력
	print_room(hMemDC, master,cRect, room_print_count);
	// 방을 잊는 선 출력
	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < MNRF; j++)
			if (master.stage.map.All_room[i]->next[j] != NULL)
			{
				MoveToEx(hMemDC, master.stage.map.All_room[i]->rect.left + (master.stage.map.All_room[i]->rect.right- master.stage.map.All_room[i]->rect.left)/2, master.stage.map.All_room[i]->rect.top, NULL);
				LineTo(hMemDC, master.stage.map.All_room[i]->next[j]->rect.left + (master.stage.map.All_room[i]->next[j]->rect.right - master.stage.map.All_room[i]->next[j]->rect.left) / 2, master.stage.map.All_room[i]->next[j]->rect.bottom);
			}
	}



	// 옆에 나오는 목록 출력
	pw = cStatus_Bar.GetWidth();
	ph = cStatus_Bar.GetHeight();
	cStatus_Bar.Draw(hMemDC, 0, 0, cRect.right, ph, 0, 0, pw, ph);
	//맨 위에 상태창 출력
	// 상태창 출력 함수 만들것
	pw = cLegend.GetWidth();
	ph = cLegend.GetHeight();
	cLegend.Draw(hMemDC, cRect.right - pw - 150, cRect.bottom / 2 - ph / 2, pw, ph, 0, 0, pw, ph);
	TCHAR Hp_bar[20];
	TCHAR Money_bar[20];
	wsprintf(Hp_bar, L"%d / %d", master.player.hp.Current_hp, master.player.hp.Max_hp);
	wsprintf(Money_bar, L"%3d", master.player.money);
	// 이 부분은 옛날 과제에서 팩맨 색 바꾸던 코드 참고
	TextOut(hMemDC, 225, 7, Hp_bar, _tcslen(Hp_bar));
	TextOut(hMemDC, 320, 7, Money_bar, _tcslen(Money_bar));

}
// 지도가 위 아래로 움직이는걸 구현할 함수
void IG_MOUSEMOVE(int mx, int my, POINT* cursor)
{
	cursor->x = mx;
	cursor->y = my;
}
void IG_Timer(POINT cursor, int* map_yPos, RECT cRect, Master* master)
{
	if (cursor.y >= 0 && cursor.y < 30)
	{
		if (*map_yPos > -30)
		{
			*map_yPos = *map_yPos - 30;
			if (master->stage.map.Boss_Room != NULL)
			{
				for (int i = 0; i < 13; i++)
				{
					OffsetRect(&master->stage.map.All_room[i]->rect, 0, 30);
				}
				OffsetRect(&master->stage.map.Boss_Room->rect, 0, 30);
			}
		}
		if (*map_yPos < -30)
			*map_yPos = -30;
	}
	if (cursor.y > cRect.bottom - 30 && cursor.y <= cRect.bottom)
	{
		if (*map_yPos < cRect.bottom + 30)
		{
			*map_yPos = *map_yPos + 30;
			if (master->stage.map.Boss_Room != NULL)
			{
				for (int i = 0; i < 13; i++)
				{
					OffsetRect(&master->stage.map.All_room[i]->rect, 0, -30);
				}
				OffsetRect(&master->stage.map.Boss_Room->rect, 0, -30);
			}
		}
		if (*map_yPos > cRect.bottom + 30)
			*map_yPos = cRect.bottom + 30;
	}
	//맵 노드들의 좌표값도 같이 움직여야한다.
	// rect 영역 움직여주는 함수 갔다가 쓰자.
	
}
void IG_LBUTTONDOWN(HWND hWnd, int mx, int my, Master* master, RECT cRect, BOOL* is_pause)
{
	TCHAR str[20];
	if (is_in_rect(mx, my, master->stage.map.Boss_Room->rect))
	{
		MessageBox(hWnd, L"보스방", L"노드 선택", MB_OK);
		master->stage.map.Current_Room = master->stage.map.Boss_Room;// 이건 필요 없음
		// 보스와 전투 시작 코드 추가
		// 전투가 끝나면 다음 스테이지로 가거나 마지막 스테이지면 점수가 나오고 메인 화면으로
	}
	else
		for (int i = 0; i < 13; i++)
		{
			wsprintf(str, L"%d", i);
			//커런트룸의 next이면
			for (int j = 0; j < MNRF; j++)
				if(is_in_rect(mx, my, master->stage.map.All_room[i]->rect))
					if (master->stage.map.Current_Room->next[j] != NULL && is_in_rect(mx, my, master->stage.map.Current_Room->next[j]->rect))
					{
						MessageBox(hWnd, str, L"노드 선택", MB_OK);
						//각각을 함수로 만들어야 랜덤 구현하기가 편함.
						switch (master->stage.map.Current_Room->room_type)
						{
						case Room_Basic_Enemy:
							break;
						case Room_Elite_Enemy:
							break;
						case Room_Rest:
							break;
						case Room_Relics:
							break;
						case Room_Merchant:
							break;
						case Room_Random:
							break;
						}
						// 위 작업이 끝나면 아래 코드가 실행되어야함
						master->stage.map.Current_Room = master->stage.map.All_room[i];
					}
		}
	RECT tmp;
	tmp.left = cRect.right - cStatus_Bar.GetHeight();
	tmp.right = cRect.right;
	tmp.top = 0;
	tmp.bottom = cStatus_Bar.GetHeight();
	if (is_in_rect(mx, my, tmp))
			*is_pause = TRUE;
}