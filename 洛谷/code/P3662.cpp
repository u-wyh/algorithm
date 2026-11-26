// https://www.luogu.com.cn/problem/P3662
// 题意：输入信号灯总数 N、目标连续正常长度 K、损坏数量 B，以及 B 个损坏信号灯的编号。
// 需修复尽量少的损坏信号灯，使得 1..N 中至少存在一段连续 K 个信号灯全部正常工作。
// 输出最少需要修复的信号灯数量。
// 数据范围：1 <= N <= 100000，1 <= B, K <= N。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,k,m;
int nums[MAXN];
int sum[MAXN];

int main()
{
    cin>>n>>k>>m;
    for(int i=1;i<=m;i++){
        int a;
        cin>>a;
        nums[a]=1;
    }
    for(int i=1;i<k;i++){
        sum[i]+=sum[i-1]+nums[i];
    }
    int ans=INT_MAX;
    for(int i=k;i<=n;i++){
        sum[i]+=sum[i-1]+nums[i];
        sum[i]-=nums[i-k];
        ans=min(ans,sum[i]);
    }
    cout<<ans;
    return 0;
}
