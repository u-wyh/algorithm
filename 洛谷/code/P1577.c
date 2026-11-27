// https://www.luogu.com.cn/problem/P1577
// 题意：输入 N 条绳子的长度 L_i，以及需要切割出的相同绳子段数 K。
// 只能切割不能拼接，求每段绳子最长能有多少。
// 输出最大长度，保留小数点后 2 位（直接舍去 2 位后小数，误差允许 0.01 或 1%）。
// 数据范围：
// 0 < n <= 10000（绳子条数 N）
// 0 < k <= 10000（目标段数 K）
// 0 < L_i <= 100000.00（绳子长度）
#include<stdio.h>
// 算法标签：二分答案

double max(double a,double b){
    return a>b?a:b;
}

int check(double x,double *nums,int n,int k){
    int ans=0;
    for(int i=1;i<=n;i++){
        ans+=(int)(nums[i]/x);
        if(ans>=k)
            return ans;
    }
    return ans;
}

int main()
{
    int n,k;
    scanf("%d %d",&n,&k);
    double nums[n+1],r=0,l=0,mid,ans;
    for(int i=1;i<=n;i++){
        scanf("%lf",&nums[i]);
        r=max(r,nums[i]);
    }
    while(r-l>=1e-4){
        mid=(l+r)/2;
        if(check(mid,nums,n,k)>=k){
            l=mid;
            ans=mid;
        }else{
            r=mid;
        }
    }
    printf("%.2lf",ans);
    return 0;
}
