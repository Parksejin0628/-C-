#include<stdio.h>
#include<time.h>
#include<Windows.h>
#include<conio.h>
#include<stdlib.h>

#define BLOCK_CREATE_POS_X 5
#define BLOCK_CREATE_POS_Y 1

typedef struct Block{
	int x;
	int y;
	int code;
}block;

void settingGame();														//���� ����� �ʱ� ���� 
void printBoard(int blockCode, int x, int y);							//blockCode���� ���� ������ ���ڸ� ����ϴ� �Լ� 
int updateGame();														//���������� ȣ��Ǵ� �Լ� 
void goto_xy(int x, int y);												//Ŀ����ġ�� �ű�� �Լ�  
void createBlock();														//����� �����ϴ� �Լ� 
void settingTetromino();												//�̳� ����� ���� 
void fallingBlock();													//���� �ð����� ����� �����ϴ� ���� �����ϴ� �Լ�  
void softDrop();														//����Ʈ ����� �����ϴ� �Լ� 
int blockMoveSimulation(block blockQueue[4], int moveX, int moveY); 	//����� �����̴� ���� �ùķ��̼��ؼ� �Ұ����� ��� 0, ������ ��� 1�� �����ϰ� preloadBlockQueue�� ������Ʈ ���ִ� �Լ�  
void inputPreloadBlockQueue(int index, int code, int x, int y);			//preloadBlockQueue�� ������ �Է��ϴ� �Լ�
void reloadBlock();														//���� �������� ����� ��ǥ�� �ֽ�ȭ���ִ� �Լ� 
void inputKey();

int board[24][12] = {0};												//���� ������ ���� 
int blockExistence = 0;													//���� �÷��̾ �����ϴ� ����� �����ϴ��� �Ǵ��ϴ� ���� 
int tetromino[8][4][4][4] = {0};										//��Ʈ������ �̳� ����� �����ϴ� ���� 
block blockQueue[4] = {0};												//���� �÷��̾ �����ϰ� �ִ� ����� ������ ���� ���� 
block preloadBlockQueue[4] = {0};										//����� �̵������� ��ǥ�� ������ ��� �ִ� ���� 
time_t gameStartTime = 0;
time_t criteriaTime = 0;
time_t moveCriteriaTime = 0;
time_t nowTime = 0;
time_t delayTime = 100;
time_t moveDelayTime = 50;
time_t decreaseTime = 0;

int main(void)
{
	int playing = 1;
	settingGame();
	while(playing)
	{
		playing = updateGame();
	}
	scanf("%d",&playing);
	
	return 0;
}

int updateGame()
{
	if(blockExistence == 0)
	{
		createBlock();
	}

	if(blockExistence == 1)
	{
		fallingBlock();
		inputKey();
	}

	
	return 1;
}

void settingGame()
{
	for(int row=2; row<=23; row++)
	{
		board[row][0] = -1;
		board[row][11] = -1;
	}
	for(int column=0; column<=11; column++)
	{
		//board[0][column] = -1;
		board[23][column] = -1;
	}
	
	for(int row=0; row<=23; row++)
	{
		for(int column=0; column<=11; column++)
		{
			printBoard(board[row][column], column, row);
		}
		printf("\n");
	}
	settingTetromino();
	gameStartTime = clock();
	criteriaTime = clock();
	moveCriteriaTime = clock();
	
	
	
	return;
}

