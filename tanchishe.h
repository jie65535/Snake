// 该头文件内容为贪吃蛇的宏定义以及类型声明和函数声明

#ifndef _tanchishe_h_
#define _tanchishe_h_

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <malloc.h>
#include <windows.h>
#include <time.h>

#define SIMPLE_MAP_X 50         // 简单难度的地图X长度
#define SIMPLE_MAP_Y 24         // 简单难度的地图Y长度
#define ORDINARY_MAP_X 30       // 普通难度的地图X长度
#define ORDINARY_MAP_Y 15       // 普通难度的地图Y长度
#define DIFFICULT_MAP_X 22      // 困难难度的地图X长度
#define DIFFICULT_MAP_Y 12      // 困难难度的地图Y长度
#define STARTED_X 11            // 蛇头的初始化X位置
#define STARTED_Y 6             // 蛇头的初始化y位置
#define INIT_LENGTH 5           // 蛇的初始化长度
#define INIT_SIMPLE_SPEED 250   // 简单难度的蛇最终速度
#define INIT_ORDINARY_SPEED 200 // 普通难度的蛇最终速度
#define INIT_DIFFICULT_SPEED 150// 困难难度的蛇最终速度
#define SIMPLE_SPEED 500        // 简单难度的蛇初始化速度
#define ORDINARY_SPEED 400      // 普通难度的蛇初始化速度
#define DIFFICULT_SPEED 300     // 困难难度的蛇初始化速度
#define FOOD_SPEED 2            // 每吃一个食物就加速（无限制）
#define SPEED_JIAN 2            // 每移动一步就加速（有限制）
#define AIR 0                   // 空气
#define WALL 2                  // 墙
#define SNAKE_BODY 1            // 蛇体
#define FOOD 3                  // 食物
#define FOOD_MAX 8              // 食物的种类个数
#define SNAKE_HEAD_T 1          // 蛇头的图案
#define SNAKE_BODY_T 4          // 蛇身的图案
#define WALL_T 22               // 墙的图案
#define AIR_T ' '               // 空气的图案


// 蛇体类型
typedef struct snake_body {
	int x;
	int y;
	struct snake_body *up;
    struct snake_body *next;
} Snake_body;

// 坐标类型
typedef struct {
	int x;
	int y;
} Coordinate;

// 方向类型
typedef Coordinate Direction;

// 包含蛇头蛇尾和方向的指针和速度
typedef struct head_tail {
    Snake_body *head;
    Snake_body *tail;
	Direction *direction;
	unsigned int speed;
} Head_Tail;

// 全局变量
HANDLE hout;                                                       // 获得标准输出的句柄
int map[SIMPLE_MAP_Y][SIMPLE_MAP_X] = {0};                         // 地图
int bian_x=0, bian_y=0;                                            // 地图边界（随难度变化而变化）
char produce_food[FOOD_MAX] = {3, 5, 6, 35, 36, 37, 38, 15};       // 食物的图案（ASCII表中的图案）
unsigned int Fraction = 0;                                         // 分数
int hard = 1;                                                      // 难度（默认为普通）
Direction olddir = {0,0};                                          // 旧的方向（在按错时可以恢复）
Coordinate *food;                                                  // 食物的坐标
unsigned int sleep_max = 0;                                        // 最快的速度

// 初始化函数
Head_Tail* initgame(Head_Tail*);

// 自定义光标定位函数
void Location(int x, int y);

// 蛇移动和移动后的判断函数 参数是头尾结构体指针
void Mobile(Head_Tail*, int);// 参数二是是否作弊

// 游戏结束
Head_Tail* Game_Over(Head_Tail*);

// 生成食物
void Produce_food(void);

// 释放游戏中分配的内存
void fre_game(Head_Tail*, int);

// 游戏开始界面
void Interface(Head_Tail*);

// 帮助界面
void banzhu(void);

// 关于界面
void guanyu(void);

// 设置
void set(void);

// 暂停界面
void zantin(Head_Tail*);

// 画游戏界面
void huagame(Head_Tail*);

#endif