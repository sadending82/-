#include "header.h"

//screen_number == 1 �� ���� �͵�

//�̹��� ����
void Set_IG_Img()
{

}
// ��ư ����
void set_IG_Button(HWND hWnd, RECT cRect, HINSTANCE g_hInst)
{

}
//����Ʈ ��ư�� �����ͼ� �������

//�� ���� - ��ũ�� �ѹ� 2 ���ȭ��
void print_IG(HDC hDC, RECT cRect, int main_menu, Master master)
{
	//������ �˸°� ����Ѵ�.
}
// ������ �� �Ʒ��� �����̴°� ������ �Լ�



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
void make_map(Master master)
{
	// ���� �濡�� ������ ���� �����ϰ� ������ Ÿ�԰��� �ش�.
}

