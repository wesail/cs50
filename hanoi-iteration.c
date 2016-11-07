#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/******************************************************************
 *学完了数组和指针，尝试用循环的方法解决汉诺塔问题，想了很久，只总结了一点移动的
 *规律。对我来说， 这个问题验证了一点：在编程中，代码实现只占了很小一部分，更重要
 *的是逻辑上理清楚。
 *
 *2016/11/7
 *
 *循环解决汉诺塔问题                                             
 * 对于汉诺塔问题：                                              
 *    #                                                           
 *   ##                                                           
 *  ###                                                          
 * ####                                                           
 *   A     B    C
 * 
 * A作为起始柱子， B作为目标柱子（也可以是C，不影响问题）
 * 
 * 使用递归是简单而方便的，但循环就非常繁琐。
 * 
 * 用循环实现有以下的问题：
 * 1、循环次数最大为 2^n - 1， N为盘子数目
 * 2、每次移动需要判别移动哪个，向哪移动，
 * 即需要移动规则，根据规则每次判定如何移动
 * 
 * ===========================================
 * 以下是总结的移动规则，从上到下优先级依次降低
 * （用数字代表盘子和其大小）
 * ===========================================
 * 首先明确，每次在上面的三个数，必定有1
 * 1的移动是最重要的
 * 
 * 一、一个数不可连续移动两次 
 *      --->如果能连续移动两次，由于单步移动是可逆的，
 *      --->将导致无限循环
 * 
 * 二、1的移动优先级最高，在满足规则一的情况下，优先移动
 * 并且，将1向与其差为奇数的数所在柱子移动
 *      --->举例来说，有三个盘子在最上头，一个是1，另外两个盘子,
 *      --->假如一个是5（5个盘子情况下的最大），另一个是4，
 *      --->则1必须向5所在的柱子移动
 * 
 * 三、如果1不能移动），则判断是否有空柱子（用0代表）
 * 有空柱子的情况下，将三个数中最大的数向空柱子（0）移动
 * 
 * 四、既不能移动1， 也没有空柱子，就将除1以外的两个数中的小数
 * 向大数的柱子移动
 * 
 * 五、游戏开始时，如果最大数为奇数，则将1移动到目标柱，
 * 否则移动到辅助柱
 *      --->前四条已经可以保证将A移动到B或C
 *      --->加上这一条，可以保证移动到指定柱，实际上没有这一条的话
 *      --->程序也能运行，对应函数firstStep
 * 
 * 根据以上规则，能在2^n - 1步数内完成移动
 * ===============================================================
 * 
 * 
 *****************************************************************/


// 函数原型
void init(int *A, int * B, int *C);
void firstStep(int *A, int * B, int *C);
void move(int *A, int * B, int *C, int *moveN);
void compare(int *A, int * B, int *C, int *moveN);
//int win(int *A, int * B, int *C);
void show();


// 存放3个数组末位数字
int lastN[3] = {0, 0, 0};

/* 值为0代表1可移动，为1代表1不可移动
 * 根据规则一，不可连续移动一个数
 * 所以，每移动一次,无论是不是移动1,都要修改该值
 */
int count_one = 0;

// 代表盘子数目
int size;
// 用数组代表柱子

int main(void)
{
    printf("请输入盘子数目：\n");
    scanf("%d", &size);
    
    int A[size];
    int B[size];
    int C[size];
    
    // 初始化三个数组
    init(A, B, C);
    show(A, B, C); 
    
    // 存放两个数，分别是要移动的值和目标位置
    int moveN[] = {0, 0};
    
    // 控制循环次数
    unsigned long long range= pow(2, size) - 1;
    for (int i = 0; i < range; i++)
    {
        // 找出要移动的数及移动目标
        compare(A, B, C, moveN);
        
        // 执行移动操作
        move(A, B, C, moveN);
    }
    
    return 0;
}


/**
 * 
 * A数组为降序排列的自然数，最小值为1， 最大值为N
 * B、C均初始化为0
 * 
 **/
