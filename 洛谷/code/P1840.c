// https://www.luogu.com.cn/problem/P1840
// 题意：数轴上 1 到 n 的点起初都是黑色。每次把闭区间 [l_i,r_i] 内的点染白，输出操作后剩余的黑点数。
// 数据范围：1 ≤ n,m ≤ 2×10^5，1 ≤ l_i ≤ r_i ≤ n。
// 算法标签：暴力枚举、模拟

#include<stdio.h>
#include<string.h>

int vis[200005];
int n,m;

int main()
{
    scanf("%d %d",&n,&m);
    int l,r;
    int ans=n;
    for(int i=1;i<=m;i++){
        scanf("%d %d",&l,&r);
        int k=r-l+1;
        for(int i=l;i<=r;i++){
            if(vis[i]==1){
                k--;
            }
            vis[i]=1;
        }
        ans-=k;
        printf("%d\n",ans);
    }
    return 0;
}
