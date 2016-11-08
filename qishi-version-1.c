#include <stdio.h>
#include <stdlib.h>
#define SIZE 8

int game(int CurrentRow, int CurrentColumn);

int board[SIZE][SIZE];

int main(void)
{
	int CurrentRow = 7;
	int CurrentColumn = 7;
	
	game(CurrentRow, CurrentColumn);
	
}

int MoveTest(int row, int column, int horizontal[], int vertical[])
{
	int limit1 = 0, limit2 = 0;
	for (int i = 0; i < SIZE; i++)
	{
		limit1 = ((row + horizontal[i]) > (SIZE-1)) || ((row + horizontal[i]) < 0)? 0:1;
		limit2 = ((column + vertical[i]) > (SIZE-1)) || ((column + vertical[i]) < 0)? 0:1;
		if (limit1 && limit2)
		{
			int NewRow =  row + horizontal[i];
			int NewColumn = column + vertical[i];
			
			if (!board[NewRow][NewColumn])
				return i;
		}
	}
	
	return -1;
}

void Move(int *row, int *column, int MoveNumber, int horizontal[], int vertical[])
{
	if (MoveNumber != -1)
	{
		*row += horizontal[MoveNumber];
		*column += vertical[MoveNumber];
		board[*row][*column] = 1;
	}
	
	return;
}

int success(void)
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (!board[i][j])
				return 1;
		}
	}
	
	return 0;
}

int game(CurrentRow, CurrentColumn)
{
	void init(int row, int column);
	int MoveTest(int row, int column, int horizontal[], int vertical[]);
	void Move(int *row, int *column, int MoveNumber, int horizontal[], int vertical[]);
	int success(void);
	void show(void);
	
	
	int counter = 0;
	int MoveNumber = 0;
	
	int horizontal[SIZE] = {2, 1, -1, -2, -2, -1, 1, 2};
	int vertical[SIZE] = {-1, -2, -2, -1, 1, 2, 2, 1};
	
	init(CurrentRow, CurrentColumn);
	
	while (success())
	{
		show();
		MoveNumber = MoveTest(CurrentRow, CurrentColumn, horizontal, vertical);
		
		if (MoveNumber == -1)
		{
			printf("无法继续！\n");
			break;
		}
		
		Move(&CurrentRow, &CurrentColumn, MoveNumber, horizontal, vertical);
		counter++;
		printf("第%i步\n", counter);
		
	}
	
	printf("游戏进行了%i步\n", counter);
	printf("最终状态为：\n");
	show();
	
	return 0;
}

void show(void)
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (!j)
				printf("|");
			
			if (!board[i][j])
				printf("__|");
			else
				printf("**|");
		}
		
		printf("\n");
	}
}

void init(int row, int column)
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			board[i][j] = 0;
		}
	}
	
	board[row][column] = 1;
}
