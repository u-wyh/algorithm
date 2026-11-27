// https://www.luogu.com.cn/problem/P2241
// 题意：给定 n*m 的方格棋盘，统计其中包含的正方形和长方形（不含正方形）个数。
// 输出正方形个数和长方形个数。
// 数据范围：1 <= n, m <= 5000。
// 算法标签：枚举、组合数学
#include<stdio.h>

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    long long ans1=0,ans2=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(i==j){
                ans1+=(n-i+1)*(m-j+1);
            }else{
                ans2+=(n-i+1)*(m-j+1);
            }
        }
    }
    printf("%lld %lld\n",ans1,ans2);
    return 0;
}
