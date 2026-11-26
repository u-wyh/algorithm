// https://www.luogu.com.cn/problem/P8208
// 题意：N 个地点（1..N），从 s_0 出发共进行 T 次掷骰子移动（经历 s_0, s_1, ..., s_T）
// 在地点 i 会等概率前往其 m_i 个互不相同候选地点之一。
// 若第 t 步到达的 s_t 之前到过（设上一次到 s_t 是在 t' 时刻，且当时下一步去了 s_{t'+1}）
// 则累计得分 s_{t'+1}（若 s_T 之前到过同样累计）。
// 求总得分的期望对 998244353 取模。
// 数据范围：100% 数据满足 1 <= N <= 100，1 <= T <= 100，1 <= s_0 <= N，1 <= m_i <= N
// sum(m_i) <= 5000，1 <= l_{i,j} <= N，同一地点的候选目的地点互不相同。
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 998244353;
const int MAXN = 105;

int n,st,m;
int cnt[MAXN];
int inv[MAXN];
int to[MAXN][MAXN];
int f[MAXN][MAXN];
int g[MAXN][MAXN];

int power(int a,int b){
    int ans=1;
    while(b){
        if(b&1){
            ans=(a*ans)%MOD;
        }
        a=(a*a)%MOD;
        b>>=1;
    }
    return ans;
}

signed main()
{
    cin>>n>>st>>m;
    for(int i=1;i<=n;i++){
        cin>>cnt[i];
        inv[i]=power(cnt[i],MOD-2);
        for(int j=1;j<=cnt[i];j++){
            cin>>to[i][j];
        }
    }

    f[0][st]=1;
    for(int i=0;i<m;i++){
        for(int u=1;u<=n;u++){
            for(int j=1;j<=cnt[u];j++){
                f[i+1][to[u][j]]=(f[i+1][to[u][j]]+f[i][u]*inv[u])%MOD;
            }
        }
    }

    int ans=0;
    for(int i=1;i<=n;i++){
        memset(g,0,sizeof(g));
        for(int j=1;j<=cnt[i];j++){
            g[1][to[i][j]]=(inv[i]*to[i][j])%MOD;
        }

        for(int k=1;k<m;k++){
            for(int u=1;u<=n;u++){
                if(u==i||!g[k][u]){
                    continue;
                }
                for(int j=1;j<=cnt[u];j++){
                    g[k+1][to[u][j]]=(g[k+1][to[u][j]]+g[k][u]*inv[u])%MOD;
                }
            }
        }

        for(int j=0;j<m;j++){
            for(int k=1;k<=m-j;k++){
                ans=(ans+f[j][i]*g[k][i])%MOD;
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}