void init(int *A, int * B, int *C)
{
    for (int i = 0, num = size; i < size; i++)
        A[i] = num--;
    
    for (int i = 0; i < size; i++)
        B[i] = 0;
        
    for (int i = 0; i < size; i++)
        C[i] = 0;
    
    return;
}


// 可有可无
void firstStep(int *A, int * B, int *C)
{
    if (size % 2)
    {
        B[0] = 1;
        C[0] = 2;
        printf("A --> B\n");
        printf("A --> C\n");
    }
    else
    {
        C[0] = 1;
        B[0] = 2;
        printf("A --> C\n");
        printf("A --> B\n");
    }
    
    A[size-1] = 0;
    A[size-2] = 0;
    return;
}

/**
 * 比较3个末位数字，根据上述四条规则判定移动哪个数
 * 和移动的目标位置，存入moveN列表
 * 
 */ 
void compare(int *A, int * B, int *C, int *moveN)
{
    // 调用函数得到末位数字
    void lastNum(int *A, int * B, int *C);
    lastNum(A, B, C);
    
    // 判断是否存在0（空柱子）
    int zero = 0;
    for (int i = 0; i < 3; i++)
    {
        if (lastN[i] == 0)
            zero = 1;
    }
    
    // 3个末位数中总有1
    int one = 1;
    
    // 找到3个末位数中最大的数big
    // small是除了1和big之外的另一个数
    // sum用来求small
    int big = lastN[0], small;
    int sum = 0;
    for (int i = 0; i < 3; i++)
    {
        if (lastN[i] > big)
            big = lastN[i];
        sum += lastN[i];
    }
    small = sum - one - big;
    
    
    /* 
     * 根据四条规则，逐步判定移动哪个数，目标数是什么
     */
     
    // 如果1可移动
    if (count_one == 0)
    {
        // 将1设为起始值
        moveN[0] = 1;
        
        // 判断1与哪个数的差为奇数，
        // 哪个差为奇数就向哪个数移动
        if (abs(one - big) % 2)
            moveN[1] = big;
        else if (abs(one - small) % 2)
            moveN[1] = small;
    }
    
    // 如果1不能移动，就判断是否有空柱子
    else if (zero)
    {
        // 有空柱子，就将剩下两个数中大数移动到空柱子
        moveN[0] = big;
        moveN[1] = 0;
    }
    
    // 如果空柱子也没有，就将剩下两个数中小数移动到大数（之后）
    else
    {
        moveN[0] = small;
        moveN[1] = big;
    }
    
    return;
}

/***********************
 *该函数用来寻找每次处于最上面的三个数，用数组来表示的话，
 * 就是末位不为0的数，如果某个数组全部为0，则代表其为空
 * 
 **/
void lastNum(int *A, int * B, int *C)
{
    
    // 用来确认3个数组中第一个不为0的数，分别对应ABC
    // 第一次找到不为零的数会将对应位置的元素增加1
    // 如果一直为0，说明数组元素都是0，则index对应元素置为0
    int count[3] = {0, 0, 0};
    
    // 从末位开始寻找
    for (int i = size - 1; i >= 0; i--)
    {
        if ((A[i] != 0) && (count[0] == 0))
        {
            lastN[0] = A[i];
            count[0]++;
        }
        
        if ((B[i] != 0) && (count[1] == 0))
        {    
            lastN[1] = B[i];
            count[1]++;
        }
        
        if ((C[i] != 0) && (count[2] == 0))
        {    
            lastN[2] = C[i];
            count[2]++;
        }
    }
    
    // 如果count里面的数一直为0，说明对应数组元素都是0
    // 那么就代表有空柱子，直接将对应的末位数字置为0
    for (int i = 0; i < 3; i++)
    {
        if (count[i] == 0)
            lastN[i] = 0;
    }
    
    return;
}


/**
 * 根据末位数字数组里面的值，搜索其地址，供移动操作使用
 * 之所以可以这样做，是因为这个问题里，每个数唯一，没有重复值
 * n作为需要搜索的值，逐个数组比对，直到找到为止。
 */
