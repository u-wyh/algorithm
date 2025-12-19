#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int MAXT = MAXN*80;

int n,all,f;
struct node{
    int val,cost;
}nums[MAXN];
int m=1;//用于去重和离散化
int help[MAXN];

int cnt=1;
int root[MAXN];
int ls[MAXT];
int rs[MAXT];
long long sum[MAXT];
int sz[MAXT];

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

int find(int val){
    int l=1,r=m,ans=m;
    while(l<=r){
        int mid=(l+r)/2;
        if(help[mid]>=val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

bool cmp(node a,node b){
    return a.val<b.val;
}

int build(int l, int r) {
    int rt = ++cnt;
    if (l == r) {
        return rt;
    } else {
        int mid = (l + r) >> 1;
        ls[rt] = build(l, mid);
        rs[rt] = build(mid + 1, r);
        return rt;
    }
}

int add(int pos,int jobv,int l,int r,int i){
    int rt=++cnt;
    ls[rt]=ls[i];
    rs[rt]=rs[i];
    sum[rt]=sum[i]+jobv;
    sz[rt]=sz[i]+1;
    if(l==r){
        return rt;
    }
    else{
        int mid=(l+r)/2;
        if(pos<=mid){
            ls[rt]=add(pos,jobv,l,mid,ls[rt]);
        }
        else{
            rs[rt]=add(pos,jobv,mid+1,r,rs[rt]);
        }
        return rt;
    }
}

long long query(int goal,int l,int r,int u,int v){
    //v版本减去u版本
    if(l==r){
        return (sum[v]-sum[u])/(sz[v]-sz[u])*goal;
    }
    int mid=(l+r)/2;
    if(sz[ls[v]]-sz[ls[u]]>=goal){
        return query(goal,l,mid,ls[u],ls[v]);
    }
    else{
        long long ans=sum[ls[v]]-sum[ls[u]];
        ans+=query(goal-sz[ls[v]]+sz[ls[u]],mid+1,r,rs[u],rs[v]);
        return ans;
    }
}

signed main()
{
    n=read(),all=read(),f=read();
    for(int i=1;i<=all;i++){
        nums[i].val=read(),nums[i].cost=read();
        help[i]=nums[i].cost;
    }
    sort(nums+1,nums+all+1,cmp);
    sort(help+1,help+all+1);
    for(int i=2;i<=all;i++){
        if(help[i]!=help[i-1]){
            help[++m]=help[i];
        }
    }
    root[0]=1;
    for(int i=1;i<=all;i++){
        int pos=find(nums[i].cost);
        root[i]=add(pos,nums[i].cost,1,m,root[i-1]);
    }
    int ans=-1;
    for(int i=n/2+1;i+n/2<=all;i++){
        if(f>=(nums[i].cost+query(n/2,1,m,root[0],root[i-1])+query(n/2,1,m,root[i],root[all]))){
            ans=nums[i].val;
        }
    }
    cout<<ans<<endl;
    return 0;
}
