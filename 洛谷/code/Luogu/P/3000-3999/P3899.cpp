#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 3e5+5;
const int MAXT = MAXN*40;

int n,m,len;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cntg=1;

int dep[MAXN];

int dfncnt;
int dfn[MAXN];
int seg[MAXN];
int sz[MAXN];

int root[MAXN];
int ls[MAXT];
int rs[MAXT];
int sum[MAXT];
int cnt;

void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

void dfs(int u,int fa){
    dep[u]=dep[fa]+1;
    dfn[u]=++dfncnt;
    seg[dfncnt]=u;
    sz[u]=1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa){
            dfs(v,u);
            sz[u]+=sz[v];
        }
    }
}

int build(int l,int r){
    int rt=++cnt;
    if(l<r){
        int mid=(l+r)>>1;
        ls[rt]=build(l,mid);
        rs[rt]=build(mid+1,r);
    }
    return rt;
}

int insert(int jobv,int val,int l,int r,int i){
    int rt=++cnt;
    sum[rt]=sum[i];
    ls[rt]=ls[i];
    rs[rt]=rs[i];

    if(l==r){
        sum[rt]+=val;
    }
    else{
        int mid=(l+r)>>1;
        if(jobv<=mid){
            ls[rt]=insert(jobv,val,l,mid,ls[rt]);
        }
        else{
            rs[rt]=insert(jobv,val,mid+1,r,rs[rt]);
        }
        sum[rt]=sum[ls[rt]]+sum[rs[rt]];
    }
    return rt;
}

void prepare(){
    dfs(1,0);
    for(int i=1;i<=n;i++){
        len=max(len,dep[i]);
    }
    
    root[0]=build(1,len);
    for(int i=1;i<=n;i++){
        root[i]=insert(dep[seg[i]],sz[seg[i]]-1,1,len,root[i-1]);
    }
}

int query(int jobl,int jobr,int l,int r,int v,int u){
    if(jobl<=l&&r<=jobr){
        return sum[u]-sum[v];
    }
    else{
        int mid=(l+r)>>1;
        int ans=0;
        if(jobl<=mid){
            ans+=query(jobl,jobr,l,mid,ls[v],ls[u]);
        }
        if(jobr>mid){
            ans+=query(jobl,jobr,mid+1,r,rs[v],rs[u]);
        }
        return ans;
    }
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
    }

    prepare();

    for(int i=1;i<=m;i++){
        int u,k;
        cin>>u>>k;

        int ans1=(sz[u]-1)*min(dep[u]-1,k);
        int ans2=query(dep[u]+1,min(len,dep[u]+k),1,len,root[dfn[u]-1],root[dfn[u]+sz[u]-1]);
        cout<<(ans1+ans2)<<endl;
    }
    return 0;
}