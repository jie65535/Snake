#include "tanchishe.h"

// 所有函数与类型等都在头文件声明，以下为函数实现

// 初始化函数
Head_Tail* initgame(Head_Tail *snake)
{
	hout = GetStdHandle(STD_OUTPUT_HANDLE);        // 获得标准输出的句柄
	CONSOLE_CURSOR_INFO cursor_info = {1,0};       // 隐藏光标所需类型
	int x=0, y=0, i=0;
	Fraction = 0;                                  // 分数初始化
	Snake_body *temp =NULL, *p1=NULL;
	system ("title 贪  吃  蛇");
	system ("cls"); 
	SetConsoleCursorInfo(hout, &cursor_info);       // 隐藏光标
	snake = (Head_Tail*)malloc(sizeof(Head_Tail));
	if (snake == NULL)
	{
		fprintf (stderr, "内存分配失败，退出游戏。");
		exit(1);
	}
	snake->head = (Snake_body*)malloc(sizeof(Snake_body));
	if (snake->head == NULL)
	{
		fprintf (stderr, "内存分配失败，退出游戏。");
		exit(1);
	}
	snake->head->up = NULL;
	temp = snake->head;
	for (y=STARTED_Y, x=STARTED_X; x > STARTED_X - INIT_LENGTH; x--) // X改变而Y不改
	{
		temp->x = x;                                  // 将坐标赋值
		temp->y = y;
		p1 = (Snake_body*)malloc(sizeof(Snake_body)); // 下一节蛇体
		if (p1 == NULL)
		{
			fprintf (stderr, "内存分配失败，退出游戏。");
			exit(1);
		}
		p1->up = temp;
		p1->next = NULL;
		temp->next = p1;
		temp = temp->next;
		p1 = NULL;
	}
	temp->x=x,temp->y=y;
	snake->tail = temp;       // 蛇尾
	snake->direction = (Direction*)malloc(sizeof(Direction)); // 下一节蛇体
	if (snake->head == NULL)
	{
		fprintf (stderr, "内存分配失败，退出游戏。");
		exit(1);
	}
	snake->direction->x = 1;  // 方向，x为1表示向右，0表示不转
	snake->direction->y = 0;
	food = (Coordinate*)malloc(sizeof(Coordinate));   // 为存放食物坐标的结构体分配内存
	
	switch (hard) {
		case 0:                              // 简单难度
			bian_x = SIMPLE_MAP_X;           // 地图的边界x
			bian_y = SIMPLE_MAP_Y;           // 地图的边界y
			snake->speed = SIMPLE_SPEED;     // 速度
			sleep_max = INIT_SIMPLE_SPEED;   // 速度的最低限制
			break;
		case 2:                              // 困难
			bian_x = DIFFICULT_MAP_X;        // 地图的边界x
			bian_y = DIFFICULT_MAP_Y;        // 地图的边界y
			snake->speed = DIFFICULT_SPEED;  // 速度
			sleep_max = INIT_DIFFICULT_SPEED;// 速度的最低限制
			break;
		default:                             // 普通难度（默认）
		    bian_x = ORDINARY_MAP_X;         // 地图的边界x
			bian_y = ORDINARY_MAP_Y;         // 地图的边界y
			snake->speed = ORDINARY_SPEED;   // 速度
			sleep_max = INIT_ORDINARY_SPEED; // 速度的最低限制
	};
	huagame(snake);
	return snake;
}

// 自定义光标定位函数
void Location(int x, int y)
{
	COORD coord;
	coord.X=x;
	coord.Y=y;
	SetConsoleCursorPosition(hout,coord);
}
// 画游戏界面
void huagame(Head_Tail *snake)
{
	int x, y;
	Snake_body *temp =NULL;
	Location(0, 0);                          // 初始化光标位置
	for (y=0; y<bian_y; y++) {
		for (x=0; x<bian_x; x++) {
			if (x == 0 || x == bian_x-1 || y == 0 || y == bian_y-1)
			{
				map[y][x] = WALL; // 如果是边界就赋值为墙
				putchar(WALL_T);  // 画墙
			} else {
				map[y][x] = AIR;  // 否则赋值为空气
				putchar(AIR_T);   // 画空气
			}
		}
		putchar('\n');
	}
	for (temp = snake->head; temp != NULL; temp = temp->next)
	{
		y=temp->y, x=temp->x;
		map[y][x] = SNAKE_BODY;    // 蛇体
		Location(x, y);
		putchar(SNAKE_BODY_T);     // 画蛇体
	}
	Location(snake->head->x, snake->head->y);
	putchar(SNAKE_HEAD_T);         // 画蛇头
	Location(food->x, food->y);                    // 将光标移动到食物的坐标上
	putchar(produce_food[food->x % FOOD_MAX]);     // 画食物
}



