#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 3e5+5;
const int MOD = 998244353;

int n,m;
int nums[MAXN];

int minn[MAXN<<2];
int maxx[MAXN<<2];
int sum[MAXN<<2];

struct node{
    int mn,mx,all;
};

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
            ans=(ans*a)%MOD;
        }
        b>>=1;
        a=(a*a)%MOD;
    }
    return ans;
}

void up(int i){
    minn[i]=min(minn[i<<1],minn[i<<1|1]);
    maxx[i]=max(maxx[i<<1],maxx[i<<1|1]);
    sum[i]=(sum[i<<1]+sum[i<<1|1])%MOD;
}

void build(int l,int r,int i){
    if(l==r){
        minn[i]=maxx[i]=nums[l];
        sum[i]=power(2,nums[l]);
    }
    else{
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

void update(int pos,int jobv,int l,int r,int i){
    if(l==r){
        minn[i]=maxx[i]=jobv;
        sum[i]=power(2,jobv);
    }
    else{
        int mid=(l+r)>>1;
        if(pos<=mid){
            update(pos,jobv,l,mid,i<<1);
        }
        else{
            update(pos,jobv,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

node compute(node a,node b){
    return {min(a.mn,b.mn),max(a.mx,b.mx),(a.all+b.all)%MOD};
}

node query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return {minn[i],maxx[i],sum[i]};
    }
    else{
        int mid=(l+r)>>1;
        node ans={INT_MAX,INT_MIN,0};
        if(jobl<=mid){
            ans=compute(ans,query(jobl,jobr,l,mid,i<<1));
        }
        if(jobr>mid){
            ans=compute(ans,query(jobl,jobr,mid+1,r,i<<1|1));
        }
        return ans;
    }
}

signed main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        nums[i]=read();
    }
    build(1,n,1);
    int ans=0;
    for(int i=1;i<=m;i++){
        int op,l,r,v;
        op=read(),l=read(),r=read();
        l^=ans,r^=ans;
        if(op==2){
            v=read();
            v^=ans;
            if(l==r){
                cout<<"Yes"<<endl;
                ans++;
                continue;
            }
            node res=query(l,r,1,n,1);
            // cout<<i<<":  "<<res.mn<<' '<<res.mx<<' '<<res.all<<endl;
            if(v==0){
                if(res.mn==res.mx){
                    cout<<"Yes"<<endl;
                    ans++;
                }
                else{
                    cout<<"No"<<endl;
                }
                continue;
            }
            if(res.mx!=(r-l)*v+res.mn){
                cout<<"No"<<endl;
                continue;
            }
            if(res.all==(((power(2,res.mn)*((power(2,((r-l+1)*v)%MOD)+MOD-1)%MOD))%MOD)*power((power(2,v)+MOD-1)%MOD,MOD-2))%MOD){
                cout<<"Yes"<<endl;
                ans++;
            }
            else{
                cout<<"No"<<endl;
            }
        }
        else{
            update(l,r,1,n,1);
        }
    }
    return 0;
}