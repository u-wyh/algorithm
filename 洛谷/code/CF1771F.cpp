#include<bits/stdc++.h>
using namespace std;
const int MOD = 1e9+7;
const int MAXN = 2e5+5;
const int MAXT = MAXN*25;

int n,q,m=1;
int nums[MAXN];
int sorted[MAXN];
int h[MAXN];

int root[MAXN];
int ls[MAXT];
int rs[MAXT];
int val[MAXT];
int cnt;

mt19937_64 rng(time(0));

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

int build(int l,int r){
    int rt=++cnt;
    if(l==r){
        return rt;
    }
    else{
        int mid=(l+r)>>1;
        ls[rt]=build(l,mid);
        rs[rt]=build(mid+1,r);
        return rt;
    }
}

int find(int val){
    int l=1,r=m,ans=1;
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

int update(int pos,int jobv,int l,int r,int i){
    int rt=++cnt;
    ls[rt]=ls[i];
    rs[rt]=rs[i];
    val[rt]=val[i]^jobv;
    if(l==r){
        return rt;
    }
    else{
        int mid=(l+r)>>1;
        if(pos<=mid){
            ls[rt]=update(pos,jobv,l,mid,ls[rt]);
        }
        else{
            rs[rt]=update(pos,jobv,mid+1,r,rs[rt]);
        }
        return rt;
    }
}

void prepare(){
    for(int i=1;i<=n;i++){
        sorted[i]=nums[i];
    }
    sort(sorted+1,sorted+n+1);
    for(int i=2;i<=n;i++){
        if(sorted[i]!=sorted[i-1]){
            sorted[++m]=sorted[i];
        }
    }
    for(int i=1;i<=n;i++){
        nums[i]=find(nums[i]);
    }
    for(int i=1;i<=m;i++){
        h[i]=(rng()%MOD+MOD)%MOD;
    }
    root[0]=build(1,m);
    for(int i=1;i<=n;i++){
        root[i]=update(nums[i],h[nums[i]],1,m,root[i-1]);
    }
}

int query(int l,int r,int v,int u){
    if((val[v]^val[u])==0){
        return 0;
    }
    if(l==r){
        return l;
    }
    else{
        int mid=(l+r)>>1;
        if((val[ls[v]]^val[ls[u]])!=0){
            return query(l,mid,ls[v],ls[u]);
        }
        else{
            return query(mid+1,r,rs[v],rs[u]);
        }
    }
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        nums[i]=read();
    }
    prepare();
    int ans=0;
    q=read();
    for(int i=1;i<=q;i++){
        int l,r;
        l=read(),r=read();
        l^=ans,r^=ans;
        ans=query(1,m,root[l-1],root[r]);
        ans=sorted[ans];
        printf("%d\n",ans);
    }
    return 0;
}