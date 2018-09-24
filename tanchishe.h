// ��ͷ�ļ�����Ϊ̰���ߵĺ궨���Լ����������ͺ�������

#ifndef _tanchishe_h_
#define _tanchishe_h_

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <malloc.h>
#include <windows.h>
#include <time.h>

#define SIMPLE_MAP_X 50         // ���Ѷȵĵ�ͼX����
#define SIMPLE_MAP_Y 24         // ���Ѷȵĵ�ͼY����
#define ORDINARY_MAP_X 30       // ��ͨ�Ѷȵĵ�ͼX����
#define ORDINARY_MAP_Y 15       // ��ͨ�Ѷȵĵ�ͼY����
#define DIFFICULT_MAP_X 22      // �����Ѷȵĵ�ͼX����
#define DIFFICULT_MAP_Y 12      // �����Ѷȵĵ�ͼY����
#define STARTED_X 11            // ��ͷ�ĳ�ʼ��Xλ��
#define STARTED_Y 6             // ��ͷ�ĳ�ʼ��yλ��
#define INIT_LENGTH 5           // �ߵĳ�ʼ������
#define INIT_SIMPLE_SPEED 250   // ���Ѷȵ��������ٶ�
#define INIT_ORDINARY_SPEED 200 // ��ͨ�Ѷȵ��������ٶ�
#define INIT_DIFFICULT_SPEED 150// �����Ѷȵ��������ٶ�
#define SIMPLE_SPEED 500        // ���Ѷȵ��߳�ʼ���ٶ�
#define ORDINARY_SPEED 400      // ��ͨ�Ѷȵ��߳�ʼ���ٶ�
#define DIFFICULT_SPEED 300     // �����Ѷȵ��߳�ʼ���ٶ�
#define FOOD_SPEED 2            // ÿ��һ��ʳ��ͼ��٣������ƣ�
#define SPEED_JIAN 2            // ÿ�ƶ�һ���ͼ��٣������ƣ�
#define AIR 0                   // ����
#define WALL 2                  // ǽ
#define SNAKE_BODY 1            // ����
#define FOOD 3                  // ʳ��
#define FOOD_MAX 8              // ʳ����������
#define SNAKE_HEAD_T 1          // ��ͷ��ͼ��
#define SNAKE_BODY_T 4          // �����ͼ��
#define WALL_T 22               // ǽ��ͼ��
#define AIR_T ' '               // ������ͼ��


// ��������
typedef struct snake_body {
	int x;
	int y;
	struct snake_body *up;
    struct snake_body *next;
} Snake_body;

// ��������
typedef struct {
	int x;
	int y;
} Coordinate;

// ��������
typedef Coordinate Direction;

// ������ͷ��β�ͷ����ָ����ٶ�
typedef struct head_tail {
    Snake_body *head;
    Snake_body *tail;
	Direction *direction;
	unsigned int speed;
} Head_Tail;

// ȫ�ֱ���
HANDLE hout;                                                       // ��ñ�׼����ľ��
int map[SIMPLE_MAP_Y][SIMPLE_MAP_X] = {0};                         // ��ͼ
int bian_x=0, bian_y=0;                                            // ��ͼ�߽磨���Ѷȱ仯���仯��
char produce_food[FOOD_MAX] = {3, 5, 6, 35, 36, 37, 38, 15};       // ʳ���ͼ����ASCII���е�ͼ����
unsigned int Fraction = 0;                                         // ����
int hard = 1;                                                      // �Ѷȣ�Ĭ��Ϊ��ͨ��
Direction olddir = {0,0};                                          // �ɵķ����ڰ���ʱ���Իָ���
Coordinate *food;                                                  // ʳ�������
unsigned int sleep_max = 0;                                        // �����ٶ�

// ��ʼ������
Head_Tail* initgame(Head_Tail*);

// �Զ����궨λ����
void Location(int x, int y);

// ���ƶ����ƶ�����жϺ��� ������ͷβ�ṹ��ָ��
void Mobile(Head_Tail*, int);// ���������Ƿ�����

// ��Ϸ����
Head_Tail* Game_Over(Head_Tail*);

// ����ʳ��
void Produce_food(void);

// �ͷ���Ϸ�з�����ڴ�
void fre_game(Head_Tail*, int);

// ��Ϸ��ʼ����
void Interface(Head_Tail*);

// ��������
void banzhu(void);

// ���ڽ���
void guanyu(void);

// ����
void set(void);

// ��ͣ����
void zantin(Head_Tail*);

// ����Ϸ����
void huagame(Head_Tail*);

#endif