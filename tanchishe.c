#include "tanchishe.h"

// ���к��������͵ȶ���ͷ�ļ�����������Ϊ����ʵ��

// ��ʼ������
Head_Tail* initgame(Head_Tail *snake)
{
	hout = GetStdHandle(STD_OUTPUT_HANDLE);        // ��ñ�׼����ľ��
	CONSOLE_CURSOR_INFO cursor_info = {1,0};       // ���ع����������
	int x=0, y=0, i=0;
	Fraction = 0;                                  // ������ʼ��
	Snake_body *temp =NULL, *p1=NULL;
	system ("title ̰  ��  ��");
	system ("cls"); 
	SetConsoleCursorInfo(hout, &cursor_info);       // ���ع��
	snake = (Head_Tail*)malloc(sizeof(Head_Tail));
	if (snake == NULL)
	{
		fprintf (stderr, "�ڴ����ʧ�ܣ��˳���Ϸ��");
		exit(1);
	}
	snake->head = (Snake_body*)malloc(sizeof(Snake_body));
	if (snake->head == NULL)
	{
		fprintf (stderr, "�ڴ����ʧ�ܣ��˳���Ϸ��");
		exit(1);
	}
	snake->head->up = NULL;
	temp = snake->head;
	for (y=STARTED_Y, x=STARTED_X; x > STARTED_X - INIT_LENGTH; x--) // X�ı��Y����
	{
		temp->x = x;                                  // �����긳ֵ
		temp->y = y;
		p1 = (Snake_body*)malloc(sizeof(Snake_body)); // ��һ������
		if (p1 == NULL)
		{
			fprintf (stderr, "�ڴ����ʧ�ܣ��˳���Ϸ��");
			exit(1);
		}
		p1->up = temp;
		p1->next = NULL;
		temp->next = p1;
		temp = temp->next;
		p1 = NULL;
	}
	temp->x=x,temp->y=y;
	snake->tail = temp;       // ��β
	snake->direction = (Direction*)malloc(sizeof(Direction)); // ��һ������
	if (snake->head == NULL)
	{
		fprintf (stderr, "�ڴ����ʧ�ܣ��˳���Ϸ��");
		exit(1);
	}
	snake->direction->x = 1;  // ����xΪ1��ʾ���ң�0��ʾ��ת
	snake->direction->y = 0;
	food = (Coordinate*)malloc(sizeof(Coordinate));   // Ϊ���ʳ������Ľṹ������ڴ�
	
	switch (hard) {
		case 0:                              // ���Ѷ�
			bian_x = SIMPLE_MAP_X;           // ��ͼ�ı߽�x
			bian_y = SIMPLE_MAP_Y;           // ��ͼ�ı߽�y
			snake->speed = SIMPLE_SPEED;     // �ٶ�
			sleep_max = INIT_SIMPLE_SPEED;   // �ٶȵ��������
			break;
		case 2:                              // ����
			bian_x = DIFFICULT_MAP_X;        // ��ͼ�ı߽�x
			bian_y = DIFFICULT_MAP_Y;        // ��ͼ�ı߽�y
			snake->speed = DIFFICULT_SPEED;  // �ٶ�
			sleep_max = INIT_DIFFICULT_SPEED;// �ٶȵ��������
			break;
		default:                             // ��ͨ�Ѷȣ�Ĭ�ϣ�
		    bian_x = ORDINARY_MAP_X;         // ��ͼ�ı߽�x
			bian_y = ORDINARY_MAP_Y;         // ��ͼ�ı߽�y
			snake->speed = ORDINARY_SPEED;   // �ٶ�
			sleep_max = INIT_ORDINARY_SPEED; // �ٶȵ��������
	};
	huagame(snake);
	return snake;
}

// �Զ����궨λ����
void Location(int x, int y)
{
	COORD coord;
	coord.X=x;
	coord.Y=y;
	SetConsoleCursorPosition(hout,coord);
}
// ����Ϸ����
void huagame(Head_Tail *snake)
{
	int x, y;
	Snake_body *temp =NULL;
	Location(0, 0);                          // ��ʼ�����λ��
	for (y=0; y<bian_y; y++) {
		for (x=0; x<bian_x; x++) {
			if (x == 0 || x == bian_x-1 || y == 0 || y == bian_y-1)
			{
				map[y][x] = WALL; // ����Ǳ߽�͸�ֵΪǽ
				putchar(WALL_T);  // ��ǽ
			} else {
				map[y][x] = AIR;  // ����ֵΪ����
				putchar(AIR_T);   // ������
			}
		}
		putchar('\n');
	}
	for (temp = snake->head; temp != NULL; temp = temp->next)
	{
		y=temp->y, x=temp->x;
		map[y][x] = SNAKE_BODY;    // ����
		Location(x, y);
		putchar(SNAKE_BODY_T);     // ������
	}
	Location(snake->head->x, snake->head->y);
	putchar(SNAKE_HEAD_T);         // ����ͷ
	Location(food->x, food->y);                    // ������ƶ���ʳ���������
	putchar(produce_food[food->x % FOOD_MAX]);     // ��ʳ��
}



// ���ƶ����ƶ�����жϺ��� ������ͷβ�ṹ��ָ��
void Mobile(Head_Tail *snake, int i)
{
	int x=0, y=0, mode=0;
	x = snake->head->x + snake->direction->x;            // �߽�Ҫ�ƶ�����λ������
	y = snake->head->y + snake->direction->y;            // �ߵ�ǰλ�ü�Ҫ�ƶ��ľ���
	Snake_body *temp = NULL, *p1 = NULL;
	unsigned int oldheadx = snake->head->x;
	unsigned int oldheady = snake->head->y;
	unsigned int oldtailx = snake->tail->x;
	unsigned int oldtaily = snake->tail->y;
	if (x == snake->head->next->x && y == snake->head->next->y)  //������򷴷����ƶ���ֱ�ӷ���
	{
		snake->direction->x = olddir.x;                       // ���ɷ���ָ�
		snake->direction->y = olddir.y;                       // ���ɷ���ָ�
		return;
	}
	if (map[y][x] == WALL || map[y][x] == SNAKE_BODY) {  // ���ײ��ǽ���߳Ե�������ͽ�����Ϸ
		snake = Game_Over(snake);
		return;
	} else if (i==1) {
		Fraction += 10;
	} else if (map[y][x] == AIR) {           // ����ǿ���
		Location(oldtailx, oldtaily);        // ����궨λ���ɵ���βλ��
		putchar(AIR_T);                      // ������
		map[oldtaily][oldtailx] = AIR;       // �ڵ�ͼ�������β
		p1 = snake->tail;                    // p1ΪҪ�ͷ��ڴ�Ľڵ㣬�����β
		snake->tail = snake->tail->up;       // ����β��ֵΪ��β��ǰһ��
		snake->tail->next = NULL;            // ����ǰ��β����һ����ֵΪ��
		free(p1);                            // �ͷ���β
	} else if (map[y][x] == FOOD) {          // �����ʳ��
		Fraction++;                          // �����ʳ��ͷ�����һ
		snake->speed -= FOOD_SPEED;          // ͬʱ�ٶ�����
		Produce_food();                      // ͬʱ�ٴ�����ʳ��
	} 
	map[y][x] = SNAKE_BODY;
	temp = (Snake_body*)malloc(sizeof(Snake_body));
	if (temp == NULL)
	{
		fprintf (stderr, "�ڴ����ʧ�ܣ��˳���Ϸ��");
		exit(1);
	}
	temp->x = x;                         // �½ڵ��x����
	temp->y = y;                         // �½ڵ��y����
	temp->up = NULL;                     // �½ڵ����һ��Ϊ��
	temp->next = snake->head;            // �½ڵ����һ��Ϊ��ǰ��ͷ
	snake->head->up = temp;              // ��ǰ��ͷ����һ��ָ���½ڵ�
	snake->head = temp;                  // ���½ڵ������ͷ
	Location(oldheadx, oldheady);        // ����궨λ���ɵ���ͷλ��
	putchar(SNAKE_BODY_T);               // ������
    // map[old_head_y][old_head_x] = SNAKE_BODY;  ������ͷ��λ���ڵ�ͼ�ϸı䣨����Ӧ��ͷ�������ֱ�ʾʱ������ͬʱ����������ͷ�����������ֱ��ʱ��ͬ������ע�͵���
	Location(x, y);                      // ����궨λ���µ���ͷλ��
	putchar(SNAKE_HEAD_T);               // ����ͷ
	map[y][x] = SNAKE_BODY;              // �ڵ�ͼ���������
}

