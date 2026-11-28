// https://www.luogu.com.cn/problem/P7404
// 题意：给定长为 N 的序列 A，每次可将区间 [L, R] 所有数加 1
// 求使新序列 B 成为单峰序列
// （存在 k 使 B_1 < ... < B_k
// 且 B_k > ... > B_N）的最少操作次数。
// 数据范围：1 <= N <= 2*10^5，1 <= A_i <= 10^9。
// 难度评分：1200（洛谷分级换算）
// 算法标签：差分、前缀和、贪心
#include<bits/stdc++.h>
using namespace std;

int n;
int nums[200005],d[200005];
long long x[200005],y[200005];

int main()
{
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>nums[i];
    }
    for(int i=1;i<n;i++){
        d[i]=nums[i]-nums[i-1];
    }
    for(int i=1;i<n;i++){
        if(d[i]<=0)
            x[i]=x[i-1]+1-d[i];
        else
            x[i]=x[i-1];
    }
    for(int i=n-1;i>=0;i--){
        if(d[i]>=0)
            y[i]=y[i+1]+d[i]+1;
        else
            y[i]=y[i+1];
    }
    long long  ans=1e15;
    for(int i=0;i<n;i++)
        ans=min(ans,max(x[i],y[i+1]));
    cout<<ans;
    //这道题是L到R区间  所以d[L]++  d[R+1]--但是我们不考虑一加一减
    //我们只在乎一个加或者减   到最后取最大值  即在完成一个任务时候顺便实现第二个目标
    return 0;
}
