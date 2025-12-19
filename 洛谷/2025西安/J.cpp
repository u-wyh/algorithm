#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int MAXN = 3e5+5;
const int MAXH = 22;
const int INF = 1e18;

int n,cases,p;
int ans;
int val[MAXN];

int mincost[MAXN];
// int minson1[MAXN];
int nodeson1[MAXN];
// int minson2[MAXN];
int nodeson2[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

int dep[MAXN];
int st[MAXN][MAXH];

int son[MAXN];
int sz[MAXN];
int top[MAXN];
int dp[MAXN];

inline void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

int lca(int a,int b){
    if(dep[a]<dep[b]){
        swap(a,b);
    }
    for(int i=p;i>=0;i--){
        if(dep[st[a][i]]>=dep[b]){
            a=st[a][i];
        }
    }
    if(a==b){
        return a;
    }
    for(int i=p;i>=1;i--){
        if(st[a][i]!=st[b][i]){
            a=st[a][i];
            b=st[b][i];
        }
    }
    return st[a][0];
}

void init(){
    cnt=1;
    for(int i=1;i<=n;i++){
        head[i]=0;
        son[i]=0;
        nodeson1[i]=0;
        nodeson2[i]=0;
        dp[i]=0;
    }
    mincost[0]=INF;
}

void dfs1(int u,int fa){
    mincost[u]=val[u];
    dep[u]=dep[fa]+1;
    st[u][0]=fa;
    sz[u]=1;
    for(int i=1;i<=p;i++){
        st[u][i]=st[st[u][i-1]][i-1];
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa){
            dfs1(v,u);
            sz[u]+=sz[v];
            if(sz[son[u]]<sz[v]){
                son[u]=v;
            }
            if(mincost[v]<=mincost[nodeson1[u]]){
                nodeson2[u]=nodeson1[u];
                nodeson1[u]=v;
            }
            else if(mincost[v]<mincost[nodeson2[u]]){
                nodeson2[u]=v;
            }
        }
    }
    mincost[u]=min(val[u],mincost[nodeson1[u]]+mincost[nodeson2[u]]);
}

void dfs2(int u,int t){
    top[u]=t;
    if(son[u]){
        int cost=0;
        if(nodeson1[u]!=son[u]){
            cost=mincost[nodeson1[u]];
        }
        else{
            cost=mincost[nodeson2[u]];
        }
        dp[son[u]]=dp[u]+cost;
        dfs2(son[u],t);
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=st[u][0]&&v!=son[u]){
            dfs2(v,v);
        }
    }
}

void fun(int x,int y){
    if(nodeson1[x]!=y){
        ans+=mincost[nodeson1[x]];
    }
    else{
        ans+=mincost[nodeson2[x]];
    }
}

void compute(int x,int y){
    fun(st[x][0],x);
    x=st[x][0];
    while(top[x]!=top[y]){
        ans+=(dp[x]-dp[top[x]]);
        fun(st[top[x]][0],top[x]);
        x=st[top[x]][0];
    }
    ans+=dp[x]-dp[y];
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin>>T;
    while(T--){
        cin>>n>>cases;
        p=log2(n)+1;
        init();
        for(int i=1;i<=n;i++){
            cin>>val[i];
        }
        for(int i=1;i<n;i++){
            int u,v;
            cin>>u>>v;
            addedge(u,v);
            addedge(v,u);
        }
        dfs1(1,0);
        dfs2(1,1);
        while(cases--){
            int x,y;
            cin>>x>>y;
            if(lca(x,y)!=y){
                cout<<-1<<endl;
                continue;
            }
            else if(x==y){
                cout<<0<<endl;
            }
            else{
                ans=0;
                compute(x,y);
                cout<<ans<<endl;
            }
        }
    }
    return 0;
}