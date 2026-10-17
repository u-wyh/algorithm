// https://www.luogu.com.cn/problem/P9329
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int MAXT = MAXN*40;
const int MAXH = 20;

int n,m,q,p;

int u[MAXN],v[MAXN];
int e[MAXN],w[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cntg=1;

int root[MAXN];
int cntt;
int ls[MAXT];
int rs[MAXT];
int sum[MAXT];
int cnt[MAXT];

int dep[MAXN];
int st[MAXN][MAXH];

int len;
int sorted[MAXN];

int headg[MAXN];
int nxtg[MAXN];
int tog[MAXN];
int cnte=1;

inline void addedgeg(int u,int v){
    nxtg[cnte]=headg[u];
    tog[cnte]=v;
    headg[u]=cnte++;
}

inline void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

int find(int x){
    int l=1,r=len,ans=len;
    while(l<=r){
        int mid=(l+r)>>1;
        if(sorted[mid]>=x){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

int build(int l,int r){
    int rt=++cntt;
    if(l<r){
        int mid=(l+r)>>1;
        ls[rt]=build(l,mid);
        rs[rt]=build(mid+1,r);
    }
    return rt;
}

void dfs1(int u,int fa){
    dep[u]=dep[fa]+1;
    st[u][0]=fa;
    for(int i=1;i<=p;i++){
        st[u][i]=st[st[u][i-1]][i-1];
    }

    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa){
            dfs1(v,u);
        }
    }
}

int insert(int v,int l,int r,int i){
    int rt=++cntt;
    ls[rt]=ls[i];
    rs[rt]=rs[i];
    cnt[rt]=cnt[i]+1;
    sum[rt]=sum[i]+sorted[v];
    if(l<r){
        int mid=(l+r)>>1;
        if(v<=mid){
            ls[rt]=insert(v,l,mid,ls[rt]);
        }
        else{
            rs[rt]=insert(v,mid+1,r,rs[rt]);
        }
    }
    // else{
    //     cout<<"   "<<v<<' '<<sum[rt]<<endl;
    // }
    return rt;
}

void calc(int u,int fa){
    root[u]=root[fa];
    for(int i=headg[u];i;i=nxtg[i]){
        int v=tog[i];
        root[u]=insert(v,1,len,root[u]);
    }
}

void dfs2(int u,int fa){
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa){
            calc(v,u);
            dfs2(v,u);
        }
    }
}

void prepare(){
    p=log2(n)+1;
    dfs1(1,0);

    for(int i=1;i<=m;i++){
        sorted[i]=w[i];
    }
    sort(sorted+1,sorted+m+1);
    len=1;
    for(int i=2;i<=m;i++){
        if(sorted[i]!=sorted[i-1]){
            sorted[++len]=sorted[i];
        }
    }
    for(int i=1;i<=m;i++){
        w[i]=find(w[i]);
        int x=u[e[i]];
        int y=v[e[i]];
        if(dep[x]<dep[y]){
            addedgeg(y,w[i]);
        }
        else{
            addedgeg(x,w[i]);
        }
    }

    root[1]=build(1,len);
    dfs2(1,0);
}

int lca(int x,int y){
    if(dep[x]<dep[y]){
        swap(x,y);
    }
    for(int i=p;i>=0;i--){
        if(dep[st[x][i]]>=dep[y]){
            x=st[x][i];
        }
    }
    if(x==y){
        return x;
    }

    for(int i=p;i>=0;i--){
        if(st[x][i]!=st[y][i]){
            x=st[x][i];
            y=st[y][i];
        }
    }
    return st[x][0];
}

int compute(int l,int r,int res,int u,int v,int w){
    // cout<<l<<' '<<r<<' '<<res<<' '<<u<<' '<<v<<' '<<w<<endl;
    if(l==r){
        int all=cnt[u]+cnt[v]-2*cnt[w];
        return min(all,res/sorted[l]);
    }
    int lsum=sum[ls[u]]+sum[ls[v]]-2*sum[ls[w]];
    int mid=(l+r)>>1;
    if(lsum<=res){
        return cnt[ls[u]]+cnt[ls[v]]-2*cnt[ls[w]]+compute(mid+1,r,res-lsum,rs[u],rs[v],rs[w]);
    }   
    else{
        return compute(l,mid,res,ls[u],ls[v],ls[w]);
    }
}

int compute(int s,int t,int a,int b){
    int l=lca(s,t);
    // cout<<' '<<l<<endl;
    int need=cnt[root[s]]+cnt[root[t]]-2*cnt[root[l]] -compute(1,len,b,root[s],root[t],root[l]);
    if(need<=a){
        return a-need;
    }
    else{
        return -1;
    }
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m>>q;
    for(int i=1;i<n;i++){
        cin>>u[i]>>v[i];
        addedge(u[i],v[i]);
        addedge(v[i],u[i]);
    }
    for(int i=1;i<=m;i++){
        cin>>e[i]>>w[i];
    }

    prepare();

    for(int i=1;i<=q;i++){
        int s,t,a,b;
        cin>>s>>t>>a>>b;
        cout<<compute(s,t,a,b)<<endl;
    }
    return 0;
}