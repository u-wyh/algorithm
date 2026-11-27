// https://www.luogu.com.cn/problem/P4326
// 题意：给出半径 R，
// 分别输出欧几里得几何下圆的面积（pi * R^2）和曼哈顿距离
// （出租车几何）下圆的面积（2 * R^2）
// 绝对误差不超过 0.0001。
// 数据范围：R <= 10000。
// 算法标签：数学
#include<stdio.h>
#include<math.h>

#define pi 3.1415926535897

int main()
{
    int n;
    scanf("%d",&n);
    double s1,s2;
    s1=pi*pow(n,2);
    printf("%.6lf\n",s1);
    s2=2*pow(n,2);
    printf("%.6lf\n",s2);
    return 0;
}
