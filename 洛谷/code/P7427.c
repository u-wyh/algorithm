// https://www.luogu.com.cn/problem/P7427
// 题意：进行 n 轮无平局游戏，第 i 轮胜者得 i 分；
// 给定两人得分 a, b，判断是否存在合法总轮数 n 及胜负方案并输出 n 与 ljcc 获胜的轮次（无解输出 No，禁止行末空格/多余回车）。
// 数据范围：a, b <= 2^31 - 1，1 <= n <= 10^5。
#include<stdio.h>
#include<math.h>

int main()
{
    long long a,b,n;
    scanf("%lld %lld",&a,&b);
    n=sqrt(2*(a+b));
    if(n*(n+1)!=2*(a+b)){
        printf("No\n");
        return 0;
    }
    printf("%lld ",n);
    for(int i=n;i>=1;i--){
        if(a>i){
            a-=i;
            printf("%d ",i);
        }
        else if(a==i){
            printf("%d",i);
            break;
        }
    }
    return 0;
}
