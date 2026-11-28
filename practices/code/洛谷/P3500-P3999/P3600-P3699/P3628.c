// https://www.luogu.com.cn/problem/P3628
// 题意：输入士兵人数 n、二次修正系数 a, b, c（a < 0），
// 以及第 1..n 号士兵的初始战斗力 x_i。
// 将 1..n 号士兵按顺序划分为若干编号连续的特别行动队，
// 每队初始战力和为 X 时其修正战斗力为 a*X^2 + b*X + c。
// 输出所有行动队修正战斗力之和的最大值。
// 数据范围：1 <= n <= 10^6，-5 <= a <= -1，
// -10^7 <= b, c <= 10^7，1 <= x_i <= 100。
// 难度评分：1900（洛谷分级换算）
// 算法标签：前缀和
#include<stdio.h>

int min(int a,int b){
    return a<b?a:b;
}

int main()
{
    int n;
    scanf("%d",&n);
    int a[n+1],sum[n+1],minans=0;
    sum[0]=0;
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        sum[i]=sum[i-1]+a[i];
        minans=min(minans,sum[i]);
    }
    if(minans>=0){
        printf("0\n");
    }else{
        printf("%d",-minans+1);
    }
    return 0;
}
