#include<stdio.h>
#include<time.h>
#include<Windows.h>
#include<conio.h>
#include<stdlib.h>

#define BLOCK_CREATE_POS_X 5
#define BLOCK_CREATE_POS_Y 2
#define KEY_DOWN 0x8000
#define KEY_UP 0x0001
#define KEY_KEEP 0x8001
#define BOARD_POS_X 5

typedef struct Block{
	int x;
	int y;
	int code;
}block;

void settingGame();														//���� ����� �ʱ� ���� 
void printBoard(int blockCode, double x, int y);						//blockCode���� ���� ������ ���ڸ� ����ϴ� �Լ� 
int updateGame();														//���������� ȣ��Ǵ� �Լ� 
void goto_xy(int x, int y);												//Ŀ����ġ�� �ű�� �Լ�  
void createBlock(int code);												//����� �����ϴ� �Լ� 
void settingTetromino();												//�̳� ����� ���� 
void fallingBlock();													//���� �ð����� ����� �����ϴ� ���� �����ϴ� �Լ�  
void softDrop();														//����Ʈ ����� �����ϴ� �Լ� 
int blockMoveSimulation(block blockQueue[4], int moveX, int moveY); 	//����� �����̴� ���� �ùķ��̼��ؼ� �Ұ����� ��� 0, ������ ��� 1�� �����ϰ� preloadBlockQueue�� ������Ʈ ���ִ� �Լ�  
void inputPreloadBlockQueue(int index, int code, int x, int y);			//preloadBlockQueue�� ������ �Է��ϴ� �Լ�
void reloadBlock();														//���� �������� ����� ��ǥ�� �ֽ�ȭ���ִ� �Լ� 
int blockRotationSimulation(block blockQueue[4], int rotDir);			//����� ȸ����Ű�� ���� �ùķ��̼����ִ� �Լ� 
void inputKey();														//Ű �Է��� �޴� �Լ� 
void landBlock(block blockQueue[4], int decreseY);						//����� ��ġ�ϴ� �Լ�
void checkLine(int line);												//y��° ���� ���� á���� Ȯ���ϴ� �Լ� 
void hardDrop();														//�ϵ� ����� �����ϴ� �Լ�
void printUI();															//UI�� ����ϴ� �Լ� 
void createBag();														//7bag�� �����ϴ� �Լ�
void hold();															//hold�� ������ �Լ� 
int importNext();														//next���� ���� ����� �����ϰ�, next�� �ֽ�ȭ �ϴ� �Լ� 

int board[24][12] = {0};												//���� ������ ���� 
int blockExistence = 0;													//���� �÷��̾ �����ϴ� ����� �����ϴ��� �Ǵ��ϴ� ���� 
block tetromino[8][4][4] = {0};											//��Ʈ������ �̳� ����� �����ϴ� ���� [����ڵ�][ȸ��][���] 
block blockQueue[4] = {0};												//���� �÷��̾ �����ϰ� �ִ� ����� ������ ���� ���� 
block preloadBlockQueue[4] = {0};										//����� �̵������� ��ǥ�� ������ ��� �ִ� ���� 
time_t gameStartTime = 0;												//������ ������ �ð��� �����ϴ� ���� 
time_t fallingCriteriaTime = 0;											//���� ������ ������ �Ǿ��ִ� ���� 
time_t moveCriteriaTime = 0;											//������� �������� ������ �Ǿ��ִ� ����  
time_t rotCriteriaTime = 0;												//���ȸ�� �������� ������ �Ǿ��ִ� ���� 
time_t nowTime = 0;														//����ð� ��, ���� ���� �� �󸶳� ���������� �����ϴ� ���� 
time_t fallingDelayTime = 1000;											//��ϳ��� ������ �ð�  
time_t moveDelayTime = 100;												//����̵� ������ �ð� 
time_t rotDelayTime = 100;												//���ȸ�� ������ �ð�  
time_t fallingDelayDecreaseTime = 5;									//��ϳ��� ������ ���ҷ�
int blockRot = 0;														//����� ȸ�� ���¸� �����ϴ� ����			
int playing = 1; 														//�÷��� ���� 
int clearLine = 0;														//������ ���� ��  
int targetLine = 40;													//��ǥ ���� �� 
int bag7[7] = {0};														//7bag���� �����ϴ� �Լ� 
int next[5] = {0};												//next���� �����ϴ� �Լ� 
int bagIndex = 5;														//7bag�� �ε��� 
int nextFrontIndex = 0;													//nextQueue�� frontIndex 
int nextRearIndex = 4;													//nextQueue�� reatIndex
int holdValue = 0; 

