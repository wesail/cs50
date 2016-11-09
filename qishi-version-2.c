#include <stdio.h>
#include <stdlib.h>
#define SIZE 8

/**
 * 骑士游历第二版
 * 计算每个格子的可达度，可达度是指在这个格子可以到达的格子数目，最小是
 * 最大是8.每步都寻找最小可达度的格子然后移动
 * 通过改变初始位置，发现都可以实现遍历
 * 
 */

int game(int CurrentRow, int CurrentColumn);

int board[SIZE][SIZE];
int accessBoard[SIZE][SIZE];

int main(void)
{
    int step[SIZE][SIZE] = {{0}};
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            step[i][j] = game(i, j);
        }
    }
    
    printf("初始位置与步数的对应表为：\n");
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            printf("%2i ", step[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    
    return 0;
	
}


/**
 * 移动前测试是否移动方案是否可行
 * 参数：
 * row、column：当前行列坐标；n是方案号
 * 
 * 如果方案可行，返回0，否则返回-1；
 * 这个函数是最初版修改后的，之所以返回-1，
 * 是因为之前版本返回的是方案号码（0~7），-1代表不可能
 */
int MoveTest(int row, int column, int n, int horizontal[], int vertical[])
{
	int limit1 = ((row + horizontal[n]) > (SIZE-1)) || ((row + horizontal[n]) < 0)? 0:1;
	int limit2 = ((column + vertical[n]) > (SIZE-1)) || ((column + vertical[n]) < 0)? 0:1;
	if (limit1 && limit2)
	{
		int NewRow =  row + horizontal[n];
		int NewColumn = column + vertical[n];
		
		if (!board[NewRow][NewColumn])
			return 0;
	}
	
	return -1;
}


/**
 * 移动操作执行
 * 参数：
 * *row、*column：代表当前坐标的变量地址
 * MoveNumber：移动方案
 * 
 * 
 */
void Move(int *row, int *column, int MoveNumber, int horizontal[], int vertical[])
{
	if (MoveNumber != -1)
	{
	    // 移动后将格子的值设为1
		*row += horizontal[MoveNumber];
		*column += vertical[MoveNumber];
		board[*row][*column] = 1;
	}
	
	return;
}


/**
 * 执行游戏
 * init：初始化棋盘格子；
 * MoveTest：测试移动方案是否可行，返回0或-1
 * Move：接受方案值，执行移动操作
 * success：测试是否遍历棋盘，返回0或1；
 * show：显示当前棋盘状态和可达度表
 * AccessBility：计算全部格子可达度
 * acsFind：找到下一步最小可达度的格子，返回方案的值
 */
int game(CurrentRow, CurrentColumn)
{
	void init(int row, int column);
	int MoveTest(int row, int column, int n, int horizontal[], int vertical[]);
	void Move(int *row, int *column, int MoveNumber, int horizontal[], int vertical[]);
	int success();
	void show(void);
	void AccessBility(int horizontal[], int vertical[]);
	int acsFind(int row, int column, int horizontal[], int vertical[]);
	
    // 	计算游戏步数
	int counter = 0;
	
    // 	存放8中方案，horizontal代表横坐标变化，vertical代表纵坐标变化
    //  数值上，正数代表增大，负数代表减小，所以0号方案就等于(x, y)+ (2, -1)，(x, y)为当前坐标
	int horizontal[SIZE] = {2, 1, -1, -2, -2, -1, 1, 2};
	int vertical[SIZE] = {-1, -2, -2, -1, 1, 2, 2, 1};
	
// 	初始化棋盘和可达度表
	init(CurrentRow, CurrentColumn);
	AccessBility(horizontal, vertical);
	
	while (success())
	{
	    // 每移动一次，显示状态
		show();
		
        // 获得移动方案
		int MoveNumber = acsFind(CurrentRow, CurrentColumn, horizontal, vertical);
		
        // 方案为-1代表不能继续移动
		if (MoveNumber == -1)
		{
// 			printf("无法继续！\n");
			break;
		}
		
        // 按照方案号进行移动，然后重新计算可达度表，并将步数加1
		Move(&CurrentRow, &CurrentColumn, MoveNumber, horizontal, vertical);
		AccessBility(horizontal, vertical);
		counter++;
		
// 		
		printf("第%i步\n", counter);
		
	}
	
	printf("游戏进行了%i步\n", counter);
	printf("最终状态为：\n");
	show();
	return counter;
}

// 显示棋盘状态和可达度表
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
	
	printf("\n");
	
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			printf("%i ", accessBoard[i][j]);
		}
		
		printf("\n");
	}
	printf("\n");
}

// 初始化棋盘
void init(int row, int column)
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			board[i][j] = 0;
			accessBoard[i][j] = 0;
		}
	}
	
    // 根据开始位置，将该位置的值置为1
	board[row][column] = 1;
}

// 计算可达度
void AccessBility(int horizontal[], int vertical[])
{
    // 外面两层遍历整个棋盘
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
		    
		    // 对每个格子而言，测试8种方案中的有效方案，得到有效方案数目
		    // 有效方案数目记为可达度，填入对应位置的可达度表
			int acsNum = 0;
			for (int k = 0; k < SIZE; k++)
			{
			    // 这里有个疑问是，为什么函数原型定义在game中，但在这个函数里仍能访问MoveTest
				if (!MoveTest(i, j, k, horizontal, vertical))
					acsNum++;
			}
			
            /**
             * 即使可达度为0也是可以接受的，
             * 可达度为0只有一种情况，周围走法已经全部不能走，
             * 只会出现在最后一步
             */
			accessBoard[i][j] = acsNum;
		}
	}
	
}

// 找到最小可达度的走法
int acsFind(int row, int column, int horizontal[], int vertical[])
{
    // 建立一个数组，存放8个方案的可达度值
	int acsSorted[SIZE];
	for (int i = 0; i < SIZE; i++)
	{
	   // 如果方案有效，将方案中下一步位置的可达度存入acsSorted，否则将对应方案的可达度设为-1
		if (!MoveTest(row, column, i, horizontal, vertical))
			acsSorted[i] = accessBoard[row + horizontal[i]][column + vertical[i]];
		else
			acsSorted[i] = -1;
	}
	
    // 存放最小可达度值
	int smallestAcs = SIZE;
	
    // smallestIndex存放最小可达度的方案
	int smallestIndex = -1;
	
    // 遍历acsSorted，找到最小可达度，返回对应的方案号码
	for (int i = 0; i < SIZE; i++)
	{
	    // 如果值为-1，代表对应方案不可行
		if ((acsSorted[i] != -1) && (acsSorted[i] < smallestAcs))
		{
			smallestAcs = acsSorted[i];
			smallestIndex = i;
		}
	}
	
    // 如果所有方案都不可行，smallestIndex值仍为-1
	return smallestIndex;
}


// 判断是否遍历完成，如果全部值都是1，代表遍历完，返回0，否则返回1
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