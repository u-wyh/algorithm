// https://www.luogu.com.cn/problem/P8109
// 题意：有 n 道题与 n 种颜色的气球，第 i 题有 a_i 队通过，第 j 种颜色有 b_j 个气球，且 {a_n}, {b_n} 均单调不降。
// 每道题只能对应一种气球颜色、每种颜色只能对应一道题
// 求所有题最多能派发的气球总数（即选定排列 π 最大化 ∑_{i=1}^n min(a_i, b_{π_i})）。
// 第一行输入 n，第二行 n 个整数 a_i，第三行 n 个整数 b_i。
// 输出一行一个整数。
// 数据范围：1 <= n <= 10^5，0 <= a_i, b_i <= 10^4，且 {a_n}, {b_n} 单调不降。
#include<stdio.h>

int min(int a,int b){
    return a<b?a:b;
}

int main()
{
    int n;
    scanf("%d",&n);
    int a[n+1],b[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d",&a[n-i+1]);
    }
    for(int i=1;i<=n;i++){
        scanf("%d",&b[n-i+1]);
    }
    long long ans=0;
    for(int i=1;i<=n;i++){
        ans+=min(a[i],b[i]);
    }
    printf("%lld\n",ans);
    return 0;
}
