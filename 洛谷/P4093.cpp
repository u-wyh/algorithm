#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m;

int v[MAXN];
int lv[MAXN];
int rv[MAXN];

struct node{
    int v,lv,rv,id;
}nums[MAXN];

int dp[MAXN];

int tree[MAXN];

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

bool cmp1(node a,node b){
    return a.v<b.v;
}

bool cmp2(node a,node b){
    return a.lv<b.lv;
}

inline int lowbit(int x){
    return x&-x;
}

void update(int x,int v){
    while(x<=n){
        tree[x]=max(v,tree[x]);
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

void merge(int l,int mid,int r){
    for(int i=l;i<=r;i++){
        nums[i]={v[i],lv[i],rv[i],i};
    }
    sort(nums+l,nums+mid+1,cmp1);
    sort(nums+mid+1,nums+r+1,cmp2);
    int p1=l-1,p2=mid+1;
    for(;p2<=r;p2++){
        while(p1+1<=mid&&nums[p1+1].v<=nums[p2].lv){
            p1++;
            update(nums[p1].rv,dp[nums[p1].id]);
        }
        dp[nums[p2].id]=max(query(nums[p2].v)+1,dp[nums[p2].id]);
    }
    for(int i=l;i<=p1;i++){
        clear(nums[i].rv);
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
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        v[i]=read();
        lv[i]=v[i],rv[i]=v[i];
    }
    for(int i=1;i<=m;i++){
        int u,v;
        u=read(),v=read();
        lv[u]=min(lv[u],v);
        rv[u]=max(rv[u],v);
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