#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m;
int val[MAXN];
int lv[MAXN];
int rv[MAXN];

int dp[MAXN];

struct node{
    int i,v,lv,rv;
};
node arr[MAXN];

int tree[MAXN];

int lowbit(int x){
    return x&-x;
}

void more(int x,int val){
    while(x<=n){
        tree[x]=max(tree[x],val);
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

void clear(int x){
    while(x<=n){
        tree[x]=0;
        x+=lowbit(x);
    }
}

bool cmp1(node a,node b){
    return a.v<b.v;
}

bool cmp2(node a,node b){
    return a.lv<b.lv;
}

void merge(int l,int mid,int r){
    for(int i=l;i<=r;i++){
        arr[i]={i,val[i],lv[i],rv[i]};
    }
    sort(arr+l,arr+mid+1,cmp1);
    sort(arr+mid+1,arr+r+1,cmp2);
    int p1,p2;
    for(p1=l-1,p2=mid+1;p2<=r;p2++){
        while(p1+1<=mid&&arr[p1+1].v<=arr[p2].lv){
            p1++;
            more(arr[p1].rv,dp[arr[p1].i]);
        }
        dp[arr[p2].i]=max(dp[arr[p2].i],query(arr[p2].v)+1);
    }
    for(int i=l;i<=p1;i++){
        clear(arr[i].rv);
    }
}

void cdq(int l,int r){
    if(l==r){
        return ;
    }

    int mid=(l+r)>>1;
    cdq(l,mid);
    merge(l,mid,r);
    cdq(mid+1,r);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>val[i];
        lv[i]=val[i];
        rv[i]=val[i];
    }

    for(int i=1;i<=m;i++){
        int pos,val;
        cin>>pos>>val;
        lv[pos]=min(lv[pos],val);
        rv[pos]=max(rv[pos],val);
    }

    for(int i=1;i<=n;i++){
        dp[i]=1;
    }
    cdq(1,n);

    int ans=0;
    for(int i=1;i<=n;i++){
        ans=max(ans,dp[i]);
    }
    cout<<ans<<endl;
    return 0;
}