#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXT = MAXN*40;

int type,n,q,m,k,mod;
int val[MAXN];
int g[MAXN],r[MAXN];
int arr[MAXN];

long long sum[MAXN];

int root[MAXN];
int tree[MAXT];
int ls[MAXT];
int rs[MAXT];
int cnt;

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
    int l=1,r=m,ans=m+1;
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

int findpos(int v){
    int l=1,r=n,ans=n+1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(val[mid]>v){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

int build(int l,int r){
    int rt=++cnt;
    if(l<r){
        int mid=(l+r)>>1;
        ls[rt]=build(l,mid);
        rs[rt]=build(mid+1,r);
    }
    return rt;
}

int insert(int pos,int l,int r,int i){
    int rt=++cnt;
    ls[rt]=ls[i];
    rs[rt]=rs[i];
    tree[rt]=tree[i]+1;
    if(l<r){
        int mid=(l+r)>>1;
        if(pos<=mid){
            ls[rt]=insert(pos,l,mid,ls[rt]);
        }
        else{
            rs[rt]=insert(pos,mid+1,r,rs[rt]);
        }
    }
    return rt;
}

int query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return tree[i];
    }
    else{
        int mid=(l+r)>>1;
        int ans=0;
        if(jobl<=mid){
            ans+=query(jobl,jobr,l,mid,ls[i]);
        }
        if(jobr>mid){
            ans+=query(jobl,jobr,mid+1,r,rs[i]);
        }
        return ans;
    }
}

void prepare(){
    sort(val+1,val+n+1);
    for(int i=1;i<=n;i++){
        g[i]=val[i]/k;
        r[i]=val[i]%k;
        arr[i]=r[i];
    }
    sort(arr+1,arr+n+1);
    m=1;
    for(int i=2;i<=n;i++){
        if(arr[i]!=arr[i-1]){
            arr[++m]=arr[i];
        }
    }
    for(int i=1;i<=n;i++){
        r[i]=find(r[i]);
        sum[i]=sum[i-1]+g[i];
        // cout<<i<<":  "<<sum[i]<<endl;
    }
    // cout<<endl;
    root[0]=build(1,m);
    for(int i=1;i<=n;i++){
        root[i]=insert(r[i],1,m,root[i-1]);
    }
}

long long fun(int x){
    if(x<=0){
        return 0;
    }

    int pos=findpos(x)-1;
    if(pos<=0){
        return 0;
    }

    long long ans=0;
    int gval=x/k;
    int rval=x%k;
    ans+=1ll*pos*gval-sum[pos];

    int lt=find(rval+1);
    // cout<<' '<<x<<' '<<r<<' '<<lt<<endl;
    if(lt<=m){
        ans-=query(lt,m,1,m,root[pos]);
    }
    // cout<<x<<' '<<gval<<' '<<pos<<' '<<sum[pos]<<' '<<lt<<' '<<m<<endl;
    return ans;
}

int main()
{
    type=read(),n=read(),q=read(),k=read();
    if(type){
        mod=read();
    }
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    prepare();
    long long ans=0;
    for(int i=1;i<=q;i++){
        long long l,r;
        l=read(),r=read();
        if(i!=1&&type){
            l=(l+ans-1)%mod+1;
            r=(r+ans-1)%mod+1;
            if(l>r){
                swap(l,r);
            }
        }

        // cout<<i<<":   "<<r<<' '<<fun(r)<<endl;
        // cout<<i<<":   "<<(l-1)<<' '<<fun(l-1)<<endl;

        ans=fun(r)-fun(l-1);
        printf("%lld\n",ans);
    }
    return 0;
}
/*
0
5 10 3
1 2 3 4 5
1 5
2 5
3 5
4 5
5 5
10 10
20 30
10 30
1 30
5 30
*/