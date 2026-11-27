// https://www.luogu.com.cn/problem/P4544
// 题意：从 X=0 走到 X=E 的数轴上有 N
// 家商店（位置 X_i，库存 F_i，单价 C_i），
// 车上载重 X 吨每走 1 公里花费 X^2 元
// 求买够 K 吨饲料并运到终点的最小总花费。
// 数据范围：1 <= K <= 10000，1 <= E <= 500，
// 1 <= N <= 500，0 < X_i < E
// 1 <= F_i <= 10000，1 <= C_i <= 10^7。
// 算法标签：动态规划、单调队列
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 505;
const int MAXK = 1e4+5;
const int INF = 1e15;

int k,e,n;

struct node{
    int pos,per,have;
}nums[MAXK];
int dis[MAXN];
int dp[MAXN][MAXK];
int q[MAXK];
int head,tail;

bool cmp(node a,node b){
    return a.pos<b.pos;
}

signed main()
{
    cin>>k>>e>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i].pos>>nums[i].have>>nums[i].per;
    }
    nums[++n].pos=e;
    sort(nums+1,nums+n+1,cmp);
    for(int i=2;i<=n;i++){
        dis[i]=nums[i].pos-nums[i-1].pos;
    }
    for(int i=0;i<=n;i++){
        for(int j=0;j<=k;j++){
            dp[i][j]=INF;
        }
    }
    dp[0][0]=0;
    for(int i=1;i<=n;i++){
        head=tail=0;
        for(int j=0;j<=k;j++){
            while(head<tail&&(j-q[head]>nums[i-1].have)){
                head++;
            }
            if(dp[i-1][j]!=INF){
                while(head<tail){
                    int p=q[tail-1];
                    if(dp[i-1][j]-j*nums[i-1].per>dp[i-1][p]-p*nums[i-1].per){
                        break;
                    }
                    tail--;
                }
                q[tail++]=j;
            }
            if(head<tail){
                int p=q[head];
                dp[i][j]=j*j*dis[i]+dp[i-1][p]+(j-p)*nums[i-1].per;
            }
        }
    }
    cout<<dp[n][k];
    return 0;
}