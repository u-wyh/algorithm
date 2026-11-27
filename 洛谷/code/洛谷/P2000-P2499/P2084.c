// https://www.luogu.com.cn/problem/P2084
// 题意：给定进制 M 和一个 M 进制正整数 N。
// 将 N 按十进制形式展开为多项式相加式子（系数*M^权值）。
// 系数为 0 的项省略，非零项之间用 + 连接。
// 数据范围：1 < M < 10，N 的位数不超过 1000。
// 算法标签：模拟、字符串
#include<stdio.h>
#include<string.h>

#define Max 1001

int main()
{
    int m;
    char str[Max];
    scanf("%d",&m);
    scanf(" ");
    fgets(str,Max,stdin);
    int n=strlen(str)-1;
    if(str[0]-'0'!=0)
        printf("%d*%d^%d",str[0]-'0',m,n-1);
    for(int i=1;i<n;i++)
    {
        if(str[i]-'0'!=0)
        {
            printf("+%d*%d^%d",str[i]-'0',m,n-i-1);
        }
    }
    return 0;
}
