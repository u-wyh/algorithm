// https://www.luogu.com.cn/problem/P1969
// 题意：有 n 列积木，初始高度都是 0。
// 每次选一个连续区间，把区间内所有列的高度同时加 1。
// 求达到给定高度 h_i 所需的最少操作次数。
// 数据范围：1 ≤ n ≤ 10^5，0 ≤ h_i ≤ 10000。
// 算法标签：贪心、差分

#include<stdio.h>

int main()
{
    int n;
    scanf("%d",&n);
    int ans=0,a,last=0;
    for(int i=1;i<=n;i++){
        scanf("%d",&a);
        if(a>last){
            ans+=a-last;
        }
        last=a;
    }
    printf("%d\n",ans);
    return 0;
}
