// https://www.luogu.com.cn/problem/P3897
// 题意：在平面上给出 n 个点（兔子）的坐标和一个圆心在原点、半径为 r
// 的圆形障碍（所有点严格在圆外，任意两点连线不与圆相切）。
// 从中选出尽量多的点，使得选出的点中任意两点所在的直线都不与圆相交，
// 输出最多能选出的点数。
// 数据范围：1 <= n <= 2000，
// 1 <= r, x_i, y_i <= 5000。
// 算法标签：模拟
#include<stdio.h>

int main()
{
    int k,a,b,c;
    scanf("%d %d %d %d",&k,&a,&b,&c);
    int nums[k];
    for(int i=0;i<k;i++)
    {
        scanf("%d",&nums[i]);
    }
    int sum=0;
    for(int i=0;i<k;i++)
    {
        if(nums[i]<=10)
            sum+=nums[i]*a;
        else if(nums[i]<=100)
            sum+=((nums[i]-10)*b+10*a);
        else
            sum+=((nums[i]-100)*c+90*b+10*a);
    }
    printf("%d\n",sum);
    return 0;
}
