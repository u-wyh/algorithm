#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;

struct node{
    int add,val;
}tree[MAXN<<2];
int n;
int dp[MAXN];
int arr[MAXN];

void up(int i){
    tree[i].val=max(tree[i<<1].val,tree[i<<1|1].val);
}

void build(int l,int r,int i){
    tree[i].add=tree[i].val=0;
    if(l==r){
        return ;
    }
    else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

void downlazy(int i,int v){
    tree[i].val+=v;
    tree[i].add+=v;
}

void down(int i){
    if(tree[i].add){
        downlazy(i<<1,tree[i].add);
        downlazy(i<<1|1,tree[i].add);
        tree[i].add=0;
    }
}

void update(int jobl,int jobr,int v,int l,int r,int i){
    if(jobl>jobr){
        return ;
    }
    if(jobl<=l&&r<=jobr){
        downlazy(i,v);
    }
    else{
        int mid=(l+r)/2;
        down(i);
        if(jobl<=mid){
            update(jobl,jobr,v,l,mid,i<<1);
        }
        if(jobr>mid){
            update(jobl,jobr,v,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

int query(int jobl,int jobr,int l,int r,int i){
    if(jobl>jobr){
        return 0;
    }
    if(jobl<=l&&r<=jobr){
        return tree[i].val;
    }
    else{
        int mid=(l+r)/2;
        down(i);
        int ans=0;
        if(jobl<=mid){
            ans=max(ans,query(jobl,jobr,l,mid,i<<1));
        }
        if(jobr>mid){
            ans=max(ans,query(jobl,jobr,mid+1,r,i<<1|1));
        }
        return ans;
    }
}

signed main()
{
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        build(1,n,1);
        for(int i=1;i<=n;i++){
            cin>>arr[i];
        }
        for(int i=n;i>=1;i--){
            dp[i]=arr[i];
            int l=i+1,r=min(arr[i]+i,n);
            dp[i]=max(dp[i],query(l,r,1,n,1));
            update(l,n,arr[i],1,n,1);
            update(i,i,dp[i],1,n,1);
        }
        cout<<dp[1]<<endl;
    }
    return 0;
}
