#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

typedef struct Block{
	int x;
	int y;
	int code;
}block;

void settingWallkickData();												//SRS정보를 담는 데이터를 저장  
void settingTetromino();												//미노 모양을 설정 

block wallkickData_normal[4][5] = {0};
block wallkickData_I[8][5] = {0};
block tetromino[8][4][4] = {0};											//테트리스의 미노 모양을 저장하는 변수 [블록코드][회전][블록] 

void settingWallkickData()
{

	wallkickData_normal[0][0].x = 0;
	wallkickData_normal[0][0].y = 0;
	wallkickData_normal[0][1].x = 0;
	wallkickData_normal[0][1].y = 0;
	wallkickData_normal[0][2].x = 0;
	wallkickData_normal[0][2].y = 0;
	wallkickData_normal[0][3].x = 0;
	wallkickData_normal[0][3].y = 0;
	wallkickData_normal[0][4].x = 0;
	wallkickData_normal[0][4].y = 0;
	
	wallkickData_normal[1][0].x = 0;
	wallkickData_normal[1][0].y = 0;
	wallkickData_normal[1][1].x = 1;
	wallkickData_normal[1][1].y = 0;
	wallkickData_normal[1][2].x = 1;
	wallkickData_normal[1][2].y = -1;
	wallkickData_normal[1][3].x = 0;
	wallkickData_normal[1][3].y = 2;
	wallkickData_normal[1][4].x = 1;
	wallkickData_normal[1][4].y = 2;
	
	wallkickData_normal[2][0].x = 0;
	wallkickData_normal[2][0].y = 0;
	wallkickData_normal[2][1].x = 0;
	wallkickData_normal[2][1].y = 0;
	wallkickData_normal[2][2].x = 0;
	wallkickData_normal[2][2].y = 0;
	wallkickData_normal[2][3].x = 0;
	wallkickData_normal[2][3].y = 0;
	wallkickData_normal[2][4].x = 0;
	wallkickData_normal[2][4].y = 0;
	
	wallkickData_normal[3][0].x = 0;
	wallkickData_normal[3][0].y = 0;
	wallkickData_normal[3][1].x = -1;
	wallkickData_normal[3][1].y = 0;
	wallkickData_normal[3][2].x = -1;
	wallkickData_normal[3][2].y = -1;
	wallkickData_normal[3][3].x = 0;
	wallkickData_normal[3][3].y = 2;
	wallkickData_normal[3][4].x = -1;
	wallkickData_normal[3][4].y = 2;
	
	wallkickData_I[0][0].x = 0;
	wallkickData_I[0][0].y = 0;
	wallkickData_I[0][1].x = -2;
	wallkickData_I[0][1].y = 0;
	wallkickData_I[0][2].x = 1;
	wallkickData_I[0][2].y = 1;
	wallkickData_I[0][3].x = 1;
	wallkickData_I[0][3].y = 2;
	wallkickData_I[0][4].x = -2;
	wallkickData_I[0][4].y = -1;
	
	wallkickData_I[1][0].x = 0;
	wallkickData_I[1][0].y = 0;
	wallkickData_I[1][1].x = -1;
	wallkickData_I[1][1].y = 0;
	wallkickData_I[1][2].x = 2;
	wallkickData_I[1][2].y = 0;
	wallkickData_I[1][3].x = -1;
	wallkickData_I[1][3].y = 2;
	wallkickData_I[1][4].x = 2;
	wallkickData_I[1][4].y = -1;
	
	wallkickData_I[2][0].x = 0;
	wallkickData_I[2][0].y = 0;
	wallkickData_I[2][1].x = 2;
	wallkickData_I[2][1].y = 0;
	wallkickData_I[2][2].x = -1;
	wallkickData_I[2][2].y = 0;
	wallkickData_I[2][3].x = 2;
	wallkickData_I[2][3].y = 1;
	wallkickData_I[2][4].x = -1;
	wallkickData_I[2][4].y = -1;

	wallkickData_I[3][0].x = 0;
	wallkickData_I[3][0].y = 0;
	wallkickData_I[3][1].x = -2;
	wallkickData_I[3][1].y = 0;
	wallkickData_I[3][2].x = 1;
	wallkickData_I[3][2].y = 0;
	wallkickData_I[3][3].x = -2;
	wallkickData_I[3][3].y = -1;
	wallkickData_I[3][4].x = 1;
	wallkickData_I[3][4].y = -2;
	
	wallkickData_I[4][0].x = 0;
	wallkickData_I[4][0].y = 0;
	wallkickData_I[4][1].x = 2;
	wallkickData_I[4][1].y = 0;
	wallkickData_I[4][2].x = -1;
	wallkickData_I[4][2].y = 0;
	wallkickData_I[4][3].x = -1;
	wallkickData_I[4][3].y = 2;
	wallkickData_I[4][4].x = 2;
	wallkickData_I[4][4].y = -1;
	
	wallkickData_I[5][0].x = 0;
	wallkickData_I[5][0].y = 0;
	wallkickData_I[5][1].x = 1;
	wallkickData_I[5][1].y = 0;
	wallkickData_I[5][2].x = -2;
	wallkickData_I[5][2].y = 0;
	wallkickData_I[5][3].x = 1;
	wallkickData_I[5][3].y = 2;
	wallkickData_I[5][4].x = -2;
	wallkickData_I[5][4].y = -1;
	
	wallkickData_I[6][0].x = 0;
	wallkickData_I[6][0].y = 0;
	wallkickData_I[6][1].x = -2;
	wallkickData_I[6][1].y = 0;
	wallkickData_I[6][2].x = 1;
	wallkickData_I[6][2].y = 0;
	wallkickData_I[6][3].x = -2;
	wallkickData_I[6][3].y = 1;
	wallkickData_I[6][4].x = 1;
	wallkickData_I[6][4].y = -1;

	wallkickData_I[7][0].x = 0;
	wallkickData_I[7][0].y = 0;
	wallkickData_I[7][1].x = 2;
	wallkickData_I[7][1].y = 0;
	wallkickData_I[7][2].x = -1;
	wallkickData_I[7][2].y = 0;
	wallkickData_I[7][3].x = 2;
	wallkickData_I[7][3].y = 1;
	wallkickData_I[7][4].x = -1;
	wallkickData_I[7][4].y = -2;
}

void settingTetromino()
{
	//Z미노
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
	
	//L미노
	
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

	//O미노  
	
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

	//S미노
	
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

	//J미노
	
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
	
	//T미노 
	
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
	
	//I미노
	
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
