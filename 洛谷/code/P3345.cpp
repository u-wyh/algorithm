#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int cent[MAXN<<1];
int cntg=1;

int fa[MAXN];
int sz[MAXN];
int top[MAXN];
int dep[MAXN];
int son[MAXN];
int dist[MAXN];

bool vis[MAXN];
int centfa[MAXN];

long long sum[MAXN];
long long addval[MAXN];
long long minusval[MAXN];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

inline void addedge(int u,int v,int w){
    nxt[cntg]=head[u];
    to[cntg]=v;
    weight[cntg]=w;
    head[u]=cntg++;
}

void dfs1(int u,int f,int dis){
    dep[u]=dep[f]+1;
    dist[u]=dis;
    fa[u]=f;
    sz[u]=1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        int w=weight[i];
        if(v!=f){
            dfs1(v,u,dis+w);
            sz[u]+=sz[v];
            if(sz[son[u]]<sz[v]){
                son[u]=v;
            }
        }
    }
}

void dfs2(int u,int t){
    top[u]=t;
    if(son[u]){
        dfs2(son[u],t);
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa[u]&&v!=son[u]){
            dfs2(v,v);
        }
    }
}

int getlca(int a,int b){
    while(top[a]!=top[b]){
        if(dep[top[a]]<dep[top[b]]){
            b=fa[top[b]];
        }
        else{
            a=fa[top[a]];
        }
    }
    return dep[a]<dep[b]?a:b;
}

int getdist(int a,int b){
    return dist[a]+dist[b]-(dist[getlca(a,b)]<<1);
}

void getsize(int u,int fa){
    sz[u]=1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa&&!vis[v]){
            getsize(v,u);
            sz[u]+=sz[v];
        }
    }
}

int getcentroid(int u,int fa){
    getsize(u,fa);
    int half=sz[u]>>1;
    bool find=false;
    while(!find){
        find=true;
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(v!=fa&&!vis[v]&&sz[v]>half){
                find=false;
                fa=u;
                u=v;
                break;
            }
        }
    }
    return u;
}

void centroidtree(int u,int fa){
    centfa[u]=fa;
    vis[u]=true;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(!vis[v]){
            int nxtcent=getcentroid(v,u);
            cent[i]=nxtcent;
            centroidtree(nxtcent,u);
        }
    }
}

void add(int x,int v){
    sum[x]+=v;
    for(int cur=x,fa=centfa[cur];fa;cur=fa,fa=centfa[cur]){
        int dist=getdist(x,fa);
        sum[fa]+=v;
        addval[fa]+=1ll*v*dist;
        minusval[cur]+=1ll*v*dist;
    }
}

long long query(int x){
    long long ans=addval[x];
    for(int cur=x,fa=centfa[cur];fa;cur=fa,fa=centfa[cur]){
        int dist=getdist(x,fa);
        ans+=addval[fa];
        ans-=minusval[cur];
        ans+=(sum[fa]-sum[cur])*dist;
    }
    return ans;
}

long long compute(int u){
    long long ans=query(u);
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(query(v)<ans){
            return compute(cent[i]);
        }
    }
    return ans;
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<n;i++){
        int u,v,w;
        u=read(),v=read(),w=read();
        addedge(u,v,w);
        addedge(v,u,w);
    }
    dfs1(1,0,0);
    dfs2(1,1);
    int root=getcentroid(1,0);
    centroidtree(root,0);
    for(int i=1;i<=m;i++){
        int x,v;
        x=read(),v=read();
        add(x,v);
        cout<<compute(root)<<endl;
    }
    return 0;
}