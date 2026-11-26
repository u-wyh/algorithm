// https://www.luogu.com.cn/problem/P2625
// 题意：给定 n 条移动或转向指令（right/left/forward/backward X）。
// 重排指令顺序，使最终位置到起点的欧几里得距离最大。
// 输出最大距离，四舍五入保留 6 位小数。
// 数据范围：1 <= n <= 50，角度 in [1, 719]，距离 in [1, 1000]。
#include<stdio.h>
#include<string.h>

struct travel
{
    char str[20];
    int nums;  // 注意这里添加了分号
};

int main()
{
    int n;
    scanf("%d", &n);
    getchar();  // 读取并丢弃之前的换行符
    struct travel t[n+1];

    for(int i = 1; i <= n; i++)
    {
        fgets(t[i].str, 20, stdin);
        while (getchar() == '\0')
        scanf("%d", &t[i].nums);
    }

    // 示例：打印读取的数据
    for(int i = 1; i <= n; i++)
    {
        printf("%s %d\n", t[i].str, t[i].nums);
    }

    return 0;
}
/*#include<stdio.h>
#include<math.h>
#include<string.h>

struct travel
{
    char str[20];
    int nums;
};
int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int n;
    scanf("%d",&n);
    struct travel t[n+1];
    for(int i=1;i<=n;i++)
    {
        fgets(t[i].str,20,stdin);
        scanf("%d",t[i].nums);
    }
    return 0;
}*/
