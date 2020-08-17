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

int watermelon[3][3] = { 0, 0, 1, 0, 1, 1, 1, 1, 0 }; //우주선
int dish[3] = { 1, 1, 1 }; //착륙 지점
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
	printf("수박받기\n\n");
	printf("수박이 하늘에서 떨어진다! 받아줘!!\n\n");
	printf("초능력을 이용해서 수박을 내 접시위로 떨어트려줘!\n");
	printf("화살표로 움직이면 되고, 정확히 떨어트려줘야해!!\n\n");
	printf("수 박 모 양\t접시위치\n");
	printf("    □     \t□□□\n");
	printf("  □□\n");
	printf("□□  \n\n");
	printf("이름을 알려줘! : ");
	scanf("%s", &name);
	printf("좋아 %s, 아무키나 누르면 시작할게!!!!\n", name);
	getch();
	system("cls");
}

//접시 랜덤출력
int print_dish(void){
	int number;
	do{
		number = rand() % 30;
	} while (number % 2 == 0); //홀수여야한다
	gotoxy(number, 23);
	for (int i = 0; i < 3; i++)
		if (dish[i])
			printf("□");
	return number;
}

//수박출력
void print_watermelon(int x, int y){
	int count = 1;
	for (int i = 0; i < 3; i++)	{
		for (int j = 0; j < 3; j++)	{
			if (watermelon[i][j])
				printf("□");
			else
				printf("  ");
		}
		gotoxy(x, y + count++);
	}
}

//잔상 삭제
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

//이동하기
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

//떨어뜨리기
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

//성공여부출력
void didwin(int x){
	int result = print_dish(); //접시 맨 왼쪽 x 값
	int sResult = move_down(x); //우주선 맨 왼쪽 x 값
	if (sResult == result){
		gotoxy(1, 24);
		printf("%s 성공!!", name);
	}
	else if (sResult + 2 == result || sResult + 4 == result || sResult - 2 == result || sResult - 4 == result){
		gotoxy(1, 24);
		printf("뭐, 나쁘진 않네요 %s씨", name);
	}
	else{
		gotoxy(1, 24);
		printf("내 수박!! ㅠㅠㅠ %s 너 진짜 개못한다ㅡㅡ", name);
	}
}