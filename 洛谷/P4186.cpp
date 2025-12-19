#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,ans;
int st;
int degree[MAXN];

int dep[MAXN];
int dis[MAXN];
int sz[MAXN];

int cnt=1;
int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];

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

inline void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void dfs(int u,int fa){
    dep[u]=dep[fa]+1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==fa){
            continue;
        }
        dfs(v,u);
        sz[u]+=sz[v];
        dis[u]=min(dis[u],dis[v]+1);
    }
}

void dfs2(int u,int fa){
    if(dep[u]>=dis[u]){
        ans-=(sz[u]-1);
        return ;
    }
    else{
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(v==fa){
                continue;
            }
            dfs2(v,u);
        }
    }
}

int main()
{
    n=read(),st=read();
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v),addedge(v,u);
        degree[u]++,degree[v]++;
    }
    if(degree[st]==1){
        cout<<1<<endl;
        return 0;
    }
    for(int i=1;i<=n;i++){
        dis[i]=n;
        if(degree[i]==1){
            ans++;
            dis[i]=0;
            sz[i]=1;
        }
    }
    dep[0]=-1;
    dfs(st,0);
    for(int i=head[st];i;i=nxt[i]){
        int v=to[i];
        dfs2(v,st);
    }
    cout<<ans<<endl;
    return 0;
}