int main(void)
{
	settingGame();
	while(playing)
	{
		updateGame();
	}
	scanf("%d",&playing);
	
	return 0;
}

int updateGame()
{
	nowTime = clock();
	createBlock(0);
	fallingBlock();
	inputKey();
	printUI();

	
	return 1;
}

void settingGame()
{
//�ʱ� ���� ���� 
	//board���� �ʱ� ���� 
	for(int row=0; row<=23; row++)
	{
		board[row][0] = -1;
		board[row][11] = -1;
	}
	for(int column=0; column<=11; column++)
	{
		//board[0][column] = -1;
		board[23][column] = -1;
	}
	//���� �õ尪 ���� 
	srand((unsigned int)time(NULL));
	
	//��Ʈ�ι̳� ���� ���� 
	settingTetromino();
	
	//�ʱ� �ð����� ���� 
	gameStartTime = clock();
	fallingCriteriaTime = clock();
	moveCriteriaTime = clock();
	rotCriteriaTime = clock();
	
	//�ʱ� next�� ���� 
	createBag();
	for(int i=0; i<5; i++)
	{
		next[i] = bag7[i];
	}
	
	
	
//�ʱ� ȭ����� ���� 
	//������ ���� 
	for(int row=3; row<=23; row++)
	{
		for(int column=0; column<=11; column++)
		{
			printBoard(board[row][column], column + BOARD_POS_X, row);
		}
		printf("\n");
	}
	
	//holdĭ ���� 
	goto_xy(0, 3);
	printf("���hold��\n");
	printf("��\n");
	printf("��\n");
	printf("������\n");
	
	//nextĭ ���� 
	for(int i=3; i<=18; i++)
	{
		goto_xy(34, i);
		if(i == 3)
		{
			printf("��next���");
		}
		else if(i==18)
		{
			printf("������");
		}
		else if((i-3)%3 == 0)
		{
			printf("--------��");
		}
		else
		{
			printBoard(-1, 21, i);
		}
	}
	
	
	return;
}

