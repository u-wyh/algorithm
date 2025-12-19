#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5+5;
const int MAXT = MAXN*40;
const int MOD = 998244353;

int n,m;

int val[MAXN];
int arr[MAXN];

int fa[MAXN];
int soncnt[MAXN];
int son[MAXN][2];

int root[MAXN];
int ls[MAXT];
int rs[MAXT];
long long sum[MAXT];
long long tag[MAXT];
int cnt;

long long D[MAXN];

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

long long power(long long x,int p){
    long long ans=1;
    while(p){
        if(p&1){
            ans=(ans*x)%MOD;
        }
        x=(x*x)%MOD;
        p>>=1;
    }
    return ans;
}

int find(int val){
    int l=1,r=m,ans=1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(arr[mid]>=val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

void prepare(){
    for(int i=1;i<=n;i++){
        if(fa[i]!=0){
            son[fa[i]][soncnt[fa[i]]++]=i;
        }
    }
    long long inv=power(10000,MOD-2);
    for(int i=1;i<=n;i++){
        if(soncnt[i]==0){
            arr[++m]=val[i];
        }
        else{
            val[i]=(val[i]*inv)%MOD;
        }
    }
    sort(arr+1,arr+m+1);
    for(int i=1;i<=n;i++){
        if(soncnt[i]==0){
            val[i]=find(val[i]);
        }
    }
}

void up(int x){
    sum[x]=(sum[ls[x]]+sum[rs[x]])%MOD;
}

void lazy(int x,long long v){
    if(x){
        sum[x]=sum[x]*v%MOD;
        tag[x]=(tag[x]*v)%MOD;
    }
}

void down(int x){
    if(tag[x]!=1){
        lazy(ls[x],tag[x]);
        lazy(rs[x],tag[x]);
        tag[x]=1;
    }
}

int insert(int pos,int l,int r,int i){
    int rt=i;
    if(rt==0){
        rt=++cnt;
        tag[rt]=1;
    }
    if(l==r){
        sum[rt]=1;
    }
    else{
        down(rt);
        int mid=(l+r)>>1;
        if(pos<=mid){
            ls[rt]=insert(pos,l,mid,ls[rt]);
        }
        else{
            rs[rt]=insert(pos,mid+1,r,rs[rt]);
        }
        up(rt);
    }
    return rt;
}

int merge(int l,int r,int t1,int t2,int p,long long sum1,long long sum2){
    if(t1==0||t2==0){
        if(t1){
            lazy(t1,sum2);
        }
        if(t2){
            lazy(t2,sum1);
        }
        return t1+t2;
    }
    if(l==r){
        sum[t1]=(sum[t1]*sum2%MOD+sum[t2]*sum1%MOD)%MOD;
    }
    else{
        down(t1);
        down(t2);
        int mid=(l+r)>>1;
        long long lsum1=(sum1+sum[rs[t1]]*(1-p+MOD)%MOD)%MOD;
        long long lsum2=(sum2+sum[rs[t2]]*(1-p+MOD)%MOD)%MOD;
        long long rsum1=(sum1+sum[ls[t1]]*p%MOD)%MOD;
        long long rsum2=(sum2+sum[ls[t2]]*p%MOD)%MOD;
        ls[t1]=merge(l,mid,ls[t1],ls[t2],p,lsum1,lsum2);
        rs[t1]=merge(mid+1,r,rs[t1],rs[t2],p,rsum1,rsum2);
        up(t1);
    }
    return t1;
}

void dfs(int u){
    if(soncnt[u]==0){
        root[u]=insert(val[u],1,m,root[u]);
    }
    else if(soncnt[u]==1){
        dfs(son[u][0]);
        root[u]=root[son[u][0]];
    }
    else{
        dfs(son[u][0]);
        dfs(son[u][1]);
        root[u]=merge(1,m,root[son[u][0]],root[son[u][1]],val[u],0,0);
    }
}

void compute(int l,int r,int i){
    if(l==r){
        D[l]=sum[i]%MOD;
    }
    else{
        down(i);
        int mid=(l+r)>>1;
        compute(l,mid,ls[i]);
        compute(mid+1,r,rs[i]);
    }
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        fa[i]=read();
    }
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    prepare();
    dfs(1);
    compute(1,m,root[1]);
    long long ans=0;
    for(int i=1;i<=m;i++){
        ans=(ans+(1ll*i*arr[i])%MOD*D[i]%MOD*D[i]%MOD)%MOD;
    }
    cout<<ans<<endl;
    return 0;
}