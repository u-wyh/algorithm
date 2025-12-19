#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;

int n;
int vis[MAXN];
int arr[MAXN];
int ans;
int f[MAXN];
int tree1[MAXN];

int tree[MAXN<<2];
int lazy[MAXN<<2];
int len[MAXN<<2];

int lowbit(int x){
    return x&(-x);
}

int sum(int x){
    int ans=0;
    while(x){
        ans+=tree1[x];
        x-=lowbit(x);
    }
    return ans;
}

void add(int x,int val){
    while(x<=n){
        tree1[x]+=val;
        x+=lowbit(x);
    }
}

void up(int i){
    tree[i]=tree[i<<1]+tree[i<<1|1];
}

void build(int l,int r,int i){
    len[i]=r-l+1;
    if(l==r){
        tree[i]=f[l];
    }
    else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

void downlazy(int i,int val){
    tree[i]+=val*len[i];
    lazy[i]+=val;
}

void down(int i){
    if(lazy[i]){
        downlazy(i<<1,lazy[i]);
        downlazy(i<<1|1,lazy[i]);
        lazy[i]=0;
    }
}

void add(int jobl,int jobr,int jobv,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        downlazy(i,jobv);
    }
    else{
        int mid=(l+r)/2;
        down(i);
        if(jobl<=mid){
            add(jobl,jobr,jobv,l,mid,i<<1);
        }
        if(jobr>mid){
            add(jobl,jobr,jobv,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

int query(int pos,int l,int r,int i){
    if(l==r){
        return tree[i];
    }
    else{
        down(i);
        int mid=(l+r)/2;
        if(pos<=mid){
            return query(pos,l,mid,i<<1);
        }
        else{
            return query(pos,mid+1,r,i<<1|1);
        }
    }
}

signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        int u;
        cin>>u;
        vis[u]=i;
    }
    for(int i=1;i<=n;i++){
        int u;
        cin>>u;
        arr[i]=vis[u];
        f[arr[i]]=sum(n)-sum(arr[i]);
        add(arr[i],1);
    }
    build(1,n,1);
    ans=tree[1];
    for(int i=1;i<n;i++){
        int k=query(arr[i],1,n,1);
        add(arr[i],arr[i],n-arr[i]-k,1,n,1);
        if(arr[i]==1){
            continue;
        }
        else{
            add(1,arr[i]-1,-1,1,n,1);
        }
        ans=min(ans,tree[1]);
    }
    cout<<ans<<endl;
    return 0;
}
