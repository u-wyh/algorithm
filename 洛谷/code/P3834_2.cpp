#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int MAXT = MAXN*30;

int n,m,len;
int val[MAXN];
int sorted[MAXN];

int root[MAXN];

int ls[MAXT];
int rs[MAXT];
int sz[MAXT];
int cnt;

int build(int l,int r){
    int i=++cnt;
    sz[i]=0;
    if(l<r){
        int mid=(l+r)>>1;
        ls[i]=build(l,mid);
        rs[i]=build(mid+1,r);
    }
    return i;
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

void up(int i){
    sz[i]=sz[ls[i]]+sz[rs[i]];
}

int add(int pos,int jobv,int l,int r,int i){
    int rt=++cnt;
    sz[rt]=sz[i];
    ls[rt]=ls[i];
    rs[rt]=rs[i];

    if(l==r){
        sz[rt]++;
    }
    else{
        int mid=(l+r)>>1;
        if(pos<=mid){
            ls[rt]=add(pos,jobv,l,mid,ls[i]);
        }
        else{
            rs[rt]=add(pos,jobv,mid+1,r,rs[i]);
        }
        up(rt);
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
    for(int i=1;i<=n;i++){
        root[i]=add(find(val[i]),1,1,len,root[i-1]);
    }
}

int query(int jobk,int l,int r,int v,int u){
    if(l==r){
        return l;
    }
    else{
        int mid=(l+r)>>1;
        int lsz=sz[ls[u]]-sz[ls[v]];
        if(lsz>=jobk){
            return query(jobk,l,mid,ls[v],ls[u]);
        }
        else{
            return query(jobk-lsz,mid+1,r,rs[v],rs[u]);
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

    prepare();

    for(int i=1;i<=m;i++){
        int l,r,k;
        cin>>l>>r>>k;
        cout<<sorted[query(k,1,len,root[l-1],root[r])]<<endl;
    }
    return 0;
}