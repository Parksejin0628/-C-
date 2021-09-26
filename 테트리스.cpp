#include<stdio.h>
#include<time.h>
#include<Windows.h>
#include<conio.h>
#include<stdlib.h>

#define BLOCK_CREATE_POS_X 5
#define BLOCK_CREATE_POS_Y 1

void settingBoard();									//���� ����� �ʱ� ���� 
void printBoard(int blockCode, int x, int y);			//blockCode���� ���� ������ ���ڸ� ����ϴ� �Լ� 
int updateGame();										//���������� ȣ��Ǵ� �Լ� 
void goto_xy(int x, int y);								//Ŀ����ġ�� �ű�� �Լ�  
void createBlock();										//����� �����ϴ� �Լ� 

int board[24][12] = {0};								//���� ������ �� 
int blockExistence = 0;									//���� �÷��̾ �����ϴ� ����� �����ϴ��� �Ǵ��ϴ� ���� 

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
		printf("��");
	}
	else if(blockCode == 0)
	{
		printf("  ");
	}
	else
	{
		printf("��");
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


