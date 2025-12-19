#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e4+5;
const int MAXM = 1e6+5;
const int MAXQ = 4e4+5;

int n,m;
struct EDGE{
    int l,r;
    bool ok;
};
EDGE edge[MAXM];
map<pair<int,int>,int>mp;

int q;
int op[MAXQ];
int u[MAXQ];
int v[MAXQ];

int father[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cntg=1;

int son[MAXN];
int sz[MAXN];
int fa[MAXN];
int dep[MAXN];
int dfncnt;
int dfn[MAXN];
int top[MAXN];

int tree[MAXN<<2];
bool tag[MAXN<<2];

int ans[MAXN];

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

int find(int x){
    return x==father[x]?x:father[x]=find(father[x]);
}

inline void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

void dfs1(int u,int f){
    dep[u]=dep[f]+1;
    sz[u]=1;
    fa[u]=f;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==f){
            continue;
        }
        dfs1(v,u);
        sz[u]+=sz[v];
        if(son[u]==0||sz[son[u]]<sz[v]){
            son[u]=v;
        }
    }
}

void dfs2(int u,int t){
    top[u]=t;
    dfn[u]=++dfncnt;
    if(son[u]){
        dfs2(son[u],t);
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=son[u]&&v!=fa[u]){
            dfs2(v,v);
        }
    }
}

void build(int l,int r,int i){
    tree[i]=r-l+1;
    if(l==1){
        tree[i]--;
    }
    if(l<r){
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
    }
}

void up(int i){
    tree[i]=tree[i<<1]+tree[i<<1|1];
}

void lazy(int i){
    tag[i]=true;
    tree[i]=0;
}

void down(int i){
    if(tag[i]){
        lazy(i<<1);
        lazy(i<<1|1);
        tag[i]=true;
    }
}

void update(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        lazy(i);
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        if(jobl<=mid){
            update(jobl,jobr,l,mid,i<<1);
        }
        if(jobr>mid){
            update(jobl,jobr,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

void update(int x,int y){
    while(top[x]!=top[y]){
        if(dep[top[x]]<=dep[top[y]]){
            swap(x,y);
        }
        update(dfn[top[x]],dfn[x],1,n,1);
        x=fa[top[x]];
    }
    if(dep[x]<dep[y]){
        swap(x,y);
    }
    update(dfn[y]+1,dfn[x],1,n,1);
}

int query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return tree[i];
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        int ans=0;
        if(jobl<=mid){
            ans+=query(jobl,jobr,l,mid,i<<1);
        }
        if(jobr>mid){
            ans+=query(jobl,jobr,mid+1,r,i<<1|1);
        }
        return ans;
    }
}

int query(int x,int y){
    int ans=0;
    while(top[x]!=top[y]){
        if(dep[top[x]]<=dep[top[y]]){
            swap(x,y);
        }
        ans+=query(dfn[top[x]],dfn[x],1,n,1);
        x=fa[top[x]];
    }
    if(dep[x]<dep[y]){
        swap(x,y);
    }
    ans+=query(dfn[y]+1,dfn[x],1,n,1);
    return ans;
}

void prepare(){
    for(int i=1;i<=n;i++){
        father[i]=i;
    }
    for(int i=1;i<=m;i++){
        if(!edge[i].ok){
            int fx=find(edge[i].l);
            int fy=find(edge[i].r);
            if(fx!=fy){
                father[fx]=fy;
                addedge(edge[i].l,edge[i].r);
                addedge(edge[i].r,edge[i].l);
                edge[i].ok=true;
            }
        }
    }
    dfs1(1,0);
    dfs2(1,1);
    build(1,n,1);

    for(int i=1;i<=m;i++){
        if(!edge[i].ok){
            update(edge[i].l,edge[i].r);
        }
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=m;i++){
        int u,v;
        u=read(),v=read();
        if(u>v){
            swap(u,v);
        }
        edge[i]={u,v,false};
        mp[{u,v}]=i;
    }
    while(true){
        q++;
        op[q]=read();
        if(op[q]==-1){
            q--;
            break;
        }
        else{
            u[q]=read(),v[q]=read();
            if(op[q]==0){
                if(u[q]>v[q]){
                    swap(u[q],v[q]);
                }
                edge[mp[{u[q],v[q]}]].ok=true;
            }
        }
    }
    prepare();
    for(int i=q;i>=1;i--){
        if(op[i]==0){
            update(u[i],v[i]);
        }
        else{
            ans[i]=query(u[i],v[i]);
        }
    }
    for(int i=1;i<=q;i++){
        if(op[i]==1){
            printf("%d\n",ans[i]);
        }
    }
    return 0;
}