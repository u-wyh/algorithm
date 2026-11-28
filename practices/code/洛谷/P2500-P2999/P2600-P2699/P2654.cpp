// https://www.luogu.com.cn/problem/P2654
// 题意：有 n 只原核生物各有初始重量，共进行 k 次实验。
// 每次取重量最小的 m 个按给定顺序排成环，相邻两只融合（耗能为两只重量之和）。
// 每次实验剩余 1 只放回培养皿，求 k 次实验的最小总耗能。
// 数据范围：1 < n <= 1000，1 <= m <= 10，
// 1 <= k <= 100，结果不超过 2^31。
// 难度评分：1800（洛谷分级换算）
// 算法标签：贪心、优先队列、区间动态规划
#include<bits/stdc++.h>
using namespace std;
#define int long long 

int n,m,k;
int dp[21][21];
int nums[21];
int sum[21];
int ord[11];
priority_queue<int,vector<int>,greater<int>>heap;

int compute(){
    sum[0]=0;
    for(int i=1;i<=2*m;i++){
        sum[i]=sum[i-1]+nums[i];
        // cout<<nums[i]<<' ';
    }
    // cout<<endl;
    for(int i=1;i<=2*m;i++){
        for(int j=1;j<=2*m;j++){
            dp[i][j]=INT_MAX;
        }
    }
    for(int i=1;i<=2*m;i++){
        dp[i][i]=0;
    }
    for(int len=2;len<=m;len++){
        for(int i=1;i<=2*m-len+1;i++){
            int j=i+len-1;
            for(int k=i;k<j;k++){
                dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j]+sum[j]-sum[i-1]);
            }
        }
    }
    int ans=LLONG_MAX;
    for(int i=1;i<=m+1;i++){
        ans=min(ans,dp[i][i+m-1]);
    }
    return ans;
}

signed main()
{
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++){
        int v;
        cin>>v;
        heap.push(v);
    }
    int ans=0;
    for(int i=1;i<=k;i++){
        for(int j=1;j<=m;j++){
            int u;
            cin>>u;
            ord[u]=j;
        }
        int all=0;
        for(int j=1;j<=m;j++){
            int u=heap.top();
            heap.pop();
            nums[ord[j]]=u;
            all+=u;
        }
        for(int j=m+1;j<=2*m;j++){
            nums[j]=nums[j-m];
        }
        ans+=compute();
        heap.push(all);
    }
    cout<<ans<<endl;
    return 0;
}