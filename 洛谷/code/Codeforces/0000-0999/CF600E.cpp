#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int MAXT = MAXN*60;

int n;
int val[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

int root[MAXN];
int ls[MAXT];
int rs[MAXT];
int maxcnt[MAXT];
int sum[MAXT];
int cntv;

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

inline void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void up(int x){
    if(maxcnt[ls[x]]>maxcnt[rs[x]]){
        maxcnt[x]=maxcnt[ls[x]];
        sum[x]=sum[ls[x]];
    }
    else if(maxcnt[ls[x]]<maxcnt[rs[x]]){
        maxcnt[x]=maxcnt[rs[x]];
        sum[x]=sum[rs[x]];
    }
    else{
        maxcnt[x]=maxcnt[ls[x]];
        sum[x]=sum[ls[x]]+sum[rs[x]];
    }
}

int add(int val,int l,int r,int i){
    int rt=i;
    if(rt==0){
        rt=++cntv;
    }
    if(l==r){
        maxcnt[rt]++;
        sum[rt]=l;
    }
    else{
        int mid=(l+r)>>1;
        if(val<=mid){
            ls[rt]=add(val,l,mid,ls[rt]);
        }
        else{
            rs[rt]=add(val,mid+1,r,rs[rt]);
        }
        up(rt);
    }
    return rt;
}

int merge(int l,int r,int t1,int t2){
    if(t1==0||t2==0){
        return t1+t2;
    }
    if(l==r){
        maxcnt[t1]+=maxcnt[t2];
        sum[t1]=l;
    }
    else{
        int mid=(l+r)>>1;
        ls[t1]=merge(l,mid,ls[t1],ls[t2]);
        rs[t1]=merge(mid+1,r,rs[t1],rs[t2]);
        up(t1);
    }
    return t1;
}

void dfs(int u,int fa){
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa){
            dfs(v,u);
            root[u]=merge(1,n,root[u],root[v]);
        }
    }
    ans[u]=sum[root[u]];
}

signed main()
{
    n=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
        root[i]=add(val[i],1,n,root[i]);
    }
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    dfs(1,0);
    for(int i=1;i<=n;i++){
        cout<<ans[i]<<' ';
    }
    return 0;
}