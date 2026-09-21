// https://www.luogu.com.cn/problem/P4096
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int INF = 1e6;

int n;

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cntg=1;

int dep[MAXN];
int f[MAXN];
int g[MAXN];

bool w[MAXN];
bool b[MAXN];

int ans[MAXN];
int len;

inline void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

void dfs(int u,int fa){
    if(head[u]==0){
        f[u]=g[u]=1;
        return ;
    }
    dep[u]=dep[fa]+1;
    if(dep[u]%2){
        f[u]=INF;
    }
    else{
        g[u]=INF;
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs(v,u);
        if(dep[u]%2==1){
            f[u]=min(f[u],f[v]);
            g[u]+=g[v];
        }
        else{
            f[u]+=f[v];
            g[u]=min(g[u],g[v]);
        }
    }
}

void dfs(int u,bool ok1,bool ok2){
    int d=dep[u];
    b[u]=ok1;
    w[u]=ok2;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(d%2){
            if(f[u]==f[v]){
                dfs(v,ok1,ok2);
            }
            else{
                dfs(v,0,ok2);
            }
        }
        else{
            if(g[u]==g[v]){
                dfs(v,ok1,ok2);
            }
            else{
                dfs(v,ok1,0);
            }
        }
    }
}

int main()
{
    cin>>n;
    for(int i=2;i<=n;i++){
        int u;
        cin>>u;
        addedge(u,i);
    }

    dfs(1,0);
    dfs(1,1,1);

    int val=0;
    for(int i=1;i<=n;i++){
        if(head[i]==0&&w[i]&&b[i]){
            ans[++len]=i;
            val^=i;
        }
    }
    cout<<ans[1]<<' '<<len<<' '<<val<<endl;
    return 0;
}