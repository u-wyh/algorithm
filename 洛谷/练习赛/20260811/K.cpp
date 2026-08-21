#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 4e5+5;
const int INF = 1e15;

int n;
int val[MAXN];
int sum[MAXN];
int tree[MAXN<<2];

void build(int l,int r,int i){
    if(l==r){
        tree[i]=sum[l];
    }
    else{
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        tree[i]=min(tree[i<<1],tree[i<<1|1]);
    }
}

int query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return tree[i];
    }
    else{
        int mid=(l+r)>>1;
        int ans=INF;
        if(jobl<=mid){
            ans=min(ans,query(jobl,jobr,l,mid,i<<1));
        }
        if(jobr>mid){
            ans=min(ans,query(jobl,jobr,mid+1,r,i<<1|1));
        }
        return ans;
    }
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>val[i];
        val[i+n]=val[i];
    }
    for(int i=1;i<=2*n;i++){
        sum[i]=sum[i-1]+val[i];
    }

    build(1,2*n,1);

    int ans=0;
    for(int i=1;i<=n;i++){
        if(sum[i-1]<=query(i,i+n-1,1,2*n,1)){
            ans++;
        }
    }
    cout<<ans<<endl;
    return 0;
}