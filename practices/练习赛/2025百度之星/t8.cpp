#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;
const int MOD = 1e9+7;

int n,m,rate,minn,maxx;
int INV2;
int val[MAXN];
int tmp[MAXN];

int tree[MAXN<<2];
int tag[MAXN<<2];

int cnt[MAXN];

int power(int a,int b){
    int ans=1;
    while(b){
        if(b&1){
            ans=(ans*a)%MOD;
        }
        b>>=1;
        a=(a*a)%MOD;
    }
    return ans;
}

int find(int val){
    int l=1,r=m,ans=1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(tmp[mid]>=val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

inline int lowbit(int x){
    return x&-x;
}

inline void add(int x,int val){
    while(x<=m){
        cnt[x]+=val;
        x+=lowbit(x);
    }
}

int sum(int x){
    int ans=0;
    while(x){
        ans+=cnt[x];
        x-=lowbit(x);
    }
    return ans;
}

void build(int l,int r,int i){
    tag[i]=1;
    if(l<r){
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
    }
}

void up(int x){
    tree[x]=(tree[x<<1]+tree[x<<1|1])%MOD;
}

void mullazy(int x,int val){
    tag[x]=(tag[x]*val)%MOD;
    tree[x]=(tree[x]*val)%MOD;
}

void down(int i){
    if(tag[i]!=1){
        mullazy(i<<1,tag[i]);
        mullazy(i<<1|1,tag[i]);
        tag[i]=1;
    }
}

void add(int pos,int val,int l,int r,int i){
    if(l==r){
        tree[i]=(tree[i]+val)%MOD;
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        if(pos<=mid){
            add(pos,val,l,mid,i<<1);
        }
        else{
            add(pos,val,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

void mul(int jobl,int jobr,int jobv,int l,int r,int i){
    if(jobl>jobr){
        return ;
    }
    if(jobl<=l&&r<=jobr){
        mullazy(i,jobv);
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        if(jobl<=mid){
            mul(jobl,jobr,jobv,l,mid,i<<1);
        }
        if(jobr>mid){
            mul(jobl,jobr,jobv,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

int query(int jobl,int jobr,int l,int r,int i){
    if(jobr<jobl){
        return 0;
    }
    if(jobl<=l&&r<=jobr){
        return tree[i];
    }
    else{
        int mid=(l+r)>>1;
        int ans=0;
        down(i);
        if(jobl<=mid){
            ans=(ans+query(jobl,jobr,l,mid,i<<1))%MOD;
        }
        if(jobr>mid){
            ans=(ans+query(jobl,jobr,mid+1,r,i<<1|1))%MOD;
        }
        return ans;
    }
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>rate;
    for(int i=1;i<=n;i++){
        cin>>val[i];
        tmp[i]=val[i];
    }
    int inv=power(100,MOD-2);
    INV2=power(2,MOD-2);
    minn=(rate*inv)%MOD;
    maxx=((100-rate)*inv)%MOD;
    // cout<<minn<<' '<<maxx<<endl;

    sort(tmp+1,tmp+n+1);
    m=1;
    for(int i=2;i<=n;i++){
        if(tmp[i]!=tmp[i-1]){
            tmp[++m]=tmp[i];
        }
    }
    for(int i=1;i<=n;i++){
        val[i]=find(val[i]);
    }

    build(1,m,1);
    for(int i=1;i<=n;i++){
        add(val[i],1);
    }

    int ans=0;

    add(val[1],1,1,m,1);
    for(int i=1;i<=n;i++){
        add(val[i],-1);
        int now=1;
        int b=sum(val[i])-sum(val[i]-1);
        int a=sum(val[i]-1);
        int c=n-i-a-b;
        // cout<<' '<<a<<' '<<b<<' '<<c;
        now=(((power(maxx,a)*power(minn,c))%MOD)*power(INV2,b))%MOD;
        // cout<<' '<<now;
        if(i!=1){
            b=query(val[i],val[i],1,m,1);
            a=query(1,val[i]-1,1,m,1);
            c=query(val[i]+1,m,1,m,1);
            int now1=(((a*maxx)%MOD)+((b*INV2)%MOD)+((c*minn)%MOD))%MOD;
            now=(now*now1)%MOD;
            // cout<<' '<<a<<' '<<b<<' '<<c;

            mul(1,val[i]-1,minn,1,m,1);
            mul(val[i]+1,m,maxx,1,m,1);
            add(val[i],((a*maxx)%MOD+(c*minn)%MOD)%MOD,1,m,1);
        }
        // int res=((tmp[val[i]]*now)%MOD);
        // cout<<' '<<now<<' '<<res<<endl;
        ans=(ans+((tmp[val[i]]*now)%MOD))%MOD;
    }
    cout<<ans<<endl;

    // int res=0;
    // for(int i=1;i<=m;i++){
    //     res=(res+(query(i,i,1,m,1)*tmp[i]%MOD))%MOD;
    // }
    // cout<<res<<endl;
    return 0;
}
/*
5 100
9 10 5 3 8

5 100
3 5 9 8 10

2 50
1 3

3 100
1 2 3

4 50
1 2 2 3

4 10
2 2 2 2
*/