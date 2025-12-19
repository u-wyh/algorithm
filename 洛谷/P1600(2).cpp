#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5+5;
const int delta = 3e5;
const int MAXH = 22;

int n,m;
int val[MAXN];
int ans[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cntg=1;

int headq[MAXN];
int nxtq[MAXN<<2];
int toq[MAXN<<2];
int opq[MAXN<<2];
int valq[MAXN<<2];
int cntq=1;

int dep[MAXN];
int st[MAXN][MAXH];

int bucket1[MAXN<<1];
int bucket2[MAXN<<1];

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
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

inline void addEdge(int u,int v,int op,int w){
    nxtq[cntq]=headq[u];
    toq[cntq]=v;
    opq[cntq]=op;
    valq[cntq]=w;
    headq[u]=cntq++;
}

inline int lca(int a,int b){
    if(dep[a]<dep[b]) swap(a,b);
    for(int i=MAXH-1;i>=0;i--){
        if(dep[st[a][i]]>=dep[b]){
            a=st[a][i];
        }
    }
    if(a==b) return a;
    for(int i=MAXH-1;i>=0;i--){
        if(st[a][i]!=st[b][i]){
            a=st[a][i];
            b=st[b][i];
        }
    }
    return st[a][0];
}

void dfs1(int u,int fa){
    dep[u]=dep[fa]+1;
    st[u][0]=fa;
    for(int i=1;i<MAXH;i++){
        st[u][i]=st[st[u][i-1]][i-1];
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa){
            dfs1(v,u);
        }
    }
}

void dfs2(int u,int fa){
    ans[u]-=bucket1[val[u]+dep[u]]+bucket2[val[u]-dep[u]+delta];

    for(int i=headq[u];i;i=nxtq[i]){
        int v=toq[i];
        int val=valq[i];
        int op=opq[i];
        if(op==1){
            bucket1[v]+=val;
        }
        if(op==2){
            bucket2[v]+=val;
        }
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa){
            dfs2(v,u);
        }
    }
    ans[u]+=bucket1[val[u]+dep[u]]+bucket2[val[u]-dep[u]+delta];
    return ;
}

int main()
{
    n=read(),m=read();
    // p=log2(n)+1;
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    dfs1(1,0);
    for(int i=1;i<=m;i++){
        int s,t;
        s=read(),t=read();
        int fa=lca(s,t);
        
        addEdge(s,dep[s],1,1);
        addEdge(st[fa][0],dep[s],1,-1);

        int v=dep[s]+dep[t]-2*dep[fa]-dep[t]+delta;
        addEdge(t,v,2,1);
        addEdge(st[fa][0],v,2,-1);

        if(dep[fa]+val[fa]==dep[s]){
            ans[fa]--;
        }
    }
    dfs2(1,0);
    for(int i=1;i<=n;i++){
        printf("%d ",ans[i]);
    }
    return 0;
}