// https://www.luogu.com.cn/problem/P3150
// 题意：输入游戏局数 N，以及每局初始的正整数 M。
// pb 先手把当前数拆成两个正整数之和，
// 之后双方轮流选择上一轮拆出的两个数之一继续拆成两个正整数之和，不能拆者负。
// 判断每局双方绝顶聪明时谁获胜。
// 输出 N 行，pb 必胜输出 pb wins，否则输出 zs wins。
// 数据范围：1 < N < 50，1 <= M <= 10^9。
// 难度评分：1200（洛谷分级换算）
// 算法标签：博弈论、数学
#include<stdio.h>

int main()
{
    int t;
    scanf("%d",&t);
    for(int i=1;i<=t;i++){
        int n;
        scanf("%d",&n);
        if(n%2==0){
            printf("pb wins\n");
        }else{
            printf("zs wins\n");
        }
    }
    return 0;
}
