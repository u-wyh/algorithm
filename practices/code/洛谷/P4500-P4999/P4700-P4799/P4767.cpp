// https://www.luogu.com.cn/problem/P4767
// 题意：数轴上有 V 个已知坐标的村庄，选位置建 P 个邮局，
// 求各村庄到最近邮局距离之和的最小值。
// 数据范围：1 <= P <= 300，P <= V <= 3000，
// 1 <= 村庄位置 <= 10000。
// 难度评分：2300（洛谷分级换算）
// 算法标签：动态规划、四边形不等式优化、前缀和
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3005;
const int MAXM = 305;
const int INF = 1e9;

int n,m;
int pos[MAXN];
int pre[MAXN];
int cost[MAXN][MAXN];
int dp[MAXN][MAXM];
int opt[MAXN][MAXM];

void prepare(){
    for(int i=1;i<=n;i++){
        pre[i]=pos[i]+pre[i-1];
    }
    for(int i=1;i<=n;i++){
        cost[i][i]=0;
        for(int j=i+1;j<=n;j++){
            int mid=(i+j)/2;
            int lt=(mid-i+1)*pos[mid]-(pre[mid]-pre[i-1]);
            int rt=(pre[j]-pre[mid])-(j-mid)*pos[mid];
            cost[i][j]=lt+rt;
        }
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>pos[i];
    }
    sort(pos+1,pos+n+1);

    prepare();

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            dp[i][j]=INF;
        }
    }
    for(int i=1;i<=n;i++){
        dp[i][1]=cost[1][i];
    }

    for(int j=2;j<=m;j++){
        opt[n+1][j]=n;
        for(int i=n;i>=1;i--){
            int mink=opt[i][j-1];
            int maxk=opt[i+1][j];
            for(int k=mink;k<=maxk;k++){
                if(dp[k][j-1]+cost[k+1][i]<dp[i][j]){
                    dp[i][j]=dp[k][j-1]+cost[k+1][i];
                    opt[i][j]=k;
                }
            }
        }
    }
    cout<<dp[n][m]<<endl;
    return 0;
}