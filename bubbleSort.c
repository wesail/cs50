#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define SIZE 10
/*
    冒泡排序学习。通过rand()函数随机产生200以内的数，
    作为10个元素数组的值。再用冒泡排序进行排序。
*/

// 声明viewArray函数，用来直观显示数组排序过程
void viewArray(const int a[], int size);

int main(void)
{
    // 	产生随机种子
	srand(time(NULL));
	
    // 初始化数组	
	int array[SIZE] = {0};
	
    // 填充数组
	for (int i = 0; i < SIZE; i++)
	{
		array[i] = 1 + rand() % 200;
	}
	
	viewArray(array, SIZE);
	printf("目前未排序！\n\n");
	
	// flag用来确认是否完成了排序
	int flag = 1; 

    /* 
        外层循环用来控制排序次数，内层循环进行两两交换
        一开始没有想到将flag放进跳出条件中，只想到了continue
        发现无论放何处都不能有效控制循环次数
    */
	for (int count = 0, hold; flag && count < SIZE; count++)
	{
	    // 每次开始都将flag置为0，用来判断是否有交换
	    flag = 0;
	    
	    for (int i = 0; i < SIZE - 1; i++)
		{
			if (array[i] > array[i+1])
			{
				hold = array[i+1];
				array[i+1] = array[i];
				array[i] = hold;
				
				flag = 1;
			}
		}
        
        if (flag)
        {
		    viewArray(array, SIZE);
		    printf("已经完成第%d次排序\n\n", count + 1);
        }
	}
	
	printf("排序完成！\n");
	viewArray(array, SIZE);
	
	return 0;
	
	
}

void viewArray(const int a[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (!i)
			printf("Array数组为：");
		printf("%d ", a[i]);
	}
	printf("\n");
}