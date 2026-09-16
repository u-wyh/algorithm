#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXT = MAXN*40;

int n;
int val[MAXN];
int arr[MAXN];

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cnt=1;

int root[MAXN];
int ls[MAXT];
int rs[MAXT];
int sz[MAXT];
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

int find(int val){
    int l=1,r=n,ans=1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(arr[mid]>=val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

void up(int i){
    sz[i]=sz[ls[i]]+sz[rs[i]];
}

int add(int val,int l,int r,int i){
    int rt=i;
    if(rt==0){
        rt=++cntv;
    }

    if(l==r){
        sz[rt]++;
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

int merge(int l,int r,int u,int v){
    if(u==0||v==0){
        return u+v;
    }
    if(l==r){
        sz[u]+=sz[v];
    }
    else{
        int mid=(l+r)>>1;
        ls[u]=merge(l,mid,ls[u],ls[v]);
        rs[u]=merge(mid+1,r,rs[u],rs[v]);
        up(u);
    }
    return u;
}

int query(int jobl,int jobr,int l,int r,int i){
    if(jobl>jobr||i==0){
        return 0;
    }
    if(jobl<=l&&r<=jobr){
        return sz[i];
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

void dfs(int u){
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs(v);
        root[u]=merge(1,n,root[u],root[v]);
    }
    ans[u]=query(val[u]+1,n,1,n,root[u]);
}

void compute(){
    for(int i=1;i<=n;i++){
        arr[i]=val[i];
    }
    sort(arr+1,arr+n+1);
    for(int i=1;i<=n;i++){
        val[i]=find(val[i]);
    }
    for(int i=1;i<=n;i++){
        root[i]=add(val[i],1,n,root[i]);
    }
    dfs(1);
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    for(int i=2;i<=n;i++){
        int u=read();
        addedge(u,i);
    }
    compute();
    for(int i=1;i<=n;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}