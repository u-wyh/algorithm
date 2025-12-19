#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5+5;
const int delta = 3e5;
const int MAXH = 22;

int n,m,p;
int val[MAXN];
int ans[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cntg=1;

int headq[MAXN];
int nxtq[MAXN<<1];
int toq[MAXN<<1];
int opq[MAXN<<1];
int cntq=1;

int son[MAXN];
int sz[MAXN];
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

inline void addEdge(int u,int v,int op){
    // cout<<u<<' '<<v<<' '<<op<<endl;
    nxtq[cntq]=headq[u];
    toq[cntq]=v;
    opq[cntq]=op;
    headq[u]=cntq++;
}

inline int lca(int a,int b){
    if(dep[a]<dep[b]) swap(a,b);
    for(int i=p;i>=0;i--){
        if(dep[st[a][i]]>=dep[b]){
            a=st[a][i];
        }
    }
    if(a==b) return a;
    for(int i=p;i>=0;i--){
        if(st[a][i]!=st[b][i]){
            a=st[a][i];
            b=st[b][i];
        }
    }
    return st[a][0];
}

void dfs1(int u,int fa){
    dep[u]=dep[fa]+1;
    sz[u]=1;
    st[u][0]=fa;
    for(int i=1;i<=p;i++){
        st[u][i]=st[st[u][i-1]][i-1];
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa){
            dfs1(v,u);
            sz[u]+=sz[v];
            if(son[u]==0||sz[son[u]]<sz[v]){
                son[u]=v;
            }
        }
    }
}

void effect(int u){
    for(int i=headq[u];i;i=nxtq[i]){
        int v=toq[i];
        int op=opq[i];
        if(op==1){
            bucket1[v]++;
        }
        else{
            bucket2[v]++;
        }
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=st[u][0]){
            effect(v);
        }
    }
}

void cancel(int u){
    for(int i=headq[u];i;i=nxtq[i]){
        int v=toq[i];
        int op=opq[i];
        if(op==1){
            bucket1[v]=0;
        }
        else{
            bucket2[v]=0;
        }
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=st[u][0]){
            cancel(v);
        }
    }
}

void dfs2(int u,int keep){
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=st[u][0]&&v!=son[u]){
            dfs2(v,0);
        }
    }
    if(son[u]){
        dfs2(son[u],1);
    }
    for(int i=headq[u];i;i=nxtq[i]){
        int v=toq[i];
        int op=opq[i];
        if(op==1){
            bucket1[v]++;
        }
        else{
            bucket2[v]++;
        }
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=st[u][0]&&v!=son[u]){
            effect(v);
        }
    }
    ans[u]+=bucket2[val[u]-dep[u]+delta]+bucket2[val[u]+dep[u]];
    if(keep==0){
        cancel(u);
    }
}

int main()
{
    n=read(),m=read();
    p=log2(n)+1;
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
        // cout<<s<<' '<<t<<' '<<fa<<endl;
        if(s!=fa){
            addEdge(s,dep[s],1);
        }
        if(t!=fa){
            int v=dep[s]+dep[t]-2*dep[fa]-dep[t]+delta;
            addEdge(t,v,2);
        }

        if(s==t){
            if(val[s]==0){
                ans[s]++;
            }
        }
    }
    dfs2(1,1);
    for(int i=1;i<=n;i++){
        printf("%d ",ans[i]);
    }
    return 0;
}