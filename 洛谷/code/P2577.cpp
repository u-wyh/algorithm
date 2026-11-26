// https://www.luogu.com.cn/problem/P2577
// 题意：N 个人分两队到两个窗口打饭（打饭时间 A_i，吃饭时间 B_i），打完立刻吃。
// 求所有人吃完饭的最早时刻。
// 输出最早时刻。
// 数据范围：N, A_i, B_i 均为不超过 200 的正整数。
#include<bits/stdc++.h>
using namespace std;

struct node{
    int a,b;
}nums[205];
int n,sum[205];
int f[205][205*205];

bool cmp(node a,node b){
    return a.b==b.b?a.a<b.a:a.b>b.b;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i].a>>nums[i].b;
    }
    sort(nums+1,nums+n+1,cmp);
    for(int i=1;i<=n;i++){
        sum[i]=sum[i-1]+nums[i].a;
    }
    //sum[0]=40000;
    for(int i=0;i<=n;i++){
        for(int j=0;j<=sum[n];j++){
            f[i][j]=INT_MAX;
        }
    }
    f[0][0]=0;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=sum[i];j++){
            if(j>=nums[i].a){
                f[i][j]=min(f[i][j],max(f[i-1][j-nums[i].a],j+nums[i].b));
            }
            f[i][j]=min(f[i][j],max(f[i-1][j],sum[i]-j+nums[i].b));
        }
    }
    int ans=INT_MAX;
    for(int i=0;i<=sum[n];i++){
        ans=min(ans,f[n][i]);
    }
    cout<<ans<<endl;
    return 0;
}