// 蛇移动和移动后的判断函数 参数是头尾结构体指针
void Mobile(Head_Tail *snake, int i)
{
	int x=0, y=0, mode=0;
	x = snake->head->x + snake->direction->x;            // 蛇将要移动到的位置坐标
	y = snake->head->y + snake->direction->y;            // 蛇当前位置加要移动的距离
	Snake_body *temp = NULL, *p1 = NULL;
	unsigned int oldheadx = snake->head->x;
	unsigned int oldheady = snake->head->y;
	unsigned int oldtailx = snake->tail->x;
	unsigned int oldtaily = snake->tail->y;
	if (x == snake->head->next->x && y == snake->head->next->y)  //如果是向反方向移动就直接返回
	{
		snake->direction->x = olddir.x;                       // 将旧方向恢复
		snake->direction->y = olddir.y;                       // 将旧方向恢复
		return;
	}
	if (map[y][x] == WALL || map[y][x] == SNAKE_BODY) {  // 如果撞到墙或者吃到蛇身体就结束游戏
		snake = Game_Over(snake);
		return;
	} else if (i==1) {
		Fraction += 10;
	} else if (map[y][x] == AIR) {           // 如果是空气
		Location(oldtailx, oldtaily);        // 将光标定位到旧的蛇尾位置
		putchar(AIR_T);                      // 画空气
		map[oldtaily][oldtailx] = AIR;       // 在地图上清除蛇尾
		p1 = snake->tail;                    // p1为要释放内存的节点，存放蛇尾
		snake->tail = snake->tail->up;       // 将蛇尾赋值为蛇尾的前一个
		snake->tail->next = NULL;            // 将当前蛇尾的下一个赋值为空
		free(p1);                            // 释放蛇尾
	} else if (map[y][x] == FOOD) {          // 如果是食物
		Fraction++;                          // 如果是食物就分数加一
		snake->speed -= FOOD_SPEED;          // 同时速度增快
		Produce_food();                      // 同时再次生成食物
	} 
	map[y][x] = SNAKE_BODY;
	temp = (Snake_body*)malloc(sizeof(Snake_body));
	if (temp == NULL)
	{
		fprintf (stderr, "内存分配失败，退出游戏。");
		exit(1);
	}
	temp->x = x;                         // 新节点的x坐标
	temp->y = y;                         // 新节点的y坐标
	temp->up = NULL;                     // 新节点的上一个为空
	temp->next = snake->head;            // 新节点的下一个为当前蛇头
	snake->head->up = temp;              // 当前蛇头的上一个指向新节点
	snake->head = temp;                  // 将新节点代替蛇头
	Location(oldheadx, oldheady);        // 将光标定位到旧的蛇头位置
	putchar(SNAKE_BODY_T);               // 画蛇身
    // map[old_head_y][old_head_x] = SNAKE_BODY;  将旧蛇头的位置在地图上改变（仅适应蛇头在用数字表示时与蛇身不同时，在这里蛇头和身体用数字表达时相同，所以注释掉）
	Location(x, y);                      // 将光标定位到新的蛇头位置
	putchar(SNAKE_HEAD_T);               // 画蛇头
	map[y][x] = SNAKE_BODY;              // 在地图上添加蛇身
}

// 游戏结束
Head_Tail* Game_Over(Head_Tail *oldsnake)
{
	Head_Tail *snake = NULL;
	t:
	system ("cls");
	printf ("+---------------------------+\n"
			"|                           |\n"
			"|        游 戏 结 束        |\n"
			"|                           |\n"
			"|         分数：%-6d      |\n"
			"|     蛇身总长：%-6d      |\n"
			"|                           |\n"
			"|    按r重来，任意键退出    |\n"
			"|       按z回主菜单         |\n"
			"+---------------------------+\n", Fraction, Fraction + 5);
	memset(map, 0, sizeof(map));          // 将地图初始化
	switch	(getch())
	{
		case 'z' :  Interface(oldsnake);
		case 'r' : 	fre_game(oldsnake, 0);
					snake = initgame(snake);
					Produce_food();                // 生成食物
					return snake;
		default  :  printf ("\n是否退出游戏？\ny.退出\t其它键返回");
					if (getchar() == 'y')
						exit(1);
					else goto t;
	}
}

// 生成食物
void Produce_food(void)
{
	int x=0, y=0;
	srand((unsigned)time(NULL));
	while (1)
	{
		x = rand() % bian_x;
		y = rand() % bian_y;
		if (map[y][x] == WALL || map[y][x] == SNAKE_BODY);
		else
		{
			map[y][x] = FOOD;                     // 在地图上赋值食物
			Location(x, y);
			food->x = x;
			food->y = y;                          // 保存食物的坐标
			putchar(produce_food[x % FOOD_MAX]);  // 画食物
			return;
		}
	}
}