void printBoard(int blockCode, double x, int y)
{
	x*=2;
	goto_xy(x, y); 
	
	//��� �ڵ忡 ���� ��� 
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


void createBlock(int code)
{
	//�������� ����� ���� ��� ����� �������� �ʴ´�. 
	if(blockExistence == 1)
	{
		return;
	}
	
	int blockCode = 0;
	int X = 0;
	int Y = 0;
	
	//���ο� ����� �����ϴ� ��� 
	if(code == 0) 
	{
		blockCode = importNext();
	}
	//������ ��� (�ַ� hold�� �ִ� ���)�� �����ϴ� ��� 
	else
	{
		blockCode = code;
	}
	// ���ο� ����� ��ǥ ���� �� ��� ��� 
	for(int i=0; i<=3; i++)
	{
		X = BLOCK_CREATE_POS_X + tetromino[blockCode][0][i].x;
		Y = BLOCK_CREATE_POS_Y + tetromino[blockCode][0][i].y;
		board[Y][X] = blockCode;
		blockQueue[i].x = X;
		blockQueue[i].y = Y;
		blockQueue[i].code = blockCode;
		printBoard(blockCode, X + BOARD_POS_X, Y);
		
		//inputPreloadBlockQueue(i, blockCode, X, Y); 
	}
	//reloadBlock();
	blockExistence = 1;
	blockRot = 0; 
	
	return;
}

void fallingBlock()
{
	if(blockExistence == 0)
	{
		return;
	}
	if(nowTime - fallingCriteriaTime >= fallingDelayTime)
	{
		fallingCriteriaTime = clock();
		softDrop();
	} 
	
	return;
}

void softDrop()
{
	
	int X = 0;
	int Y = 0;
	int CODE = blockQueue[0].code;
	int temp = blockMoveSimulation(blockQueue, 0, 1);
	if(temp == 0)
	{
		landBlock(blockQueue, 0);
		
		return;
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
	int CODE = blockQueue[0].code;;
	
	if(moveX != 0)
	{
		for(int i=0; i<=3; i++)
		{
			X = blockQueue[i].x;
			Y = blockQueue[i].y;
			
			//goto_xy(0, 25+i);
			//printf("                                                                                          ");
			//goto_xy(0, 25+i);
			//printf("���� x : %d, ���� y : %d, moveX : %d, moveY : %d / �̵� x�� : %d, �̵� y�� : %d\n", X, Y, moveX, moveY, X + moveX, Y + moveY);
			
			if(board[Y][X + moveX] != 0 && board[Y][X + moveX] != CODE)
			{
				return 0;
			}
			inputPreloadBlockQueue(i, CODE, X + moveX, Y);
		}
		
	}
	else if(moveY != 0)
	{
		for(int i=0; i<=3; i++)
		{
			X = blockQueue[i].x;
			Y = blockQueue[i].y;
			
			//goto_xy(0, 25+i);
			//printf("                                                                                          ");
			//goto_xy(0, 25+i);
			//printf("���� x : %d, ���� y : %d, moveX : %d, moveY : %d / �̵� x�� : %d, �̵� y�� : %d\n", X, Y, moveX, moveY, X + moveX, Y + moveY);
			
			if(board[Y + moveY][X] != 0 && board[Y + moveY][X] != CODE)
			{
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
	int CODE = blockQueue[0].code;
	
	for(int i=0; i<=3; i++)
	{
		X = blockQueue[i].x;
		Y = blockQueue[i].y;
		
		board[Y][X] = 0;
		printBoard(0, X + BOARD_POS_X, Y); 
	}
	
	CODE = preloadBlockQueue[0].code;
	for(int i=0; i<=3; i++)
	{
		X = preloadBlockQueue[i].x;
		Y = preloadBlockQueue[i].y;
		
		board[Y][X] = CODE;
		printBoard(CODE, X + BOARD_POS_X, Y); 
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
	if(blockExistence == 0)
	{
		return;
	}
	
	
	int temp = 0;
	int X = 0;
	int Y = 0;
	int CODE = 0;
	int keycode_z = 0X5a;
	int keycode_x = 0x58;
	int keycode_c = 0x43;
	if(GetAsyncKeyState(VK_LEFT))
	{
		if(nowTime - moveCriteriaTime < moveDelayTime)
		{
			return;
		} 
		moveCriteriaTime = clock();
		temp = blockMoveSimulation(blockQueue, -1, 0);
		if(temp != 0)
		{
			reloadBlock();
		}
	}
	if(GetAsyncKeyState(VK_RIGHT))
	{
		if(nowTime - moveCriteriaTime < moveDelayTime)
		{
			return;
		} 
		moveCriteriaTime = clock();
		temp = blockMoveSimulation(blockQueue, 1, 0);
		if(temp != 0)
		{
			reloadBlock();
		}
	}
	else if(GetAsyncKeyState(VK_DOWN))
	{
		if(nowTime - moveCriteriaTime < moveDelayTime)
		{
			return;
		} 
		moveCriteriaTime = clock();
		softDrop();
	}
	if(GetAsyncKeyState(keycode_z))
	{
		if(nowTime - rotCriteriaTime < rotDelayTime)
		{
			return;
		} 
		rotCriteriaTime = clock();
		temp = blockRotationSimulation(blockQueue, -1);
		if(temp != 0)
		{
			reloadBlock();
		}
	}
	if(GetAsyncKeyState(keycode_x))
	{
		if(nowTime - rotCriteriaTime < rotDelayTime)
		{
			return;
		} 
		rotCriteriaTime = clock();
		temp = blockRotationSimulation(blockQueue, 1);
		if(temp != 0)
		{
			reloadBlock();
		}
	}
	if(GetAsyncKeyState(VK_SPACE) & KEY_DOWN)
	{
		if(nowTime - moveCriteriaTime < moveDelayTime)
		{
			return;
		} 
		moveCriteriaTime = clock();
		hardDrop();
	}
	
	if(GetAsyncKeyState(keycode_c) & KEY_DOWN)
	{
		if(nowTime - moveCriteriaTime < moveDelayTime)
		{
			return;
		} 
		moveCriteriaTime = clock();
		hold();
	}
}

int blockRotationSimulation(block blockQueue[4], int rotDir)
{
	int X = 0;
	int Y = 0;
	int CODE = blockQueue[0].code;
	
	for(int i=0; i<=3; i++)
	{
		X = tetromino[CODE][(blockRot + 4 + rotDir) % 4][i].x - tetromino[CODE][blockRot][i].x;
		Y = tetromino[CODE][(blockRot + 4 + rotDir) % 4][i].y - tetromino[CODE][blockRot][i].y;
		
		if(board[blockQueue[i].y + Y][blockQueue[i].x + X] != 0 && board[blockQueue[i].y + Y][blockQueue[i].x + X] != CODE)
		{
			return 0;
		}
		inputPreloadBlockQueue(i, CODE, blockQueue[i].x + X, blockQueue[i].y + Y);
	}
	blockRot = (blockRot + 4 + rotDir) % 4;
	
	return 1;
} 

void landBlock(block blockQueue[4], int decreaseY)
{
	int X = 0;
	int Y = 0;
	int CODE = blockQueue[0].code;
	int line[24] = {0};
	for(int i=0; i<=3; i++)
	{
		X = blockQueue[i].x;
		Y = blockQueue[i].y;
		inputPreloadBlockQueue(i,CODE + 7, X, Y + decreaseY);
		line[Y + decreaseY] = 1;
	}
	reloadBlock();
	blockExistence = 0;
	for(int i=0; i<24; i++)
	{
		if(line[i] != 0)
		{
			checkLine(i);
		}
	}
	if(fallingDelayTime >= 50)
	{
		fallingDelayTime -= fallingDelayDecreaseTime;
	}
	
		
	return;
}

void checkLine(int line)
{
	if(line <=1)
	{
		playing = 0;
		return;
	}
	for(int x=1; x<=10; x++)
	{
		if(board[line][x] == 0)
		{
			return;
		}
	}
	for(int x=1; x<=10; x++)
	{
		board[line][x] = 0;
		printBoard(0, x + BOARD_POS_X, line);
	}
	for(int y = line - 1; y>=0; y--)
	{
		for(int x = 1; x<=10; x++)
		{
			board[y+1][x] = board[y][x];
			printBoard(board[y+1][x], x + BOARD_POS_X, y+1);
			board[y][x] = 0;
			printBoard(board[y][x], x + BOARD_POS_X, y);
		}
	}
	clearLine++; 
	
	return;
}

void hardDrop()
{
	int temp = 0;
	
	for(int i=1; i<=30; i++)
	{
		temp = blockMoveSimulation(blockQueue, 0, i);
		if(temp == 0)
		{
			landBlock(blockQueue, i-1);
			
			return;
		}
	}
	
	return;
}

void printUI()
{
	goto_xy(0, 28);
	printf("���� �ð� | %d:%d.%d         ", nowTime / 60000, (nowTime / 1000)%60, nowTime % 1000);
	goto_xy(0, 29);
	printf("line : %d / %d        ", clearLine, targetLine);
	goto_xy(0, 30);
	printf("blockCode : %d             ", blockQueue[0].code);
	if(clearLine >= targetLine)
	{
		goto_xy (0, 30);
		printf("clear!\n");
		playing = 0;
	}
	
	return;
}

void createBag()
{
	int randomValue = 0;
	int temp = 0;
	
	for(int i=0; i<7; i++)
	{
		bag7[i] = i+1;
	}
	for(int i=0; i<7; i++)
	{
		randomValue = rand() % 7;
		temp = bag7[i];
		bag7[i] = bag7[randomValue];
		bag7[randomValue] = temp;
	}
	
	return;
} 

void hold()
{
	int originValue = holdValue;
	int X = 0;
	int Y = 0;
	
	holdValue = blockQueue[0].code;
	for(int i=0; i<=3; i++)
	{
		printBoard(0, 1+i, 4);
		printBoard(0, 1+i, 5);
	}
	for(int i=0; i<=3; i++)
	{
		X = blockQueue[i].x;
		Y = blockQueue[i].y;
		
		inputPreloadBlockQueue(i, 0, X, Y);
		
		X = tetromino[holdValue][0][i].x;
		Y = tetromino[holdValue][0][i].y;
		if(holdValue == 3)
		{
			printBoard(holdValue, 2 + X, 5 + Y);
		}
		else if(holdValue == 7)
		{
			printBoard(holdValue, 2 + X, 5 + Y);
		}
		else
		{
			printBoard(holdValue, 2.5 + X, 5 + Y);
		}
		
		
		
	}
	reloadBlock();
	blockExistence = 0;
	createBlock(originValue);
	
	return;
}

int importNext()
{
	int nextBlock = next[(nextFrontIndex) % 5];
	int X = 0;
	int Y = 0;
	
	nextFrontIndex ++;
	nextRearIndex ++;
	next[(nextRearIndex)%5] = bag7[bagIndex];
	bagIndex++;
	if(bagIndex >= 7)
	{
		createBag();
		bagIndex = 0;
	}
	for(int y=4; y<=17; y++)
	{
		if((y-3) % 3 != 0)
		{
			printBoard(0, 17, y);
			printBoard(0, 18, y);
			printBoard(0, 19, y);
			printBoard(0, 20, y);
		}
	}
		for(int i=nextFrontIndex; i<=nextRearIndex ; i++)
		{
			for(int j=0; j<=3; j++)
			{
				X = tetromino[next[i%5]][0][j].x;
				Y = tetromino[next[i%5]][0][j].y;
				if(next[i%5] == 3)
				{
					printBoard(next[i%5], 18 + X, 5 + (3*(i-nextFrontIndex)) + Y);
				}
				else if(next[i%5] == 7)
				{
					printBoard(next[i%5], 18 + X, 5 + (3*(i-nextFrontIndex)) + Y);
				}
				else
				{
					printBoard(next[i%5], 18.5 + X, 5 + (3*(i-nextFrontIndex)) + Y);
				}
			}
		}
		
		return nextBlock;
} 

void settingTetromino()
{
	//Z�̳�
	tetromino[1][0][0].x = -1;
	tetromino[1][0][0].y = -1;
	tetromino[1][0][0].code = 1;
	tetromino[1][0][1].x = 0;
	tetromino[1][0][1].y = -1;
	tetromino[1][0][1].code = 1;
	tetromino[1][0][2].x = 0;
	tetromino[1][0][2].y = 0;
	tetromino[1][0][2].code = 1;
	tetromino[1][0][3].x = 1;
	tetromino[1][0][3].y = 0;
	tetromino[1][0][3].code = 1;
	
	tetromino[1][1][0].x = 1;
	tetromino[1][1][0].y = -1;
	tetromino[1][1][0].code = 1;
	tetromino[1][1][1].x = 1;
	tetromino[1][1][1].y = 0;
	tetromino[1][1][1].code = 1;
	tetromino[1][1][2].x = 0;
	tetromino[1][1][2].y = 0;
	tetromino[1][1][2].code = 1;
	tetromino[1][1][3].x = 0;
	tetromino[1][1][3].y = 1;
	tetromino[1][1][3].code = 1;
	
	tetromino[1][2][0].x = 1;
	tetromino[1][2][0].y = 1;
	tetromino[1][2][0].code = 1;
	tetromino[1][2][1].x = 0;
	tetromino[1][2][1].y = 1;
	tetromino[1][2][1].code = 1;
	tetromino[1][2][2].x = 0;
	tetromino[1][2][2].y = 0;
	tetromino[1][2][2].code = 1;
	tetromino[1][2][3].x = -1;
	tetromino[1][2][3].y = 0;
	tetromino[1][2][3].code = 1;
	
	tetromino[1][3][0].x = -1;
	tetromino[1][3][0].y = 1;
	tetromino[1][3][0].code = 1;
	tetromino[1][3][1].x = -1;
	tetromino[1][3][1].y = 0;
	tetromino[1][3][1].code = 1;
	tetromino[1][3][2].x = 0;
	tetromino[1][3][2].y = 0;
	tetromino[1][3][2].code = 1;
	tetromino[1][3][3].x = 0;
	tetromino[1][3][3].y = -1;
	tetromino[1][3][3].code = 1;
	
	//L�̳�
	
	tetromino[2][0][0].x = -1;
	tetromino[2][0][0].y = 0;
	tetromino[2][0][0].code = 2; 
	tetromino[2][0][1].x = 0;
	tetromino[2][0][1].y = 0;
	tetromino[2][0][1].code = 2; 
	tetromino[2][0][2].x = 1;
	tetromino[2][0][2].y = 0;
	tetromino[2][0][2].code = 2; 
	tetromino[2][0][3].x = 1;
	tetromino[2][0][3].y = -1;
	tetromino[2][0][3].code = 2; 
	
	tetromino[2][1][0].x = 0;
	tetromino[2][1][0].y = -1;
	tetromino[2][1][0].code = 2;
	tetromino[2][1][1].x = 0;
	tetromino[2][1][1].y = 0;
	tetromino[2][1][1].code = 2;
	tetromino[2][1][2].x = 0;
	tetromino[2][1][2].y = 1;
	tetromino[2][1][2].code = 2;
	tetromino[2][1][3].x = 1;
	tetromino[2][1][3].y = 1;
	tetromino[2][1][3].code = 2; 
	
	tetromino[2][2][0].x = 1;
	tetromino[2][2][0].y = 0;
	tetromino[2][2][0].code = 2;
	tetromino[2][2][1].x = 0;
	tetromino[2][2][1].y = 0;
	tetromino[2][2][1].code = 2;
	tetromino[2][2][2].x = -1;
	tetromino[2][2][2].y = 0;
	tetromino[2][2][2].code = 2;
	tetromino[2][2][3].x = -1;
	tetromino[2][2][3].y = 1;
	tetromino[2][2][3].code = 2;

	tetromino[2][3][0].x = 0;
	tetromino[2][3][0].y = 1;
	tetromino[2][3][0].code = 2;
	tetromino[2][3][1].x = 0;
	tetromino[2][3][1].y = 0;
	tetromino[2][3][1].code = 2;
	tetromino[2][3][2].x = 0;
	tetromino[2][3][2].y = -1;
	tetromino[2][3][2].code = 2;
	tetromino[2][3][3].x = -1;
	tetromino[2][3][3].y = -1;
	tetromino[2][3][3].code = 2;

	//O�̳�  
	
	tetromino[3][0][0].x = 0;
	tetromino[3][0][0].y = -1;
	tetromino[3][0][0].code = 3;
	tetromino[3][0][1].x = 0;
	tetromino[3][0][1].y = 0;
	tetromino[3][0][1].code = 3;
	tetromino[3][0][2].x = 1;
	tetromino[3][0][2].y = 0;
	tetromino[3][0][2].code = 3;
	tetromino[3][0][3].x = 1;
	tetromino[3][0][3].y = -1;
	tetromino[3][0][3].code = 3;
	
	tetromino[3][1][0].x = 0;
	tetromino[3][1][0].y = -1;
	tetromino[3][1][0].code = 3;
	tetromino[3][1][1].x = 0;
	tetromino[3][1][1].y = 0;
	tetromino[3][1][1].code = 3;
	tetromino[3][1][2].x = 1;
	tetromino[3][1][2].y = 0;
	tetromino[3][1][2].code = 3;
	tetromino[3][1][3].x = 1;
	tetromino[3][1][3].y = -1;
	tetromino[3][1][3].code = 3;
	
	tetromino[3][2][0].x = 0;
	tetromino[3][2][0].y = -1;
	tetromino[3][2][0].code = 3;
	tetromino[3][2][1].x = 0;
	tetromino[3][2][1].y = 0;
	tetromino[3][2][1].code = 3;
	tetromino[3][2][2].x = 1;
	tetromino[3][2][2].y = 0;
	tetromino[3][2][2].code = 3;
	tetromino[3][2][3].x = 1;
	tetromino[3][2][3].y = -1;
	tetromino[3][2][3].code = 3;
	
	tetromino[3][3][0].x = 0;
	tetromino[3][3][0].y = -1;
	tetromino[3][3][0].code = 3;
	tetromino[3][3][1].x = 0;
	tetromino[3][3][1].y = 0;
	tetromino[3][3][1].code = 3;
	tetromino[3][3][2].x = 1;
	tetromino[3][3][2].y = 0;
	tetromino[3][3][2].code = 3;
	tetromino[3][3][3].x = 1;
	tetromino[3][3][3].y = -1;
	tetromino[3][3][3].code = 3;

	//S�̳�
	
	tetromino[4][0][0].x = 1;
	tetromino[4][0][0].y = -1;
	tetromino[4][0][0].code = 4;
	tetromino[4][0][1].x = 0;
	tetromino[4][0][1].y = -1;
	tetromino[4][0][1].code = 4;
	tetromino[4][0][2].x = 0;
	tetromino[4][0][2].y = 0;
	tetromino[4][0][2].code = 4;
	tetromino[4][0][3].x = -1;
	tetromino[4][0][3].y = 0;
	tetromino[4][0][3].code = 4;
	
	tetromino[4][1][0].x = 1;
	tetromino[4][1][0].y = 1;
	tetromino[4][1][0].code = 4;
	tetromino[4][1][1].x = 1;
	tetromino[4][1][1].y = 0;
	tetromino[4][1][1].code = 4;
	tetromino[4][1][2].x = 0;
	tetromino[4][1][2].y = 0;
	tetromino[4][1][2].code = 4;
	tetromino[4][1][3].x = 0;
	tetromino[4][1][3].y = -1;
	tetromino[4][1][3].code = 4;
	
	tetromino[4][2][0].x = -1;
	tetromino[4][2][0].y = 1;
	tetromino[4][2][0].code = 4;
	tetromino[4][2][1].x = 0;
	tetromino[4][2][1].y = 1;
	tetromino[4][2][1].code = 4;
	tetromino[4][2][2].x = 0;
	tetromino[4][2][2].y = 0;
	tetromino[4][2][2].code = 4;
	tetromino[4][2][3].x = 1;
	tetromino[4][2][3].y = 0;
	tetromino[4][2][3].code = 4;
	
	tetromino[4][3][0].x = -1;
	tetromino[4][3][0].y = -1;
	tetromino[4][3][0].code = 4;
	tetromino[4][3][1].x = -1;
	tetromino[4][3][1].y = 0;
	tetromino[4][3][1].code = 4;
	tetromino[4][3][2].x = 0;
	tetromino[4][3][2].y = 0;
	tetromino[4][3][2].code = 4;
	tetromino[4][3][3].x = 0;
	tetromino[4][3][3].y = 1;
	tetromino[4][3][3].code = 4;

	//J�̳�
	
	tetromino[5][0][0].x = 1;
	tetromino[5][0][0].y = 0;
	tetromino[5][0][0].code = 5;
	tetromino[5][0][1].x = 0;
	tetromino[5][0][1].y = 0;
	tetromino[5][0][1].code = 5;
	tetromino[5][0][2].x = -1;
	tetromino[5][0][2].y = 0;
	tetromino[5][0][2].code = 5;
	tetromino[5][0][3].x = -1;
	tetromino[5][0][3].y = -1;
	tetromino[5][0][3].code = 5; 

	tetromino[5][1][0].x = 0;
	tetromino[5][1][0].y = 1;
	tetromino[5][1][0].code = 5;
	tetromino[5][1][1].x = 0;
	tetromino[5][1][1].y = 0;
	tetromino[5][1][1].code = 5;
	tetromino[5][1][2].x = 0;
	tetromino[5][1][2].y = -1;
	tetromino[5][1][2].code = 5;
	tetromino[5][1][3].x = 1;
	tetromino[5][1][3].y = -1;
	tetromino[5][1][3].code = 5;

	tetromino[5][2][0].x = -1;
	tetromino[5][2][0].y = 0;
	tetromino[5][2][0].code = 5;
	tetromino[5][2][1].x = 0;
	tetromino[5][2][1].y = 0;
	tetromino[5][2][1].code = 5;
	tetromino[5][2][2].x = 1;
	tetromino[5][2][2].y = 0;
	tetromino[5][2][2].code = 5;
	tetromino[5][2][3].x = 1;
	tetromino[5][2][3].y = 1;
	tetromino[5][2][3].code = 5;
	
	tetromino[5][3][0].x = 0;
	tetromino[5][3][0].y = -1;
	tetromino[5][3][0].code = 5;
	tetromino[5][3][1].x = 0;
	tetromino[5][3][1].y = 0;
	tetromino[5][3][1].code = 5;
	tetromino[5][3][2].x = 0;
	tetromino[5][3][2].y = 1;
	tetromino[5][3][2].code = 5;
	tetromino[5][3][3].x = -1;
	tetromino[5][3][3].y = 1;
	tetromino[5][3][3].code = 5;
	
	//T�̳� 
	
	tetromino[6][0][0].x = 1;
	tetromino[6][0][0].y = 0;
	tetromino[6][0][0].code = 6;
	tetromino[6][0][1].x = 0;
	tetromino[6][0][1].y = 0;
	tetromino[6][0][1].code = 6;
	tetromino[6][0][2].x = -1;
	tetromino[6][0][2].y = 0;
	tetromino[6][0][2].code = 6;
	tetromino[6][0][3].x = 0;
	tetromino[6][0][3].y = -1;
	tetromino[6][0][3].code = 6;
	
	tetromino[6][1][0].x = 0;
	tetromino[6][1][0].y = 1;
	tetromino[6][1][0].code = 6;
	tetromino[6][1][1].x = 0;
	tetromino[6][1][1].y = 0;
	tetromino[6][1][1].code = 6;
	tetromino[6][1][2].x = 0;
	tetromino[6][1][2].y = -1;
	tetromino[6][1][2].code = 6;
	tetromino[6][1][3].x = 1;
	tetromino[6][1][3].y = 0;
	tetromino[6][1][3].code = 6;
	
	tetromino[6][2][0].x = 1;
	tetromino[6][2][0].y = 0;
	tetromino[6][2][0].code = 6;
	tetromino[6][2][1].x = 0;
	tetromino[6][2][1].y = 0;
	tetromino[6][2][1].code = 6;
	tetromino[6][2][2].x = -1;
	tetromino[6][2][2].y = 0;
	tetromino[6][2][2].code = 6;
	tetromino[6][2][3].x = 0;
	tetromino[6][2][3].y = 1;
	tetromino[6][2][3].code = 6;
	
	tetromino[6][3][0].x = 0;
	tetromino[6][3][0].y = 1;
	tetromino[6][3][0].code = 6;
	tetromino[6][3][1].x = 0;
	tetromino[6][3][1].y = 0;
	tetromino[6][3][1].code = 6;
	tetromino[6][3][2].x = 0;
	tetromino[6][3][2].y = -1;
	tetromino[6][3][2].code = 6;
	tetromino[6][3][3].x = -1;
	tetromino[6][3][3].y = 0;
	tetromino[6][3][3].code = 6;
	
	//I�̳�
	
	tetromino[7][0][0].x = -1;
	tetromino[7][0][0].y = 0;
	tetromino[7][0][0].code = 7;
	tetromino[7][0][1].x = 0;
	tetromino[7][0][1].y = 0;
	tetromino[7][0][1].code = 7;
	tetromino[7][0][2].x = 1;
	tetromino[7][0][2].y = 0;
	tetromino[7][0][2].code = 7;
	tetromino[7][0][3].x = 2;
	tetromino[7][0][3].y = 0;
	tetromino[7][0][3].code = 7; 
	
	tetromino[7][1][0].x = 1;
	tetromino[7][1][0].y = -1;
	tetromino[7][1][0].code = 7;
	tetromino[7][1][1].x = 1;
	tetromino[7][1][1].y = 0;
	tetromino[7][1][1].code = 7;
	tetromino[7][1][2].x = 1;
	tetromino[7][1][2].y = 1;
	tetromino[7][1][2].code = 7;
	tetromino[7][1][3].x = 1;
	tetromino[7][1][3].y = 2;
	tetromino[7][1][3].code = 7;
	
	tetromino[7][2][0].x = -1;
	tetromino[7][2][0].y = 1;
	tetromino[7][2][0].code = 7;
	tetromino[7][2][1].x = 0;
	tetromino[7][2][1].y = 1;
	tetromino[7][2][1].code = 7;
	tetromino[7][2][2].x = 1;
	tetromino[7][2][2].y = 1;
	tetromino[7][2][2].code = 7;
	tetromino[7][2][3].x = 2;
	tetromino[7][2][3].y = 1;
	tetromino[7][2][3].code = 7;
	
	tetromino[7][3][0].x = 0;
	tetromino[7][3][0].y = -1;
	tetromino[7][3][0].code = 7;
	tetromino[7][3][1].x = 0;
	tetromino[7][3][1].y = 0;
	tetromino[7][3][1].code = 7;
	tetromino[7][3][2].x = 0;
	tetromino[7][3][2].y = 1;
	tetromino[7][3][2].code = 7;
	tetromino[7][3][3].x = 0;
	tetromino[7][3][3].y = 2;
	tetromino[7][3][3].code = 7;
}

