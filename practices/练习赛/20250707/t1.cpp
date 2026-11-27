#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 150005;
const int MAXM = 3e6+5;

int n,m;
struct node{
    int l,r;
}nums[MAXN];

int tree[MAXM];

bool cmp(node a,node b){
    return (a.r!=b.r)?(a.r<b.r):(a.l<b.l);
}

inline int lowbit(int x){
    return x&-x;
}

void update(int x,int val){
    while(x<=m){
        tree[x]=max(val,tree[x]);
        x+=lowbit(x);
    }
}

int query(int x){
    int ans=0;
    while(x){
        ans=max(ans,tree[x]);
        x-=lowbit(x);
    }
    return ans;
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i].l>>nums[i].r;
        nums[i].l++;
        nums[i].r++;
        m=max(m,nums[i].r);
    }
    sort(nums+1,nums+n+1,cmp);
    for(int i=1;i<=n;i++){
        int k=query(nums[i].l-1);
        update(nums[i].r,nums[i].r-nums[i].l+1+k);
    }
    printf("%lld\n",query(m));
    return 0;
}