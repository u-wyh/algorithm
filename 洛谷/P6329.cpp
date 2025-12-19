#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXT = MAXN*100;

int n,m;
int val[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cntg=1;

int fa[MAXN];
int sz[MAXN];
int top[MAXN];
int dep[MAXN];
int son[MAXN];

bool vis[MAXN];
int centfa[MAXN];

int addroot[MAXN];
int minusroot[MAXN];
int ls[MAXT];
int rs[MAXT];
int tree[MAXT];
int cntt;

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

void dfs1(int u,int f){
    dep[u]=dep[f]+1;
    fa[u]=f;
    sz[u]=1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=f){
            dfs1(v,u);
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
    return dep[a]+dep[b]-(dep[getlca(a,b)]<<1);
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
            centroidtree(getcentroid(v,u),u);
        }
    }
}

int add(int pos,int jobv,int l,int r,int i){
    if(i==0){
        i=++cntt;
    }
    if(l==r){
        tree[i]+=jobv;
    }
    else{
        int mid=(l+r)>>1;
        if(pos<=mid){
            ls[i]=add(pos,jobv,l,mid,ls[i]);
        }
        else{
            rs[i]=add(pos,jobv,mid+1,r,rs[i]);
        }
        tree[i]=tree[ls[i]]+tree[rs[i]];
    }
    return i;
}

int query(int jobl,int jobr,int l,int r,int i){
    if(i==0){
        return 0;
    }
    if(jobl<=l&&r<=jobr){
        return tree[i];
    }
    else{
        int mid=(l+r)>>1;
        int ans=0;
        if(jobl<=mid){
            ans+=query(jobl,jobr,l,mid,ls[i]);
        }
        if(jobr>mid){
            ans+=query(jobl,jobr,mid+1,r,rs[i]);
        }
        return ans;
    }
}

void add(int x,int v){
    addroot[x]=add(0,v,0,n-1,addroot[x]);
    for(int cur=x,fa=centfa[cur];fa;cur=fa,fa=centfa[cur]){
        int dist=getdist(x,fa);
        addroot[fa]=add(dist,v,0,n-1,addroot[fa]);
        minusroot[cur]=add(dist,v,0,n-1,minusroot[cur]);
    }
}

int query(int x,int k){
    int ans=query(0,k,0,n-1,addroot[x]);
    for(int cur=x,fa=centfa[cur];fa;cur=fa,fa=centfa[cur]){
        int dist=getdist(x,fa);
        if(k>=dist){
            ans+=query(0,k-dist,0,n-1,addroot[fa]);
            ans-=query(0,k-dist,0,n-1,minusroot[cur]);
        }
    }
    return ans;
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
    dfs2(1,1);
    centroidtree(getcentroid(1,0),0);
    for(int i=1;i<=n;i++){
        add(i,val[i]);
    }
    int ans=0;
    for(int i=1;i<=m;i++){
        int op,x,y;
        op=read(),x=read(),y=read();
        x^=ans;
        y^=ans;
        if(op==0){
            ans=query(x,y);
            cout<<ans<<endl;
        }
        else{
            add(x,y-val[x]);
            val[x]=y;
        }
    }
    return 0;
}