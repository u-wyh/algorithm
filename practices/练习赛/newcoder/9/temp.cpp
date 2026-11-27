#include<bits/stdc++.h>
using namespace std;

const int MAXN = 505;
const int MAXE = 250005;
const int INF = 0x3f3f3f3f;
const int MOD = 998244353;

int T;
int n,m,s,t;

int head[MAXN];
int nxt[MAXE];
int to[MAXE];
int cntg;

int ds[MAXN];
int dt[MAXN];
int q[MAXN];

// nb[u] 表示点 u 的闭邻域
bitset<MAXN> nb[MAXN];

int nbsz[MAXN];

// inter[u][v] = |N[u] ∩ N[v]|
int inter[MAXN][MAXN];

// dp[u][v] 表示最后两个点为 u,v 时的最小闭邻域大小
int dp[MAXN][MAXN];
int ways[MAXN][MAXN];

inline int read(){
    int x=0,f=1;
    char ch=getchar();

    while(ch<'0'||ch>'9'){
        if(ch=='-'){
            f=-1;
        }
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

// 计算三个闭邻域的交集大小
inline int get3(int a,int b,int c){
    return (nb[a]&nb[b]&nb[c]).count();
}

void solve(){
    n=read();
    m=read();
    s=read();
    t=read();

    cntg=1;

    for(int i=1;i<=n;i++){
        head[i]=0;
        nb[i].reset();
        nb[i][i]=1;
    }

    for(int i=1;i<=m;i++){
        int u=read();
        int v=read();

        addedge(u,v);
        addedge(v,u);

        nb[u][v]=1;
        nb[v][u]=1;
    }

    bfs(s,ds);
    bfs(t,dt);

    int D=ds[t];

    // 预处理每个点闭邻域大小
    for(int i=1;i<=n;i++){
        nbsz[i]=nb[i].count();
    }

    // 预处理两两闭邻域交集大小
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){
            inter[i][j]=inter[j][i]=(nb[i]&nb[j]).count();
        }
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            dp[i][j]=INF;
            ways[i][j]=0;
        }
    }

    // 初始化第一步 s -> v
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

    // 沿最短路分层进行 DP
    for(int d=2;d<=D;d++){
        for(int u=1;u<=n;u++){
            if(ds[u]!=d-1){
                continue;
            }

            if(ds[u]+dt[u]!=D){
                continue;
            }

            // 枚举前驱 a
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

                // 枚举后继 v
                for(int iv=head[u];iv;iv=nxt[iv]){
                    int v=to[iv];

                    if(ds[v]!=d){
                        continue;
                    }

                    if(ds[v]+dt[v]!=D){
                        continue;
                    }

                    // v 只可能和前两个路径点 a,u 的闭邻域产生重复
                    int add=
                        nbsz[v]
                        -inter[u][v]
                        -inter[a][v]
                        +get3(a,u,v);

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

    // 最短路只有一条边
    if(D==1){
        ans=nbsz[s]+nbsz[t]-inter[s][t];
        cnt=1;
    }
    else{
        // 枚举 t 的所有最短路前驱
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