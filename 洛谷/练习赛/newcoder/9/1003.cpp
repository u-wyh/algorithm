#include<bits/stdc++.h>
using namespace std;
const int MAXN = 505;
const int MAXM = 500005;
const int INF = 1e9+7;
const int MOD = 998244353;

int n,m,s,t;

int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int cntg=1;

int ds[MAXN];
int dt[MAXN];

bitset<MAXN>neighbor[MAXN];
int nbsz[MAXN];
int two[MAXN][MAXN];

int dp[MAXN][MAXN];
int cnt[MAXN][MAXN];

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

void init(){
    for(int i=1;i<=n;i++){
        head[i]=0;
        neighbor[i].reset();
        neighbor[i][i]=1;
    }
    cntg=1;
}

int q[MAXN];
void bfs(int s,int *dis){
    for(int i=1;i<=n;i++){
        dis[i]=-1;
    }
    int l=1,r=0;
    q[++r]=s;
    dis[s]=0;
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

inline int get3(int a,int b,int c){
    return (neighbor[a]&neighbor[b]&neighbor[c]).count();
}

int main()
{
    int T=read();
    while(T--){
        cin>>n>>m>>s>>t;
        init();
        for(int i=1;i<=m;i++){
            int u,v;
            cin>>u>>v;
            addedge(u,v);
            addedge(v,u);
            neighbor[u][v]=1;
            neighbor[v][u]=1;
        }

        bfs(s,ds);
        bfs(t,dt);

        int dis=ds[t];
        for(int i=1;i<=n;i++){
            nbsz[i]=neighbor[i].count();
        }

        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                two[i][j]=two[j][i]=(neighbor[i]&neighbor[j]).count();
            }
        }

        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                dp[i][j]=INF;
                cnt[i][j]=0;
            }
        }

        for(int i=head[s];i;i=nxt[i]){
            int v=to[i];
            if(ds[v]+dt[v]!=dis){
                continue;
            }
            dp[s][v]=nbsz[s]+nbsz[v]-two[s][v];
            cnt[s][v]=1;
        }

        for(int d=2;d<=dis;d++){
            for(int u=1;u<=n;u++){
                if(ds[u]!=d-1){
                    continue;
                }

                if(ds[u]+dt[u]!=dis){
                    continue;
                }

                for(int i=head[u];i;i=nxt[i]){
                    int a=to[i];

                    if(ds[a]!=d-2){
                        continue;
                    }

                    if(ds[a]+dt[a]!=dis){
                        continue;
                    }

                    for(int e=head[u];e;e=nxt[e]){
                        int v=to[e];
                        if(ds[v]!=d){
                            continue;
                        }

                        if(ds[v]+dt[v]!=dis){
                            continue;
                        }

                        int add=nbsz[v]-two[u][v]-two[a][v]+get3(a,u,v);

                        int ndp=dp[a][u]+add;
                        if(ndp<dp[u][v]){
                            dp[u][v]=ndp;
                            cnt[u][v]=cnt[a][u];
                        }
                        else if(ndp==dp[u][v]){
                            cnt[u][v]+=cnt[a][u];
                            cnt[u][v]%=MOD;
                        }
                    }
                }
            }
        }

        int ans=INF;
        int anscnt=0;

        for(int i=head[t];i;i=nxt[i]){
            int u=to[i];
            if(ds[u]!=dis-1){
                continue;
            }
            if(ds[u]+dt[u]!=dis){
                continue;
            }

            if(dp[u][t]<ans){
                ans=dp[u][t];
                anscnt=cnt[u][t];
            }
            else if(dp[u][t]==ans){
                anscnt+=cnt[u][t];
                anscnt%=MOD;
            }
        }

        cout<<ans<<' '<<anscnt<<endl;
    }
    return 0;
}