// 释放所有分配了的内存
void fre_game(Head_Tail *snake, int i)
{
	system("cls");
	printf ("正在释放内存...");
	free(snake->direction);
	Snake_body *temp = snake->head, *p1;
	while (temp != NULL)
	{
		p1 = temp;
		temp = temp->next;
		free(p1);
	}
	snake->head = NULL;
	snake->tail = NULL;
	free(snake);
	snake = NULL;
	free(food);
	if (i != 0)  // 检查是否要退出
	    exit(1);
}

// 游戏开始界面
void Interface(Head_Tail *snake)
{
	while (1)
	{
		system("cls");
		printf ("+----------------------------+\n"
				"|                            |\n"
				"|        贪   吃   蛇        |\n"
				"|                            |\n"
				"|        1.开始游戏          |\n"
				"|        2.帮    助          |\n"
				"|        3.设    置          |\n"
				"|        4.关    于          |\n"
				"|        q.退    出          |\n"
				"+----------------------------+\n");
		switch(getch()) {
			case '1': return;
			case '2': banzhu(); break;
			case '3': set();    break;
			case '4': guanyu(); break;
			case 'q': 
				if (snake == NULL) exit(1);
				else fre_game(snake, 1);
		}
	}
}

// 帮助界面
void banzhu(void)
{
	system("cls");
	printf ("+----------------------------+\n"
			"|                            |\n"
			"|        游 戏 帮 助         |\n"
			"|     w                      |\n"
			"|   a s d     为方向键       |\n"
			"|p键为暂停，暂停后任意键继续 |\n"
			"|q键退出(请不要强制退出，程序|\n"
			"|将释放游戏分配后的内存)     |\n"
			"|         任意键返回         |\n"
			"+----------------------------+\n");
	getch();
}

// 关于界面
void guanyu(void)
{
	system("cls");
	printf ("+----------------------------+\n"
			"|                            |\n"
			"|        关       于         |\n"
			"|                            |\n"
			"|        作者：筱傑          |\n"
			"|    制作时间：5小时         |\n"
			"|        版本：第一代        |\n"
			"|      作者QQ：840465812     |\n"
			"|        任意键返回          |\n"
			"+----------------------------+\n");
	getch();
}

// 设置
void set(void)
{
	char haedstr[3][5] = {"简单\0", "普通\0", "困难\0"};
	while (1)
	{
		system("cls");
		printf ("+----------------------------+\n"
				"|                            |\n"
				"|        设       置         |\n"
				"|                            |\n"
				"|        难度：%4s          |\n"
				"|        1.简单              |\n"
				"|        2.普通              |\n"
				"|        3.困难              |\n"
				"|        其它键返回          |\n"
				"+----------------------------+\n", haedstr[hard]);
		switch (getch())
		{
			case '1': hard = 0; break;
			case '2': hard = 1; break;
			case '3': hard = 2; break;
			default : return;
		}
	}
}

int main(void)
{
	Head_Tail *snake = NULL;
	int i=0;
	Interface(snake);
	snake = initgame(snake);
	Produce_food();                // 生成食物
	while(1)
	{
		olddir.x = snake->direction->x;       // 保存现在的方向到旧方向
		olddir.y = snake->direction->y;
		if (kbhit())
		{
			switch(getch())
			{
				case 'w': snake->direction->y = -1, snake->direction->x = 0; break;
				case 's': snake->direction->y = 1, snake->direction->x = 0; break;
				case 'a': snake->direction->y = 0, snake->direction->x = -1; break;
				case 'd': snake->direction->y = 0, snake->direction->x = 1; break;
				case 'q': snake = Game_Over(snake); break;
				case 'p': zantin(snake); break;
				case 'b': i=1; break;
			}
		}
		Mobile(snake, i);
		i=0;
		if (snake->speed > sleep_max)
			Sleep(snake->speed -= SPEED_JIAN);
		else Sleep(snake->speed);
	}
	return 0;
}

// 暂停界面
void zantin(Head_Tail *snake)
{
	system ("cls");
	printf ("+----------------------------+\n"
			"|                            |\n"
			"|      游戏正在暂停中        |\n"
			"|                            |\n"
			"|       当前分数：%-6d     |\n"
			"|       当前蛇长：%-6d     |\n"
			"|                            |\n"
			"|                            |\n"
			"|        任意键键返回        |\n"
			"+----------------------------+\n", Fraction, Fraction+5);
	getch();
	system("cls");
	huagame(snake);
}