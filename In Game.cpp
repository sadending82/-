#include "header.h"

//screen_number == 1 �� ���� �͵�


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






//�̹��� ����
void Set_IG_Img()
{

}



// �ʻ����� ������ ���� ����ġ �Լ�
int get_random_type_of_room()
{
	int rand_num;
	int room_weight[Number_of_Room_Types];
	int Cumulative_weight = 0;//���� ����ġ
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

//	������ ���� ������ �Լ�
void make_random_map(Master master)
{
	////int seed = master.game_seed;
	////srand(seed);
	//int stage_num = master.stage.stage_num;
	//int num_of_rooms[DNF] = { 0 };
	//master.stage.map.num_of_rooms = 0;
	//for (int i = 0; i < DNF; i++)
	//{
	//	num_of_rooms[i] = (rand() % MNRF) + 1;// 1 ~ 'MNRF' �� ����
	//	master.stage.map.num_of_rooms += num_of_rooms[i];
	//}
	//
	//
	//master.stage.map.All_room = (Room**)malloc(sizeof(Room*) * master.stage.map.num_of_rooms);
	////������ �� �Ǹ� �� ����� �ʱ�ȭ�����
	///*
	//
	//*/
	//
	//Room start_room;// ���� �� 
	//start_room.room_type = Room_Start;
	//int room_count = 0;
	//for (int i = 0; i < DNF; i++)
	//{
	//	//������ ���� ������ �ľ��� ��ġRECT�� ����
	//	//�� ���� type ����
	//	switch (num_of_rooms[i])//���� ���� ����
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
	////��� �������� ����
	////1�̸� �� �Ʒ��� ���� �� �����ؾ���
	//// 2 �̸� ������ ����
	//// 3 �̸� ������ ���� �˾Ƽ� �� �غ�
	//room_count = 0;
	//for (int i = 0; i < num_of_rooms[0]; i++)
	//{
	//	start_room.next1[i] = master.stage.map.All_room[room_count++];
	//}
	//master.stage.map.Start_Room = start_room;
	//
	//// ������ ����� ����
	//Room* boss_room = (Room*)malloc(sizeof(Room));// ���� �� 
	//boss_room->room_type = Room_Boss;
	//// ��ġ�� �����ؾ���
	//
	//for (int i = 1; i < DNF - 1; i++)
	//{
	//	//���� ���� ���� ������ ���� ���� ���� ������ ���� �������ش�
	//	/*
	//	
	//	11
	//	12
	//	13
	//	-- �׳� �� �����ϰ� ��
	//	21
	//	-- �ϳ��� �����
	//	22
	//	-- 1:1 �������� �����
	//	23
	//	31
	//	-- �ϳ��� �����
	//	32
	//	33
	//	-- 1:1 �������� �����
	//
	//	�� ���� ��������
	//	���̳� �İ� 1�� ���� ��������Ѵ�
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
	//		//�ұ��� ������ ���� ��� �� �� �����ؾ���
	//		//���� �����ص� �Լ��� �������� �ʵ��� ��� MNRF�� ���� �����ϵ��� �ۼ�
	//		if (num_of_rooms[i] > num_of_rooms[i - 1])
	//		{
	//			//��� �ϳ��� �����ϰ�� �״�� ������ ������
	//			//��� �ϳ��� �������� ����ȴ�.
	//		}
	//		else if (num_of_rooms[i] < num_of_rooms[i - 1])
	//		{
	//
	//		}
	//	}
	//}
	// ������ �� ���� ���� �� ������� �����Ѵ�.
}
//	���������� ���� Ÿ�Ը� �ִ� �Լ�
void make_map(Master* master, RECT cRect)
{
	// ���� �濡�� ������ ���� �����ϰ� ������ Ÿ�԰��� �ش�.
	master->stage.map.num_of_rooms = 13;
	
	master->stage.map.All_room = (Room**)malloc(sizeof(Room*) * master->stage.map.num_of_rooms);
	//������ �� �Ǹ� �� ����� �ʱ�ȭ�����
	for (int i = 0; i < master->stage.map.num_of_rooms; i++)
	{
		master->stage.map.All_room[i] = (Room*)malloc(sizeof(Room));
		for (int j = 0; j < MNRF; j++)
			master->stage.map.All_room[i]->next[j] = NULL;
		master->stage.map.All_room[i]->room_type = rand() % 6;
	}
	
	
	Room start_room;// ���� �� 
	start_room.room_type = Room_Start;

	Room* boss_room = (Room*)malloc(sizeof(Room));
	boss_room->room_type = Room_Boss;

	start_room.next[0] = master->stage.map.All_room[0];
	start_room.next[1] = master->stage.map.All_room[1];
	start_room.next[2] = master->stage.map.All_room[2];
	//						���⳪    ���Ⱑ �����ϰ�				���⵵ ���� - ���� ���� �Լ� ���鶧 ����غ���
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
	// ����DC�� ũ��� cRect���� ���� 2��,���� 3/5��
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
// ������ ���� ����� �Լ�
void print_room(HDC hMapDC)
{

}
//�� ���� - ��ũ�� �ѹ� 2 ���ȭ��
void print_IG(HDC hMemDC, HDC hMapDC, RECT cRect, int main_menu, Master master)
{
	//������ �˸°� ����Ѵ�.
}
// ������ �� �Ʒ��� �����̴°� ������ �Լ�
