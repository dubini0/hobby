#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>

void intro_game(void);
void gotoxy(int x, int y);
int print_dish(void);
void print_watermelon(int x, int y);
void delete_watermelon(int x, int y);
void move_arrow_key(char key, int *x1, int x_b);
void didwin(int x);
int move_down(int x);

int watermelon[3][3] = { 0, 0, 1, 0, 1, 1, 1, 1, 0 }; //���ּ�
int dish[3] = { 1, 1, 1 }; //���� ����
char name[20];

int main(void){
	int x;
	do{
		x = rand() % 30;
	} while (x % 2 == 0);

	srand((unsigned)time(NULL));
	intro_game();
	didwin(x);
	gotoxy(1, 25);
	return 0;
}

void gotoxy(int x, int y){
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void intro_game(void){
	printf("���ڹޱ�\n\n");
	printf("������ �ϴÿ��� ��������! �޾���!!\n\n");
	printf("�ʴɷ��� �̿��ؼ� ������ �� �������� ����Ʈ����!\n");
	printf("ȭ��ǥ�� �����̸� �ǰ�, ��Ȯ�� ����Ʈ�������!!\n\n");
	printf("�� �� �� ��\t������ġ\n");
	printf("    ��     \t����\n");
	printf("  ���\n");
	printf("���  \n\n");
	printf("�̸��� �˷���! : ");
	scanf("%s", &name);
	printf("���� %s, �ƹ�Ű�� ������ �����Ұ�!!!!\n", name);
	getch();
	system("cls");
}

//���� �������
int print_dish(void){
	int number;
	do{
		number = rand() % 30;
	} while (number % 2 == 0); //Ȧ�������Ѵ�
	gotoxy(number, 23);
	for (int i = 0; i < 3; i++)
		if (dish[i])
			printf("��");
	return number;
}

//�������
void print_watermelon(int x, int y){
	int count = 1;
	for (int i = 0; i < 3; i++)	{
		for (int j = 0; j < 3; j++)	{
			if (watermelon[i][j])
				printf("��");
			else
				printf("  ");
		}
		gotoxy(x, y + count++);
	}
}

//�ܻ� ����
void delete_watermelon(int x, int y){
	int count = 1;
	gotoxy(x, y);
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			printf("  ");
		}
		gotoxy(x, y + count++);
	}
}

//�̵��ϱ�
void move_arrow_key(char key, int *x1, int x_b){
	switch (key){
	case 75:
		*x1 = *x1 - 2;
		if (*x1 < 1)
			*x1 = 1;
		break;
	case 77:
		*x1 = *x1 + 2;
		if (*x1 > x_b)
			*x1 = x_b;
		break;
	default:
		return;
	}
}

//����߸���
int move_down(int x){
	int y;
	char key;
	for (y = 1; y < 20; y++){
		gotoxy(x, y);
		print_watermelon(x, y);
		Sleep(100);
		delete_watermelon(x, y);
		Sleep(50);
		if (kbhit()){
			key = getch();
			move_arrow_key(key, &x, 30);
		}
	}
	gotoxy(x, y);
	print_watermelon(x, y);
	return x;
}

//�����������
void didwin(int x){
	int result = print_dish(); //���� �� ���� x ��
	int sResult = move_down(x); //���ּ� �� ���� x ��
	if (sResult == result){
		gotoxy(1, 24);
		printf("%s ����!!", name);
	}
	else if (sResult + 2 == result || sResult + 4 == result || sResult - 2 == result || sResult - 4 == result){
		gotoxy(1, 24);
		printf("��, ������ �ʳ׿� %s��", name);
	}
	else{
		gotoxy(1, 24);
		printf("�� ����!! �ФФ� %s �� ��¥ �����Ѵ٤Ѥ�", name);
	}
}