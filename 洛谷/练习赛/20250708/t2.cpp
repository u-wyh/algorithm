#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;

int n,q;
int val[MAXN];

int sum[MAXN<<2];
int maxx[MAXN<<2];
int minn[MAXN<<2];
int len[MAXN<<2];
int tag[MAXN<<2];

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

void up(int i){
    maxx[i]=max(maxx[i<<1],maxx[i<<1|1]);
    minn[i]=min(minn[i<<1],minn[i<<1|1]);
    sum[i]=sum[i<<1]+sum[i<<1|1];
}

void build(int l,int r,int i){
    len[i]=r-l+1;
    tag[i]=0;
    if(l==r){
        sum[i]=val[l];
        maxx[i]=val[l];
        minn[i]=val[l];
    }
    else{
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

void lazy(int i,int v){
    sum[i]=len[i]*v;
    maxx[i]=v;
    minn[i]=v;
    tag[i]=v;
}

void down(int i){
    if(tag[i]){
        lazy(i<<1,tag[i]);
        lazy(i<<1|1,tag[i]);
        tag[i]=0;
    }
}

int query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return sum[i];
    }
    else{
        int ans=0;
        down(i);
        int mid=(l+r)>>1;
        if(jobl<=mid){
            ans+=query(jobl,jobr,l,mid,i<<1);
        }
        if(jobr>mid){
            ans+=query(jobl,jobr,mid+1,r,i<<1|1);
        }
        return ans;
    }
}

void update(int jobl,int jobr,int jobv,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        if(minn[i]>=jobv){
            lazy(i,jobv);
        }
        else{
            int mid=(l+r)>>1;
            down(i);
            if(jobl<=mid&&maxx[i<<1]>=jobv){
                update(jobl,jobr,jobv,l,mid,i<<1);
            }
            if(jobr>mid&&maxx[i<<1|1]>=jobv){
                update(jobl,jobr,jobv,mid+1,r,i<<1|1);
            }
            up(i);
        }
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        if(jobl<=mid&&maxx[i<<1]>=jobv){
            update(jobl,jobr,jobv,l,mid,i<<1);
        }
        if(jobr>mid&&maxx[i<<1|1]>=jobv){
            update(jobl,jobr,jobv,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

signed main()
{
    n=read(),q=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    build(1,n,1);
    for(int i=1;i<=q;i++){
        int op,v;
        op=read();
        if(op==1){
            v=read();
            if(maxx[1]>v){
                update(1,n,v,1,n,1);
            }
        }
        else{
            cout<<query(1,n,1,n,1)<<endl;
        }
    }
    return 0;
}