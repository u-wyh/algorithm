// https://www.luogu.com.cn/problem/P6847
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int MAXT = MAXN*30;

int n,m,k;
int fa[MAXN];
int d[MAXN];
int w[MAXN];

int rt[MAXN];
int ls[MAXT];
int rs[MAXT];
int sum[MAXT];
int cntt=0;

int add(int pos,int jobv,int l,int r,int i){
    int rt=i;
    if(rt==0){
        rt=++cntt;
    }
    sum[rt]+=jobv;
    if(l!=r){
        int mid=(l+r)>>1;
        if(pos<=mid){
            ls[rt]=add(pos,jobv,l,mid,ls[rt]);
        } 
        else{
            rs[rt]=add(pos,jobv,mid+1,r,rs[rt]);
        }
    }
    return rt;
}

int rest;
int remove(int pos,int l,int r,int i){
    if(i==0 || rest==0 || r<=pos){
        return i;
    }

    if(l>pos && sum[i]<=rest){
        rest-=sum[i];
        return 0;
    }

    if(l==r){
        int v=min(sum[i],rest);
        sum[i]-=v;
        rest-=v;
        if(sum[i]==0){
            return 0;
        }
        return i;
    }

    int mid=(l+r)>>1;
    ls[i]=remove(pos,l,mid,ls[i]);
    rs[i]=remove(pos,mid+1,r,rs[i]);
    sum[i]=sum[ls[i]]+sum[rs[i]];
    return i;
}

int merge(int l,int r,int x,int y){
    if(x==0||y==0){
        return x+y;
    }
    if(l==r){
        sum[x]+=sum[y];
        return x;
    }
    int mid=(l+r)>>1;
    ls[x]=merge(l,mid,ls[x],ls[y]);
    rs[x]=merge(mid+1,r,rs[x],rs[y]);
    sum[x]=sum[ls[x]]+sum[rs[x]];
    return x;
}

signed main()
{
    cin>>n>>m>>k;
    for(int i=2;i<=n;i++){
        cin>>fa[i];
    }
    for(int i=1;i<=m;i++){
        int u;
        cin>>u>>d[u]>>w[u];
    }

    for(int u=n;u>=2;u--){
        if(d[u]){
            rt[u]=add(d[u],w[u],1,k,rt[u]);
            rest=w[u];
            rt[u]=remove(d[u],1,k,rt[u]);
        }

        rt[fa[u]]=merge(1,k,rt[fa[u]],rt[u]);
    }

    cout<<sum[rt[1]]<<endl;
    return 0;
}