// https://www.luogu.com.cn/problem/P9586
// 题意：多组数据（共 T 组）。
// 小 C 与小 D 玩牌，牌有“杀、闪、斩”三种：小 C 有 c_1 杀、c_2 闪、c_3 斩，小 D 有 d_1 杀、d_2 闪、d_3 斩（明牌）。
// 小 C 先手回合交替，回合内可出任意张杀或斩（打完弃掉）：出杀需对方用闪回应，出斩需对方用杀回应，无法回应即输。
// 双方绝顶聪明，判断结果。
// 题意：第一行输入 T，每组输入六个整数 c_1, c_2, c_3, d_1, d_2, d_3；
// 每组输出 C（小 C 胜）、D（小 D 胜）或 E（平局）。
// 数据范围：1 <= T <= 10^5，0 <= c_1, c_2, c_3, d_1, d_2, d_3 <= 10^9。
// 算法标签：分类讨论
#include<stdio.h>

int main()
{
    int t;
    scanf("%d",&t);
    int c1,c2,c3,d1,d2,d3;
    for(int i=1;i<=t;i++){
        scanf("%d %d %d %d %d %d",&c1,&c2,&c3,&d1,&d2,&d3);
        if(c1>d2||c3>d1)
            printf("C\n");
        else if(d3>c1||d1-c3>c2)
            printf("D\n");
        else
            printf("E\n");
    }
    return 0;
}
