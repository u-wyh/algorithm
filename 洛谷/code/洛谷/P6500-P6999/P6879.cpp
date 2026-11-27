// https://www.luogu.com.cn/problem/P6879
// 题意：周长为 L 的圆上从原点出发每秒移动 1 米（可顺时针或逆时针折返），
// 第 i 个雕像在顺时针 X_i 米处且须在 T_i 秒内收集否则爆炸
// 求最多能收集的雕像数量。
// 数据范围：1 <= N <= 200，2 <= L <= 10^9，
// 1 <= X_i < L，X_i < X_{i+1}
// 0 <= T_i <= 10^9。
// 算法标签：区间动态规划
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 205;
const int INF = 1e10;

int n,m;
int pos[MAXN];
int t[MAXN];
int f[MAXN][MAXN][MAXN][2];

signed main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>pos[i];
    }
    pos[n+1]=m;
    for(int i=1;i<=n;i++){
        cin>>t[i];
    }
    for(int i=0;i<=n+1;i++){
        for(int j=0;j<=n+1;j++){
            for(int k=0;k<=n+1;k++){
                f[i][j][k][0]=f[i][j][k][1]=INF;
            }
        }
    }
    f[0][0][0][0]=f[0][0][0][1]=0;
    for(int l=0;l<=n;l++){
        for(int r=0;r<=n;r++){
            if(l+r>=n){
                break;
            }
            for(int k=0;k<=n;k++){
                int tmp=f[l][r][k][0];
                if(tmp<=INF){
                    f[l+1][r][k+(tmp+pos[n-l+1]-pos[n-l]<=t[n-l])][0]=min(f[l+1][r][k+(tmp+pos[n-l+1]-pos[n-l]<=t[n-l])][0],tmp+pos[n-l+1]-pos[n-l]);
                    f[l][r+1][k+(tmp+m-pos[n-l+1]+pos[r+1]<=t[r+1])][1]=min(f[l][r+1][k+(tmp+m-pos[n-l+1]+pos[r+1]<=t[r+1])][1],tmp+m-pos[n-l+1]+pos[r+1]);
                }
                tmp=f[l][r][k][1];
                if(tmp<=INF){
                    f[l+1][r][k+(tmp+m+pos[r]-pos[n-l]<=t[n-l])][0]=min(f[l+1][r][k+(tmp+m+pos[r]-pos[n-l]<=t[n-l])][0],tmp+m+pos[r]-pos[n-l]);
                    f[l][r+1][k+(tmp-pos[r]+pos[r+1]<=t[r+1])][1]=min(f[l][r+1][k+(tmp-pos[r]+pos[r+1]<=t[r+1])][1],tmp-pos[r]+pos[r+1]);
                }
            }
        }
    }
    int ans=0;
    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++){
            for(int k=0;k<=n;k++){
                if(min(f[i][j][k][0],f[i][j][k][1])<INF){
                    ans=max(ans,k);
                }
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}
