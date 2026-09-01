#include<bits/stdc++.h>
using namespace std;

const int MAXN = 505;
const int MAXE = 250005;
const int MAXW = 8;
const int INF = 0x3f3f3f3f;
const int MOD = 998244353;

int T;
int n,m,s,t;

int head[MAXN];
int nxt[MAXE];
int to[MAXE];
int cntg;

int ds[MAXN]; // s 到各点的最短距离
int dt[MAXN]; // t 到各点的最短距离
int q[MAXN];

// nb[u] 表示点 u 的闭邻域 N[u]，使用 bitset 压位存储
unsigned long long nb[MAXN][MAXW];

// nbsz[u] = |N[u]|
int nbsz[MAXN];

// inter[u][v] = |N[u] ∩ N[v]|
int inter[MAXN][MAXN];

/*
    dp[u][v]：
    当前最短路最后两个点为 u,v 时，
    已覆盖闭邻域并集的最小大小

    ways[u][v]：
    达到 dp[u][v] 的路径数量
*/
int dp[MAXN][MAXN];
int ways[MAXN][MAXN];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

inline void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

void bfs(int st,int *dis){
    for(int i=1;i<=n;i++){
        dis[i]=-1;
    }

    int l=1,r=0;
    q[++r]=st;
    dis[st]=0;

    while(l<=r){
        int u=q[l++];

        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];

            if(dis[v]==-1){
                dis[v]=dis[u]+1;
                q[++r]=v;
            }
        }
    }
}

// 计算 |N[a] ∩ N[b] ∩ N[c]|
inline int get3(int a,int b,int c,int W){
    int res=0;

    for(int i=0;i<W;i++){
        res+=__builtin_popcountll(
            nb[a][i]&nb[b][i]&nb[c][i]
        );
    }

    return res;
}

void solve(){
    n=read();
    m=read();
    s=read();
    t=read();

    cntg=1;

    for(int i=1;i<=n;i++){
        head[i]=0;
    }

    // n<=500，每 64 个点压入一个 unsigned long long
    int W=(n+63)>>6;

    /*
        初始化每个点的闭邻域。
        闭邻域包含点自身，所以先把自己加入。
    */
    for(int i=1;i<=n;i++){
        for(int j=0;j<W;j++){
            nb[i][j]=0;
        }

        nb[i][(i-1)>>6]|=1ULL<<((i-1)&63);
    }

    for(int i=1;i<=m;i++){
        int u=read();
        int v=read();

        addedge(u,v);
        addedge(v,u);

        // 相邻点互相属于对方的闭邻域
        nb[u][(v-1)>>6]|=1ULL<<((v-1)&63);
        nb[v][(u-1)>>6]|=1ULL<<((u-1)&63);
    }

    bfs(s,ds);
    bfs(t,dt);

    int D=ds[t];

    // 预处理每个点闭邻域的大小
    for(int i=1;i<=n;i++){
        nbsz[i]=0;

        for(int j=0;j<W;j++){
            nbsz[i]+=__builtin_popcountll(nb[i][j]);
        }
    }

    // 预处理任意两个点闭邻域的交集大小
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){
            int res=0;

            for(int k=0;k<W;k++){
                res+=__builtin_popcountll(nb[i][k]&nb[j][k]);
            }

            inter[i][j]=inter[j][i]=res;
        }
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            dp[i][j]=INF;
            ways[i][j]=0;
        }
    }

    /*
        一个点 u 能出现在某条 s->t 最短路上，当且仅当：

        ds[u] + dt[u] = D
    */

    /*
        初始化最短路的第一条边 s -> v。

        当前覆盖：
        N[s] ∪ N[v]
    */
    for(int i=head[s];i;i=nxt[i]){
        int v=to[i];

        if(ds[v]!=1){
            continue;
        }

        if(ds[v]+dt[v]!=D){
            continue;
        }

        dp[s][v]=nbsz[s]+nbsz[v]-inter[s][v];
        ways[s][v]=1;
    }

    /*
        沿最短路分层 DP。

        当前：
            ... -> a -> u

        加入：
            ... -> a -> u -> v

        因为路径是最短路，N[v] 只可能和前两个路径点
        N[u]、N[a] 发生重复，不可能和更早的点发生重复。

        所以 v 的新增贡献为：

        |N[v]|
        - |N[v] ∩ N[u]|
        - |N[v] ∩ N[a]|
        + |N[v] ∩ N[u] ∩ N[a]|
    */
    for(int d=2;d<=D;d++){

        // u 位于最短路的第 d-1 层
        for(int u=1;u<=n;u++){
            if(ds[u]!=d-1){
                continue;
            }

            if(ds[u]+dt[u]!=D){
                continue;
            }

            // 枚举 u 的前驱 a
            for(int ia=head[u];ia;ia=nxt[ia]){
                int a=to[ia];

                if(ds[a]!=d-2){
                    continue;
                }

                if(ds[a]+dt[a]!=D){
                    continue;
                }

                if(dp[a][u]==INF){
                    continue;
                }

                // 枚举 u 的后继 v
                for(int iv=head[u];iv;iv=nxt[iv]){
                    int v=to[iv];

                    if(ds[v]!=d){
                        continue;
                    }

                    if(ds[v]+dt[v]!=D){
                        continue;
                    }

                    int add=
                        nbsz[v]
                        -inter[u][v]
                        -inter[a][v]
                        +get3(a,u,v,W);

                    int ndp=dp[a][u]+add;

                    if(ndp<dp[u][v]){
                        dp[u][v]=ndp;
                        ways[u][v]=ways[a][u];
                    }
                    else if(ndp==dp[u][v]){
                        ways[u][v]+=ways[a][u];

                        if(ways[u][v]>=MOD){
                            ways[u][v]-=MOD;
                        }
                    }
                }
            }
        }
    }

    int ans=INF;
    int cnt=0;

    /*
        D=1 时路径只有 s->t，
        不会进入上面的三点 DP，需要单独处理。
    */
    if(D==1){
        ans=nbsz[s]+nbsz[t]-inter[s][t];
        cnt=1;
    }
    else{
        // 枚举 t 在最短路上的所有前驱，合并最终答案
        for(int i=head[t];i;i=nxt[i]){
            int u=to[i];

            if(ds[u]!=D-1){
                continue;
            }

            if(ds[u]+dt[u]!=D){
                continue;
            }

            if(dp[u][t]<ans){
                ans=dp[u][t];
                cnt=ways[u][t];
            }
            else if(dp[u][t]==ans){
                cnt+=ways[u][t];

                if(cnt>=MOD){
                    cnt-=MOD;
                }
            }
        }
    }

    printf("%d %d\n",ans,cnt);
}

int main(){
    T=read();

    while(T--){
        solve();
    }

    return 0;
}