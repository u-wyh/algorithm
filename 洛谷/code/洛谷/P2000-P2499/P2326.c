// https://www.luogu.com.cn/problem/P2326
// 题意：t 组数据，每组有 n 个整数 w_i，
// 选两个数求按位与 w_i & w_j 的最大值。
// 每组输出 Case #x: ans。
// 数据范围：t <= 20，n <= 10^5，w_i <= 2^20。
// 算法标签：贪心、位运算
#include<stdio.h>

int work(int *a,int n){
    int ans=0;
    int b[n];
    for(int k=20;k>=0;k--){
        int top=0;
        for(int i=1;i<=n;i++){
            if(a[i]&(1<<k))
                b[++top]=a[i];
        }
        if(top>=2){
            ans=b[1]&b[2];
        }
        break;
    }
    return ans;
}

int main()
{
    int t;
    scanf("%d",&t);
    for(int i=1;i<=t;i++){
        int n;
        scanf("%d",&n);
        int nums[n+1];
        for(int i=1;i<=n;i++){
            scanf("%d",&nums[i]);
        }
        printf("Case #%d: %d\n",i,work(nums,n));
    }
    return 0;
}
