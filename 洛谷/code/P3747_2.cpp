// https://www.luogu.com.cn/problem/P3747
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e4+5;

int n,m,p,c;
int a[MAXN];

int tree[MAXN<<2];
int mincnt[MAXN<<2];

int len;
int mod[60];
int val[MAXN][60];

int phi(int n){
    int ans=n;
    for(int i=2;i*i<=n;i++){
        if(n%i==0){
            ans=ans/i*(i-1);
            while(n%i==0){
                n/=i;
            }
        }
    }
    if(n>1){
        ans=ans/n*(n-1);
    }
    return ans;
}

bool flag1=false;
bool flag2=false;

int power(int a,int b,int mod){
    int ans=1;
    while(b){
        if(b&1){
            ans=ans*a;
            if(ans>=mod){
                flag2=true;
            }
            else if(flag1){
                flag2=true;
            }
            ans%=mod;
        }
        b>>=1;
        a=(a*a);
        if(a>=mod){
            flag1=true;
        }
        a%=mod;
    }
    return ans;
}

int calc(int id,int k,int dep){
    if(k==0){
        if(a[id]>=mod[dep]){
            flag2=true;
        }
        else{
            flag2=false;
        }
        return a[id]%mod[dep];
    }
    int p=calc(id,k-1,dep+1);
    if(flag2){
        p=p+mod[dep+1];
    }
    flag1=false;
    flag2=false;
    return power(c,p,mod[dep]);
}

void prepare(){
    mod[0]=p;
    while(mod[len]!=1){
        ++len;
        mod[len]=phi(mod[len-1]);
    }
    mod[++len]=1;

    for(int i=1;i<=n;i++){
        for(int j=1;j<=len;j++){
            val[i][j]=calc(i,j,0);
        }
    }
}

void up(int x){
    tree[x]=(tree[x<<1]+tree[x<<1|1])%p;
    mincnt[x]=min(mincnt[x<<1],mincnt[x<<1|1]);
}

void build(int l,int r,int i){
    if(l==r){
        tree[i]=a[l];
    }
    else{
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

void update(int jobl,int jobr,int l,int r,int i){
    if(mincnt[i]>=len){
        return ;
    }
    if(l==r){
        mincnt[i]++;
        tree[i]=val[l][mincnt[i]];
    }
    else{
        int mid=(l+r)>>1;
        if(jobl<=mid){
            update(jobl,jobr,l,mid,i<<1);
        }
        if(jobr>mid){
            update(jobl,jobr,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

int query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return tree[i];
    }
    else{
        int mid=(l+r)>>1;
        int ans=0;
        if(jobl<=mid){
            ans+=query(jobl,jobr,l,mid,i<<1);
        }
        if(jobr>mid){
            ans+=query(jobl,jobr,mid+1,r,i<<1|1);
        }
        ans%=p;
        return ans;
    }
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin>>n>>m>>p>>c;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    prepare();
    build(1,n,1);
    for(int i=1;i<=m;i++){
        int op,l,r;
        cin>>op>>l>>r;
        if(op==0){
            update(l,r,1,n,1);
        }
        else{
            cout<<query(l,r,1,n,1)<<endl;
        }
    }
    return 0;
}