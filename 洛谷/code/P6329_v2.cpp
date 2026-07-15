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

int sz[MAXN];
bool vis[MAXN];

int fa[MAXN];
int siz[MAXN];
int son[MAXN];
int dep[MAXN];
int top[MAXN];

int centfa[MAXN];
int addtree[MAXN];
int minustree[MAXN];
int ls[MAXT];
int rs[MAXT];
int sum[MAXT];
int cntt;

void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

void getsize(int u,int fa){
    sz[u]=1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(!vis[v]&&v!=fa){
            getsize(v,u);
            sz[u]+=sz[v];
        }
    }
}

int getcentroid(int u,int fa){
    getsize(u,fa);
    int half=sz[u]>>1;
    bool flag=false;
    while(!flag){
        flag=true;
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(v!=fa&&!vis[v]&&sz[v]>half){
                flag=false;
                fa=u;
                u=v;
                break;
            }
        }
    }
    return u;
}

void dfs1(int u,int f){
    siz[u]=1;
    dep[u]=dep[f]+1;
    fa[u]=f;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=f){
            dfs1(v,u);
            siz[u]+=siz[v];
            if(siz[v]>siz[son[u]]){
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
        if(v!=son[u]&&v!=fa[u]){
            dfs2(v,v);
        }
    }
}

int getlca(int x,int y){
    while(top[x]!=top[y]){
        if(dep[top[x]]>=dep[top[y]]){
            x=fa[top[x]];
        }
        else{
            y=fa[top[y]];
        }
    }
    return (dep[x]<dep[y])?x:y;
}

int getdist(int x,int y){
    return dep[x]+dep[y]-2*dep[getlca(x,y)];
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
        sum[i]+=jobv;
    }
    else{
        int mid=(l+r)>>1;
        if(pos<=mid){
            ls[i]=add(pos,jobv,l,mid,ls[i]);
        }
        if(pos>mid){
            rs[i]=add(pos,jobv,mid+1,r,rs[i]);
        }
        sum[i]=sum[ls[i]]+sum[rs[i]];
    }
    return i;
}

int query(int jobl,int jobr,int l,int r,int i){
    if(i==0){
        return 0;
    }
    if(jobl<=l&&r<=jobr){
        return sum[i];
    }
    else{
        int ans=0;
        int mid=(l+r)>>1;
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
    addtree[x]=add(0,v,0,n-1,addtree[x]);
    for(int cur=x,fa=centfa[x];fa>0;cur=fa,fa=centfa[cur]){
        int dis=getdist(x,fa);
        addtree[fa]=add(dis,v,0,n-1,addtree[fa]);
        minustree[cur]=add(dis,v,0,n-1,minustree[cur]);
    }
}

int query(int x,int k){
    int ans=query(0,k,0,n-1,addtree[x]);
    for(int cur=x,fa=centfa[x];fa>0;cur=fa,fa=centfa[cur]){
        int dis=getdist(x,fa);
        if(k<dis){
            continue;
        }
        ans+=query(0,k-dis,0,n-1,addtree[fa]);
        ans-=query(0,k-dis,0,n-1,minustree[cur]);
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>val[i];
    }
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
    }

    dfs1(1,0);
    dfs2(1,1);
    centroidtree(getcentroid(1,0),0);

    for(int i=1;i<=n;i++){
        add(i,val[i]);
    }

    int lastans=0;
    for(int i=1;i<=m;i++){
        int op,x,y;
        cin>>op>>x>>y;
        x^=lastans;
        y^=lastans;
        if(op==0){
            lastans=query(x,y);
            cout<<lastans<<endl;
        }
        else{
            add(x,y-val[x]);
            val[x]=y;
        }
    }
    return 0;
}