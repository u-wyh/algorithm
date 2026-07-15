#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9+7;
const int MAXN = 1e5+5;

int n,m;
int arr[MAXN];
int sum[MAXN<<2];
int squ[MAXN<<2];

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

int power(int a,int b){
    int ans=1;
    while(b){
        if(b&1){
            ans*=a;
            ans%=MOD;
        }
        b>>=1;
        a*=a;
        a%=MOD;
    }
    return ans;
}

int inv(int a,int MOD){
    return power(a,MOD-2);
}

void up(int i){
    sum[i]=sum[i<<1]+sum[i<<1|1];
    squ[i]=squ[i<<1]+squ[i<<1|1];
    sum[i]%=MOD;
    squ[i]%=MOD;
}

void build(int l,int r,int i){
    if(l==r){
        sum[i]=arr[l];
        squ[i]=arr[l]*arr[l];
    }
    else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

void update(int pos,int jobv,int l,int r,int i){
    if(l==r){
        sum[i]=jobv;
        squ[i]=jobv*jobv;
    }
    else{
        int mid=(l+r)/2;
        if(pos<=mid){
            update(pos,jobv,l,mid,i<<1);
        }
        else{
            update(pos,jobv,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

int querysum(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return sum[i];
    }
    else{
        int mid=(l+r)/2;
        int ans=0;
        if(jobl<=mid){
            ans+=querysum(jobl,jobr,l,mid,i<<1);
        }
        if(jobr>mid){
            ans+=querysum(jobl,jobr,mid+1,r,i<<1|1);
        }
        ans%=MOD;
        return ans;
    }
}

int querysqu(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return squ[i];
    }
    else{
        int mid=(l+r)/2;
        int ans=0;
        if(jobl<=mid){
            ans+=querysqu(jobl,jobr,l,mid,i<<1);
        }
        if(jobr>mid){
            ans+=querysqu(jobl,jobr,mid+1,r,i<<1|1);
        }
        ans%=MOD;
        return ans;
    }
}

signed main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        arr[i]=read();
    }
    build(1,n,1);
    for(int i=1;i<=m;i++){
        int op,l,r;
        op=read(),l=read(),r=read();
        if(op==1){
            update(l,r,1,n,1);
        }
        else{
            int len=r-l+1;
            len=inv(len,MOD);
            int ans=(len*querysqu(l,r,1,n,1))%MOD;
            int k=(querysum(l,r,1,n,1)*len)%MOD;
            k=(k*k)%MOD;
            ans-=k;
            ans=(ans%MOD+MOD)%MOD;
            cout<<ans<<endl;
        }
    }
    return 0;
}