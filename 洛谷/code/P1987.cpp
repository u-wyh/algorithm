// https://www.luogu.com.cn/problem/P1987
// 题意：每棵摇钱树初有 m_i 枚金币，每过一天会掉 b_i 枚。每天最多砍一棵树并拿走树上剩余的金币。求 k 天内最多获得多少金币。
// 数据范围：至多 10 组，1 ≤ n,k ≤ 1000，1 ≤ m_i ≤ 10^5，1 ≤ b_i ≤ 1000，以 0 0 结束。
// 算法标签：动态规划、排序

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e3+5;

struct node{
    int val,cost;
}nums[MAXN];
int n,m;
int f[MAXN][MAXN];

bool cmp(node a,node b){
    return a.cost>b.cost;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    scanf("%d %d",&n,&m);
    while(n+m){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                f[i][j]=0;
            }
        }
        for(int i=1;i<=n;i++){
            scanf("%d",&nums[i].val);
        }
        for(int i=1;i<=n;i++){
            scanf("%d",&nums[i].cost);
        }
        sort(nums+1,nums+n+1,cmp);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=min(i,m);j++){
                f[i][j]=max(f[i-1][j],f[i-1][j-1]+max(0,nums[i].val-nums[i].cost*(j-1)));
            }
        }
        int ans=0;
        for (int i=1;i<=m;i++)
            ans = max(ans, f[n][i]);
        printf("%d\n",ans);
        scanf("%d %d",&n,&m);
    }
    return 0;
}
