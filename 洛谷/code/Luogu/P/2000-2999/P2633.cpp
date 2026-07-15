#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXT = MAXN*40;
const int MAXH = 20;

int n,m,len,p;
int val[MAXN];
int sorted[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cntg=1;

int dep[MAXN];
int st[MAXN][MAXH];

int root[MAXN];
int ls[MAXT];
int rs[MAXT];
int sz[MAXT];
int cnt;

void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

int find(int val){
    int l=1,r=len,ans=1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(sorted[mid]>=val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

int insert(int val,int l,int r,int i){
    int rt=++cnt;
    ls[rt]=ls[i];
    rs[rt]=rs[i];
    sz[rt]=sz[i];

    if(l==r){
        sz[rt]++;
    }
    else{
        int mid=(l+r)>>1;
        if(val<=mid){
            ls[rt]=insert(val,l,mid,ls[rt]);
        }
        else{
            rs[rt]=insert(val,mid+1,r,rs[rt]);
        }
        sz[rt]=sz[ls[rt]]+sz[rs[rt]];
    }
    return rt;
}

void dfs(int u,int fa){
    root[u]=insert(find(val[u]),1,len,root[fa]);
    dep[u]=dep[fa]+1;
    st[u][0]=fa;
    for(int i=1;i<=p;i++){
        st[u][i]=st[st[u][i-1]][i-1];
    }

    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa){
            dfs(v,u);
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

void prepare(){
    for(int i=1;i<=n;i++){
        sorted[i]=val[i];
    }
    sort(sorted+1,sorted+n+1);
    len=1;
    for(int i=2;i<=n;i++){
        if(sorted[i]!=sorted[i-1]){
            sorted[++len]=sorted[i];
        }
    }

    root[0]=build(1,len);

    p=log2(n)+1;
    dfs(1,0);

}

int lca(int a,int b){
    if(dep[a]<=dep[b]){
        swap(a,b);
    }

    for(int i=p;i>=0;i--){
        if(dep[st[a][i]]>=dep[b]){
            a=st[a][i];
        }
    }
    if(a==b){
        return a;
    }

    for(int i=p;i>=0;i--){
        if(st[a][i]!=st[b][i]){
            a=st[a][i];
            b=st[b][i];
        }
    }
    return st[a][0];
}

int query(int jobk,int l,int r,int u,int v,int x,int y){
    if(l==r){
        return l;
    }
    else{
        int mid=(l+r)>>1;
        int lsz=sz[ls[u]]+sz[ls[v]]-sz[ls[x]]-sz[ls[y]];
        if(lsz>=jobk){
            return query(jobk,l,mid,ls[u],ls[v],ls[x],ls[y]);
        }
        else{
            return query(jobk-lsz,mid+1,r,rs[u],rs[v],rs[x],rs[y]);
        }
    }
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

    prepare();

    int lastans=0;
    for(int i=1;i<=m;i++){
        int u,v,k;
        cin>>u>>v>>k;
        u^=lastans;
        int fa=lca(u,v);
        lastans=sorted[query(k,1,len,root[u],root[v],root[fa],root[st[fa][0]])];
        cout<<lastans<<endl;
    }
    return 0;
}