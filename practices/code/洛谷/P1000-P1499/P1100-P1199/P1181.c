// https://www.luogu.com.cn/problem/P1181
// 题意：给一列非负整数，把它从头到尾划成若干连续非空段，每段和不超过 M。
// 求最少需要分几段。
// 数据范围：1 ≤ N ≤ 10^5，1 ≤ M ≤ 10^9，M 大于每一项，
// 序列总和不超过 10^9。
// 难度评分：1000（洛谷分级换算）
// 算法标签：二分答案、贪心

#include<stdio.h>
#include<stdbool.h>

bool check(int limit,int *nums,int n,int m){
    int ans=1,sum=0;
    for(int i=1;i<=n;i++){
        if((sum+nums[i])>m){
            ans++;
            sum=nums[i];
        }else{
            sum+=nums[i];
        }
        if(ans>limit){
            return false;
        }
    }
    return ans<=limit;
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int nums[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d",&nums[i]);
    }
    int l=1,r=n,mid,ans=n;
    while(l<=r){
        mid=l+((r-l)>>1);
        if(check(mid,nums,n,m)){
            ans=mid;
            r=mid-1;
        }else{
            l=mid+1;
        }
    }
    printf("%d\n",ans);
    return 0;
}
