// https://www.luogu.com.cn/problem/P1258
// 题意：甲乙两人同时从 A 地出发前往相距 s 的 B 地，两人步行速度均为 a，小车速度为 b（a < b）。
// 题意：A 地有一辆小车（除驾驶员外最多载一人），求两人同时到达 B 地的最短时间。
// 输入：一行输入三个实数 s, a, b。
// 输出：输出两人同时到达的最短时间，保留 6 位小数。
// 数据范围：0 <= s, a, b <= 10^9。
#include<stdio.h>
// 算法标签：数学

int main()
{
    int n,a,b;
    scanf("%d %d %d",&n,&a,&b);
    double t;
    t=(1.0*n/(2+1.0*(a-b)/(a+b))/b)+(n-(1.0*n/(2+1.0*(a-b)/(a+b))))/a;
    printf("%.6lf",t);
    return  0;
}
