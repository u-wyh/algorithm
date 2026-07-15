#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+10;

int n,m;

int u[MAXN];
int v[MAXN];
int w[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cntg=1;

int dfncnt;
int dfn[MAXN];
int node1,node2,skipedge;

int fa[MAXN];
int son[MAXN];
int sz[MAXN];
int top[MAXN];
int dep[MAXN];

int tree[MAXN];

inline void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

void dfs1(int u){
    dfn[u]=++dfncnt;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(dfn[v]==0){
            dfs1(v);
        }
        else if(dfn[u]<dfn[v]) {
            node1=u;
            node2=v;
            skipedge=(i+1)>>1;
        }
    }
}

void dfs2(int u,int f){
    sz[u]=1;
    dep[u]=dep[f]+1;
    fa[u]=f;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=f&&skipedge!=((i+1)>>1)){
            dfs2(v,u);
            sz[u]+=sz[v];
            if(sz[v]>sz[son[u]]){
                son[u]=v;
            }
        }
    }
}

void dfs3(int u,int t){
    top[u]=t;
    dfn[u]=++dfncnt;
    if(son[u]){
        dfs3(son[u],t);
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa[u]&&v!=son[u]&&((i+1)>>1)!=skipedge){
            dfs3(v,v);
        }
    }
}

int lowbit(int x){
    return x&(-x);
}

void add(int x,int v){
    while(x<=n){
        tree[x]+=v;
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

int sum(int l,int r){
    if(l>r){
        return 0;
    }
    return query(r)-query(l-1);
}

void prepare(){
    dfs1(1);
    dfncnt=0;
    dfs2(1,0);
    dfs3(1,1);
    for(int i=1;i<=n;i++){
        if(i!=skipedge){
            add(max(dfn[u[i]],dfn[v[i]]),w[i]);
        }
    }
}

void setedge(int x,int y){
    if(x!=skipedge){
        add(max(dfn[u[x]],dfn[v[x]]),y-w[x]);
    }
    w[x]=y;
}

int compute(int x,int y){
    int ans=0;
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]]){
            swap(x,y);
        }
        ans+=sum(dfn[top[x]],dfn[x]);
        x=fa[top[x]];
    }
    ans+=sum(min(dfn[x],dfn[y])+1,max(dfn[x],dfn[y]));
    return ans;
}

int getdist(int x,int y){
    int ans1=compute(x,y);
    int ans2=compute(x,node1)+compute(y,node2)+w[skipedge];
    int ans3=compute(x,node2)+compute(y,node1)+w[skipedge];
    return min(ans1,min(ans2,ans3));
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>u[i]>>v[i]>>w[i];
        addedge(u[i],v[i]);
        addedge(v[i],u[i]);
    }

    prepare();

    for(int i=1;i<=m;i++){
        int op,x,y;
        cin>>op>>x>>y;
        if(op==1){
            setedge(x,y);
        }
        else{
            cout<<getdist(x,y)<<endl;
        }
    }
    return 0;
}