int * getaddr(int *A, int * B, int *C, int n)
{
    int * addr;
    
    if (n != 0)
    {
        for (int i = 0; i < size; i++)
        {
        if (A[i] == n)
            addr = &A[i];
        if (B[i] == n)
            addr = &B[i];
        if (C[i] == n)
            addr = &C[i];
        }
    }
    else
    {
        if (A[0] == 0)
            addr = &A[0];
        if (B[0] == 0)
            addr = &B[0];
        if (C[0] == 0)
            addr = &C[0];
    }
    
    return addr;
}


/**
 * 读取名moveN里面的两个数，作为要移动的数，和目标数
 * 移动操作是
 * 如果目标数不为0，则将要移动的数移动到目标数之后，
 * 否则直接移动到目标数组顶端
 * 
 * 这也是与实际对应的，一个盘子只能移动到一个盘子上方，
 * 除非柱子为空
 * 
 */
void move(int *A, int *B, int *C, int *moveN)
{
    // 函数圆形
    int * getaddr(int *A, int * B, int *C, int n);
    void printStep(int *A, int * B, int *C, int *moveN);
    
    // 打印移动操作
    printStep(A, B, C, moveN);
    
    // 获取两个数的地址
    int *a = getaddr(A, B, C, moveN[0]);
    int *b = getaddr(A, B, C, moveN[1]);
    
    // 如果目标数为0，则地址加1，否则不变
    b = moveN[1]? (b + 1 ): b;
    
    // 将要移动的数移动后，直接将原来位置赋0
    *b = *a;
    *a = 0;
    
    show(A, B, C);
    // 移动后改变1的状态
    // 如果先前1可移动（为0），则变为不可移动
    if (count_one == 0)
        count_one = 1;
        
    // 如果先前不可移动，则变为可移动
    else
        count_one = 0;
    
    return;
}

// 打印移动动作
void printStep(int *A, int * B, int *C, int *moveN)
{
    char start, goal;
    
    show(A, B, C, size);
    
    for (int i = 0; i < size; i++)
    {
        if (A[i] == moveN[0])
            start = 'A';
        if (B[i] == moveN[0])
            start = 'B';
        if (C[i] == moveN[0])
            start = 'C';
        
        if (moveN[1] != 0)
        {
            if (A[i] == moveN[1])
                goal = 'A';
            if (B[i] == moveN[1])
                goal = 'B';
            if (C[i] == moveN[1])
                goal = 'C';
        }
        else
        {
            if (A[0] == 0)
                goal = 'A';
            if (B[0] == 0)
                goal = 'B';
            if (C[0] == 0)
                goal = 'C';
        }
    }
    
    printf("%c --> %c \n", start, goal);
}

// 判断是否完成,暂时无用
/*********************************************************
int win(int *A, int * B, int *C)
{
    int b = size;
    int c = size;
    
    int condition1, condition2;
    
    for (int i = 0; i < size; i++)
    {
        if (A[i] != 0)
            return 1; 
        
        //condition1 = (C[i] != b--) && (B[i] != 0)?0:1;
        //condition2 = (B[i] != c--) && (C[i] != 0)?0:1;
        
        if (condition1)
            return 2;
        
        if (condition2)
            return 3;
    }
    return 0;
}
***********************************************************/

// 打印
void show(int *A, int * B, int *C)
{
    printf("A:\n");
    for (int i = 0; i < size; i++)
    {
        if (A[i] != 0)
            printf("%2i", A[i]);
        else
            printf(" _");
    }
    printf("\n");
    
    printf("B:\n");
    for (int i = 0; i < size; i++)
    {
        if (B[i] != 0)
            printf("%2i", B[i]);
        else
            printf(" _");
    }
    printf("\n");
    
    printf("C:\n");
    for (int i = 0; i < size; i++)
    {
        if (C[i] != 0)
            printf("%2i", C[i]);
        else
            printf(" _");
    }
    printf("\n\n");
    
}