// ��Ϸ����
Head_Tail* Game_Over(Head_Tail *oldsnake)
{
	Head_Tail *snake = NULL;
	t:
	system ("cls");
	printf ("+---------------------------+\n"
			"|                           |\n"
			"|        �� Ϸ �� ��        |\n"
			"|                           |\n"
			"|         ������%-6d      |\n"
			"|     �����ܳ���%-6d      |\n"
			"|                           |\n"
			"|    ��r������������˳�    |\n"
			"|       ��z�����˵�         |\n"
			"+---------------------------+\n", Fraction, Fraction + 5);
	memset(map, 0, sizeof(map));          // ����ͼ��ʼ��
	switch	(getch())
	{
		case 'z' :  Interface(oldsnake);
		case 'r' : 	fre_game(oldsnake, 0);
					snake = initgame(snake);
					Produce_food();                // ����ʳ��
					return snake;
		default  :  printf ("\n�Ƿ��˳���Ϸ��\ny.�˳�\t����������");
					if (getchar() == 'y')
						exit(1);
					else goto t;
	}
}

// ����ʳ��
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
			map[y][x] = FOOD;                     // �ڵ�ͼ�ϸ�ֵʳ��
			Location(x, y);
			food->x = x;
			food->y = y;                          // ����ʳ�������
			putchar(produce_food[x % FOOD_MAX]);  // ��ʳ��
			return;
		}
	}
}

// �ͷ����з����˵��ڴ�
void fre_game(Head_Tail *snake, int i)
{
	system("cls");
	printf ("�����ͷ��ڴ�...");
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
	if (i != 0)  // ����Ƿ�Ҫ�˳�
	    exit(1);
}

// ��Ϸ��ʼ����
void Interface(Head_Tail *snake)
{
	while (1)
	{
		system("cls");
		printf ("+----------------------------+\n"
				"|                            |\n"
				"|        ̰   ��   ��        |\n"
				"|                            |\n"
				"|        1.��ʼ��Ϸ          |\n"
				"|        2.��    ��          |\n"
				"|        3.��    ��          |\n"
				"|        4.��    ��          |\n"
				"|        q.��    ��          |\n"
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

// ��������
void banzhu(void)
{
	system("cls");
	printf ("+----------------------------+\n"
			"|                            |\n"
			"|        �� Ϸ �� ��         |\n"
			"|     w                      |\n"
			"|   a s d     Ϊ�����       |\n"
			"|p��Ϊ��ͣ����ͣ����������� |\n"
			"|q���˳�(�벻Ҫǿ���˳�������|\n"
			"|���ͷ���Ϸ�������ڴ�)     |\n"
			"|         ���������         |\n"
			"+----------------------------+\n");
	getch();
}

// ���ڽ���
void guanyu(void)
{
	system("cls");
	printf ("+----------------------------+\n"
			"|                            |\n"
			"|        ��       ��         |\n"
			"|                            |\n"
			"|        ���ߣ����          |\n"
			"|    ����ʱ�䣺5Сʱ         |\n"
			"|        �汾����һ��        |\n"
			"|      ����QQ��840465812     |\n"
			"|        ���������          |\n"
			"+----------------------------+\n");
	getch();
}

// ����
void set(void)
{
	char haedstr[3][5] = {"��\0", "��ͨ\0", "����\0"};
	while (1)
	{
		system("cls");
		printf ("+----------------------------+\n"
				"|                            |\n"
				"|        ��       ��         |\n"
				"|                            |\n"
				"|        �Ѷȣ�%4s          |\n"
				"|        1.��              |\n"
				"|        2.��ͨ              |\n"
				"|        3.����              |\n"
				"|        ����������          |\n"
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
	Produce_food();                // ����ʳ��
	while(1)
	{
		olddir.x = snake->direction->x;       // �������ڵķ��򵽾ɷ���
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

// ��ͣ����
void zantin(Head_Tail *snake)
{
	system ("cls");
	printf ("+----------------------------+\n"
			"|                            |\n"
			"|      ��Ϸ������ͣ��        |\n"
			"|                            |\n"
			"|       ��ǰ������%-6d     |\n"
			"|       ��ǰ�߳���%-6d     |\n"
			"|                            |\n"
			"|                            |\n"
			"|        �����������        |\n"
			"+----------------------------+\n", Fraction, Fraction+5);
	getch();
	system("cls");
	huagame(snake);
}