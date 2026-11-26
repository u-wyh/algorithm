// https://www.luogu.com.cn/problem/P4860
// 题意：T 组询问，每组有 n 个石子，两人轮流每次取 p^k 个（p 为质数且 k 为 0 或 1，即每次取 1 个或质数个），取完最后石子者胜
// October 先手，判断谁有必胜策略。
// 数据范围：1 <= T <= 10^5，1 <= n <= 5 * 10^7。
#include<stdio.h>

int main()
{
    int t;
    scanf("%d",&t);
    for(int i=1;i<=t;i++){
        int n;
        scanf("%d",&n);
        if(n%4==0){
            printf("Roy wins!\n");
        }else{
            printf("October wins!\n");
        }
    }
    return 0;
}
