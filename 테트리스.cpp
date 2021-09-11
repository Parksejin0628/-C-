#include<stdio.h>
#include<time.h>
#include<Windows.h>
#include<conio.h>

void settingBoard();
void printBoard(int blockCode);
int updateGame();

int board[24][12] = {0};

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

void printBoard(int blockCode)
{
	if(blockCode == -1)
	{
		printf("бс");
	}
	else if(blockCode == 0)
	{
		printf("  ");
	}
	
	return;
}

int updateGame()\
{
	return 0;
}
