#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m;
int val[MAXN];

// Ê÷Á´ÆÊ·Ö
int fa[MAXN];
int sz[MAXN];
int son[MAXN];

int cnt=1;
int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];

int cntq=1;
int headq[MAXN];
int nxtq[MAXN];
int toq[MAXN];
int idq[MAXN];

int tot[MAXN];
int tree[MAXN];

int ans[MAXN];

inline int lowbit(int x){
    return x&(-x);
}

void add(int x,int val){
    // cout<<' '<<x<<' '<<val<<endl;
    if(x==0){
        return ;
    }
    while(x<=n){
        tree[x]+=val;
        x+=lowbit(x);
    }
}

int query(int x){
    int ans=0;
    while(x){
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}

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
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==f){
            continue;
        }
        dfs1(v,u);
        sz[u]+=sz[v];
        if(son[u]==0||sz[v]>sz[son[u]]){
            son[u]=v;
        }
    }
}

void effect(int u){
    tot[val[u]]++;
    add(tot[val[u]]-1,-1);
    add(tot[val[u]],1);
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa[u]){
            effect(v);
        }
    }
}

void cancel(int u){
    tot[val[u]]--;
    add(tot[val[u]]+1,-1);
    add(tot[val[u]],1);
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa[u]){
            cancel(v);
        }
    }
}

void dfs2(int u,int keep){
    // cout<<' '<<u<<' '<<keep<<endl;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=son[u]&&v!=fa[u]){
            dfs2(v,0);
        }
    }
    if(son[u]!=0){
        dfs2(son[u],1);
    }
    tot[val[u]]++;
    add(tot[val[u]]-1,-1);
    add(tot[val[u]],1);
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=son[u]&&v!=fa[u]){
            effect(v);
        }
    }
    for(int i=headq[u];i;i=nxtq[i]){
        if(toq[i]>sz[u]){
            ans[idq[i]]=0;
            continue;
        }
        ans[idq[i]]=query(n)-query(toq[i]-1);
    }
    if(keep==0){
        cancel(u);
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    dfs1(1,0);
    for(int i=1;i<=m;i++){
        int u,v;
        u=read(),v=read();
        addEdge(u,v,i);
    }
    dfs2(1,1);
    // cout<<666<<endl;
    for(int i=1;i<=m;i++){
        printf("%d\n",ans[i]);
    }
    return 0;
}