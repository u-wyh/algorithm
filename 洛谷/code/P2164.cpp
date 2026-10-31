// https://www.luogu.com.cn/problem/P2164
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 305;
const int MAXM = MAXN*MAXN;

int n,m;

int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int id[MAXM];
int cntg=1;

int c[MAXN][MAXN];

int dis[MAXN];
int q[MAXN];
long long cnt[MAXN];

long double dp[MAXN];
long double ans[MAXM];

void addedge(int u,int v,int i){
    nxt[cntg]=head[u];
    to[cntg]=v;
    id[cntg]=i;
    head[u]=cntg++;
}

void solve(int s){
    int ql=1,qr=1;
    for(int i=1;i<=n;i++){
        dis[i]=-1;
        cnt[i]=0;
        dp[i]=0;
    }
    dis[s]=0;
    cnt[s]=1;
    q[ql]=s;

    while(ql<=qr){
        int u=q[ql++];
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(dis[v]==-1){
                dis[v]=dis[u]+1;
                q[++qr]=v;
            }
            if(dis[v]==dis[u]+1){
                cnt[v]+=cnt[u];
            }
        }
    }

    for(int k=qr;k>=1;k--){
        int v=q[k];
        for(int i=head[v];i;i=nxt[i]){
            int u=to[i];
            if(dis[u]!=dis[v]-1){
                continue;
            }
            long double val=(c[s][v]+dp[v])*(long double)cnt[u]/cnt[v];
            ans[id[i]]+=val;
            dp[u]+=val;
        }
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        addedge(u,v,i);
        addedge(v,u,i);
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>c[i][j];
        }
    }

    for(int i=1;i<=n;i++){
        solve(i);
    }

    cout<<fixed<<setprecision(3);
    for(int i=1;i<=m;i++){
        cout<<ans[i]<<"\n";
    }
    return 0;
}