void printBoard(int blockCode, int x, int y)
{
	x*=2;
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


void createBlock()
{
	int blockCode = 0;
	int remainBlock = 3;
	int X = 0;
	int Y = 0;
	
	if(blockExistence == 1)
	{
		return;
	}
	srand((unsigned int)time(NULL));
	blockCode = ((int)rand() % 7) + 1;
	//printf("\n blockCode : %d\n", blockCode);
	for(int y = 0; y <= 3; y++)
	{
		for(int x = 0; x <= 3; x++)
		{
			if(tetromino[blockCode][0][y][x] != 0)
			{
				X = BLOCK_CREATE_POS_X - 1 + x;
				Y = BLOCK_CREATE_POS_Y - 1 + y;
				board[Y][X] = blockCode;
				printBoard(blockCode, X, Y);
				blockQueue[remainBlock].x = X;
				blockQueue[remainBlock].y = Y;
				blockQueue[remainBlock].code = blockCode;
				remainBlock--;
			}
		}
	}
	blockExistence = 1;
	
	return;
}

void fallingBlock()
{
	nowTime = clock();
	if(nowTime - criteriaTime >= delayTime && delayTime > 0)
	{
		criteriaTime = clock();
		delayTime -= decreaseTime;
		softDrop();
	} 
}

void softDrop()
{
	
	int X = 0;
	int Y = 0;
	int CODE = 0;
	/*
	for(int i=0; i<=3; i++)
	{
		X = blockQueue[i].x;
		Y = blockQueue[i].y;
		CODE = blockQueue[i].code;
		
		board[Y+1][X] = CODE;
		printBoard(CODE, X, Y+1);
		printBoard(0, X, Y);
		blockQueue[i].y = Y+1;
	}
	*/
	
	int temp = blockMoveSimulation(blockQueue, 0, 1);
	if(temp == 0)
	{
		for(int i=0; i<=3; i++)
		{
			X = blockQueue[i].x;
			Y = blockQueue[i].y;
			CODE = blockQueue[i].code;
			
			inputPreloadBlockQueue(i,CODE + 7, X, Y);
		}
		reloadBlock();
		blockExistence = 0;
	}
	else
	{
		reloadBlock();
	}
} 

int blockMoveSimulation(block blockQueue[4], int moveX, int moveY)
{
	int X = 0;
	int Y = 0;
	int CODE = 0;
	
	if(moveX != 0)
	{
		for(int i=0; i<=3; i++)
		{
			X = blockQueue[i].x;
			Y = blockQueue[i].y;
			CODE = blockQueue[i].code;
			
			if(board[Y][X + moveX] != 0 && board[Y][X + moveX] != CODE)
			{
				return 0;
			}
			inputPreloadBlockQueue(i, CODE, X + moveX, Y);
		}
	}
	if(moveY != 0)
	{
		for(int i=0; i<=3; i++)
		{
			X = blockQueue[i].x;
			Y = blockQueue[i].y;
			CODE = blockQueue[i].code;
			
			if(board[Y + moveY][X] != 0 && board[Y + moveY][X] != CODE)
			{
				goto_xy(0, 25);
				printf("crush!, x : %d, y : %d �� �ڵ尪 : %d", X, Y + moveY, board[Y + moveY][X]);
				return 0;
			}
			inputPreloadBlockQueue(i, CODE, X, Y + moveY);
		}
	}
	
	return 1;
}

void inputPreloadBlockQueue(int index, int code, int x, int y)
{
	preloadBlockQueue[index].code = code;
	preloadBlockQueue[index].x = x;
	preloadBlockQueue[index].y = y;
}

void reloadBlock()
{
	int X = 0;
	int Y = 0;
	int CODE = 0;
	
	for(int i=0; i<=3; i++)
	{
		X = blockQueue[i].x;
		Y = blockQueue[i].y;
		CODE = blockQueue[i].code;
		
		board[Y][X] = 0;
		printBoard(0, X, Y); 
	}
	for(int i=0; i<=3; i++)
	{
		X = preloadBlockQueue[i].x;
		Y = preloadBlockQueue[i].y;
		CODE = preloadBlockQueue[i].code;
		
		board[Y][X] = CODE;
		printBoard(CODE, X, Y); 
		blockQueue[i] = preloadBlockQueue[i];
	}
}

void goto_xy(int x, int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

void inputKey()
{
	nowTime = clock();
	if(nowTime - moveCriteriaTime < moveDelayTime)
	{
		return;
	} 
	moveCriteriaTime = clock();
	
	int temp = 0;
	int X = 0;
	int Y = 0;
	int CODE = 0;
	if(GetAsyncKeyState(VK_LEFT))
	{
		temp = blockMoveSimulation(blockQueue, -1, 0);
		if(temp != 0)
		{
			reloadBlock();
		}
	}
	else if(GetAsyncKeyState(VK_RIGHT))
	{
		temp = blockMoveSimulation(blockQueue, 1, 0);
		if(temp != 0)
		{
			reloadBlock();
		}
	}
	else if(GetAsyncKeyState(VK_DOWN))
	{
		softDrop();
	}
}

void settingTetromino()
{
	//Z�̳�  
	tetromino[1][0][0][0] = 1;
	tetromino[1][0][0][1] = 1;
	tetromino[1][0][1][1] = 1;
	tetromino[1][0][1][2] = 1;

	tetromino[1][1][0][2] = 1;
	tetromino[1][1][1][1] = 1;
	tetromino[1][1][1][2] = 1;
	tetromino[1][1][2][1] = 1;
	
	tetromino[1][2][1][0] = 1;
	tetromino[1][2][1][1] = 1;
	tetromino[1][2][2][1] = 1;
	tetromino[1][2][2][2] = 1;
	
	tetromino[1][3][0][1] = 1;
	tetromino[1][3][1][0] = 1;
	tetromino[1][3][1][1] = 1;
	tetromino[1][3][2][0] = 1;
	
	//L�̳�  
	tetromino[2][0][0][2] = 1;
	tetromino[2][0][1][0] = 1;
	tetromino[2][0][1][1] = 1;
	tetromino[2][0][1][2] = 1;
	
	tetromino[2][1][0][1] = 1;
	tetromino[2][1][1][1] = 1;
	tetromino[2][1][2][1] = 1;
	tetromino[2][1][2][2] = 1;

	tetromino[2][2][1][0] = 1;
	tetromino[2][2][1][1] = 1;
	tetromino[2][2][1][2] = 1;
	tetromino[2][2][2][0] = 1;
	
	tetromino[2][3][0][0] = 1;
	tetromino[2][3][0][1] = 1;
	tetromino[2][3][1][1] = 1;
	tetromino[2][3][2][1] = 1;
	
	//O�̳�  
	tetromino[3][0][0][1] = 1;
	tetromino[3][0][0][2] = 1;
	tetromino[3][0][1][1] = 1;
	tetromino[3][0][1][2] = 1;
	
	tetromino[3][1][0][1] = 1;
	tetromino[3][1][0][2] = 1;
	tetromino[3][1][1][1] = 1;
	tetromino[3][1][1][2] = 1;
	
	tetromino[3][2][0][1] = 1;
	tetromino[3][2][0][2] = 1;
	tetromino[3][2][1][1] = 1;
	tetromino[3][2][1][2] = 1;
	
	tetromino[3][3][0][1] = 1;
	tetromino[3][3][0][2] = 1;
	tetromino[3][3][1][1] = 1;
	tetromino[3][3][1][2] = 1;

	//S�̳�  
	tetromino[4][0][0][1] = 1;
	tetromino[4][0][0][2] = 1;
	tetromino[4][0][1][0] = 1;
	tetromino[4][0][1][1] = 1;
	
	tetromino[4][1][0][0] = 1;
	tetromino[4][1][1][0] = 1;
	tetromino[4][1][1][1] = 1;
	tetromino[4][1][2][1] = 1;
	
	tetromino[4][2][1][1] = 1;
	tetromino[4][2][1][2] = 1;
	tetromino[4][2][2][0] = 1;
	tetromino[4][2][2][1] = 1;
	
	tetromino[4][3][0][0] = 1;
	tetromino[4][3][1][0] = 1;
	tetromino[4][3][1][1] = 1;
	tetromino[4][3][2][1] = 1;
	
	//J�̳�  
	tetromino[5][0][0][0] = 1;
	tetromino[5][0][1][0] = 1;
	tetromino[5][0][1][1] = 1;
	tetromino[5][0][1][2] = 1;
	
	tetromino[5][1][0][1] = 1;
	tetromino[5][1][0][2] = 1;
	tetromino[5][1][1][1] = 1;
	tetromino[5][1][2][1] = 1;
	
	tetromino[5][2][1][0] = 1;
	tetromino[5][2][1][1] = 1;
	tetromino[5][2][1][2] = 1;
	tetromino[5][2][2][2] = 1;
	
	tetromino[5][3][0][1] = 1;
	tetromino[5][3][1][1] = 1;
	tetromino[5][3][2][0] = 1;
	tetromino[5][3][2][1] = 1;
	
	//T�̳�  
	tetromino[6][0][0][1] = 1;
	tetromino[6][0][1][0] = 1;
	tetromino[6][0][1][1] = 1;
	tetromino[6][0][1][2] = 1;
	
	tetromino[6][1][0][1] = 1;
	tetromino[6][1][1][1] = 1;
	tetromino[6][1][1][2] = 1;
	tetromino[6][1][2][1] = 1;
	
	tetromino[6][2][1][0] = 1;
	tetromino[6][2][1][1] = 1;
	tetromino[6][2][1][2] = 1;
	tetromino[6][2][2][1] = 1;
	
	tetromino[6][3][0][1] = 1;
	tetromino[6][3][1][0] = 1;
	tetromino[6][3][1][1] = 1;
	tetromino[6][3][2][1] = 1;
	
	//I�̳�  
	tetromino[7][0][1][0] = 1;
	tetromino[7][0][1][1] = 1;
	tetromino[7][0][1][2] = 1;
	tetromino[7][0][1][3] = 1;
	
	tetromino[7][1][0][2] = 1;
	tetromino[7][1][1][2] = 1;
	tetromino[7][1][2][2] = 1;
	tetromino[7][1][3][2] = 1;
	
	tetromino[7][2][2][0] = 1;
	tetromino[7][2][2][1] = 1;
	tetromino[7][2][2][2] = 1;
	tetromino[7][2][2][3] = 1;
	
	tetromino[7][3][0][1] = 1;
	tetromino[7][3][1][1] = 1;
	tetromino[7][3][2][1] = 1;
	tetromino[7][3][3][1] = 1;
	
	return;
}

