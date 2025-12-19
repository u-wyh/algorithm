#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXT = MAXN*200;
const int MAXH = 18;

int n,m;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cntg=1;

int dep[MAXN];
int st[MAXN][MAXH];

bool vis[MAXN];
int centfa[MAXN];
int sz[MAXN];

int addroot[MAXN];
int minusroot[MAXN];
int ls[MAXT];
int rs[MAXT];
int tree[MAXT];
int cntt;

inline void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

void dfs(int u,int fa){
    dep[u]=dep[fa]+1;
    st[u][0]=fa;
    for(int p=1;p<MAXH;p++){
        st[u][p]=st[st[u][p-1]][p-1];
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa){
            dfs(v,u);
        }
    }
}

int getlca(int a,int b){
    if(dep[a]<dep[b]){
        swap(a,b);
    }
    for(int p=MAXH-1;p>=0;p--){
        if(dep[st[a][p]]>=dep[b]){
            a=st[a][p];
        }
    }
    if(a==b){
        return a;
    }
    for(int p=MAXH-1;p>=0;p--){
        if(st[a][p]!=st[b][p]){
            a=st[a][p];
            b=st[b][p];
        }
    }
    return st[a][0];
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

void add(int x,int k,int v){
    addroot[x]=add(k,v,0,n-1,addroot[x]);
    for(int cur=x,fa=centfa[cur];fa;cur=fa,fa=centfa[cur]){
        int dist=getdist(x,fa);
        if(k>=dist){
            addroot[fa]=add(k-dist,v,0,n-1,addroot[fa]);
            minusroot[cur]=add(k-dist,v,0,n-1,minusroot[cur]);
        }
    }
}

int query(int x){
    int ans=query(0,n-1,0,n-1,addroot[x]);
    for(int cur=x,fa=centfa[cur];fa;cur=fa,fa=centfa[cur]){
        int dist=getdist(x,fa);
        ans+=query(dist,n-1,0,n-1,addroot[fa]);
        ans-=query(dist,n-1,0,n-1,minusroot[cur]);
    }
    return ans;
}

int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<n;i++){
        int u,v;
        scanf("%d %d",&u,&v);
        addedge(u,v);
        addedge(v,u);
    }
    dfs(1,0);
    centroidtree(getcentroid(1,0),0);
    for(int i=1;i<=m;i++){
        char op;
        int x,k,v;
        scanf(" %c %d",&op,&x);
        if(op=='M'){
            scanf("%d %d",&k,&v);
            add(x,k,v);
        }
        else{
            cout<<query(x)<<endl;
        }
    }
    return 0;
}