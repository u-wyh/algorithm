#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;

int n,m;

int val[MAXN];

bool vis[MAXN][26];
int ans[MAXN];

// Ê÷Á´ÆÊ·Ö
int fa[MAXN];
int sz[MAXN];
int dep[MAXN];
int son[MAXN];
int maxdep[MAXN];

int cnt=1;
int head[MAXN];
int nxt[MAXN];
int to[MAXN];

int cntq=1;
int headq[MAXN];
int nxtq[MAXN];
int toq[MAXN];
int idq[MAXN];

bool ok[MAXN];

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

inline void addEdge(int u,int v,int id){
    nxtq[cntq]=headq[u];
    toq[cntq]=v;
    idq[cntq]=id;
    headq[u]=cntq++;
}

void dfs1(int u,int f){
    fa[u]=f;
    sz[u]=1;
    maxdep[u]=dep[u]=dep[f]+1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs1(v,u);
        maxdep[u]=max(maxdep[u],maxdep[v]);
        sz[u]+=sz[v];
        if(son[u]==0||sz[v]>sz[son[u]]){
            son[u]=v;
        }
    }
}

void effect(int u){
    vis[dep[u]][val[u]]^=1;
    if(vis[dep[u]][val[u]]){
        ans[dep[u]]++;
    }
    else{
        ans[dep[u]]--;
    }
    for(int i=head[u];i;i=nxt[i]){
        effect(to[i]);
    }
}

void cancel(int u){
    vis[dep[u]][val[u]]^=1;
    if(vis[dep[u]][val[u]]){
        ans[dep[u]]++;
    }
    else{
        ans[dep[u]]--;
    }
    for(int i=head[u];i;i=nxt[i]){
        cancel(to[i]);
    }
}

void dfs2(int u,int keep){
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=son[u]){
            dfs2(v,0);
        }
    }
    if(son[u]!=0){
        dfs2(son[u],1);
    }
    vis[dep[u]][val[u]]^=1;
    if(vis[dep[u]][val[u]]){
        ans[dep[u]]++;
    }
    else{
        ans[dep[u]]--;
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=son[u]){
            effect(v);
        }
    }
    for(int i=headq[u];i;i=nxtq[i]){
        if(toq[i]>maxdep[u]){
            ok[idq[i]]=true;
            continue;
        }
        ok[idq[i]]=(ans[toq[i]]<=1)?true:false;
    }
    if(keep==0){
        cancel(u);
    }
}

int main()
{
    n=read(),m=read();
    for(int i=2;i<=n;i++){
        int u;
        u=read();
        addedge(u,i);
    }
    for(int i=1;i<=n;i++){
        char c;
        scanf("%c",&c);
        val[i]=c-'a';
    }
    dfs1(1,0);
    for(int i=1;i<=m;i++){
        int u,v;
        u=read(),v=read();
        addEdge(u,v,i);
    }
    dfs2(1,1);
    for(int i=1;i<=m;i++){
        if(ok[i]){
            printf("Yes\n");
        }
        else{
            printf("No\n");
        }
    }
    return 0;
}