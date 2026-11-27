// https://www.luogu.com.cn/problem/P9515
// 题意：你从数轴原点 0 在时刻 0 出发，每秒至多移动 1 单位，
// 必须在时刻 t 或之前到达坐标 f（之后一直停在 f）。
// 数轴上有 n 个签到处，
// 第 i 个位于 x_i 且从时刻 a_i
// 开始营业（经过且当前时刻 >= a_i 即可签到，不耗时间，不限按编号顺序）。
// 求最多能去多少个签到处签到。
// 题意：第一行输入 n, t, f，接下来 n 行每行输入 x_i, a_i；
// 输出一个非负整数。
// 数据范围：1 <= n <= 10^6，
// 0 <= f <= t <= 10^18，0 <= x_i <= f
// 0 <= a_i <= t（不保证 x_i 互不相同）。
// 算法标签：线性扫描
#include<stdio.h>

int main()
{
    int n,t,f,k;
    scanf("%d %d %d",&n,&t,&f);
    k=t-f;
    long long x,a;
    int ans=0;
    for(int i=1;i<=n;i++){
        scanf("%lld %lld",&x,&a);
        if((k+x)>=a){
            ans++;
        }
    }
    printf("%d\n",ans);
}
