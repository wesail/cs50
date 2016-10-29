#include <stdio.h>

// 声明move函数，执行移动盘子的操作
int move(int plates, char start, char goal, char temp);

int main(void)
{
	// 定义盘子数目
	int plates;
	printf("请输入盘子数目：");
	scanf("%d", &plates);
	
	// 定义三根柱子，从A移动到B
	char start = 'A'; 
	char goal  = 'B';
	char temp  = 'C';
	
	// 调用move，执行移动操作
	move(plates, start, goal, temp);
	
	return 0;
}

int move(int plates, char start, char goal, char temp)
{
	// 如果只有一个盘子，直接移动到目标即可
	if (plates == 1)
	{
		printf("%c --> %c\n", start, goal);
		return 0;
	}
	else
	{
		// 在有多个盘子的情况下，分三步
		// 第一步，将n-1个盘子移动到临时柱子上，
		// 即 A --> C，而B作为临时柱子
		move(plates - 1, start, temp, goal);
		
		// 第二步，将第一步剩下的一个底部盘子移动到目标柱子
		// 即 A --> B
		move(1, start, goal, temp);
		
		// 第三步，从临时柱子上将n-1个盘子移动到目标柱子上。完成。
		// 即 C --> B，而A作为临时柱子
		move(plates - 1, temp, goal, start);
		
		return 0;
	}
}