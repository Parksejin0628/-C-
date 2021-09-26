#include<stdio.h>
#include<time.h>
#include<Windows.h>
#include<conio.h>
#include<stdlib.h>

#define BLOCK_CREATE_POS_X 5
#define BLOCK_CREATE_POS_Y 1

void settingBoard();									//게임 실행시 초기 세팅 
void printBoard(int blockCode, int x, int y);			//blockCode값에 따라 지정된 문자를 출력하는 함수 
int updateGame();										//지속적으로 호출되는 함수 
void goto_xy(int x, int y);								//커서위치를 옮기는 함수  
void createBlock();										//블록을 생성하는 함수 

int board[24][12] = {0};								//게임 보드판 변 
int blockExistence = 0;									//현재 플레이어가 조종하는 블록이 존재하는지 판단하는 변수 

int main(void)
{
	int playing = 1;
	settingBoard();
	while(playing)
	{
		playing = updateGame();
	}
	scanf("%d",&playing);
	
	return 0;
}

int updateGame()
{
	createBlock();
	
	return 0;
}

void settingBoard()
{
	for(int row=0; row<=21; row++)
	{
		board[row][0] = -1;
		board[row][11] = -1;
	}
	for(int column=0; column<=11; column++)
	{
		board[0][column] = -1;
		board[21][column] = -1;
	}
	
	for(int row=0; row<=21; row++)
	{
		for(int column=0; column<=11; column++)
		{
			printBoard(board[row][column]);
		}
		printf("\n");
	}
	
	return;
}

void printBoard(int blockCode, int x, int y)
{
	goto_xy(x, y); 
	
	if(blockCode == -1)
	{
		printf("□");
	}
	else if(blockCode == 0)
	{
		printf("  ");
	}
	else
	{
		printf("■");
	}
	
	return;
}

void goto_xy(int x, int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

void createBlock()
{
	int blockCode = 0;
	
	if(blockExistence == 1)
	{
		return;
	}
	blockCode = rand()%6 + 1;
	
	if(blockCode == 7)
	{
		for(int y = BLOCK_CREATE_POS_Y - 1; y <= BLOCK_CREATE_POS_Y + 1; y++)
		{
			for(int x = BLOCK_CREATE_POS_X - 1; x <= BLOCK_CREATE_POS_X + 1; x++)
			{
				if(block[blockCode][0][y][x] != 0)
				{
					board[y][x]
					printBoard(blockCode, x, y);
				}
			}
		}
	}
}


