#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;
const int MAXM = 3e5+5;

// int cnt;
// int prime[MAXN];
// bool vis[MAXN];

int d[MAXN];

int n,m;
int val[MAXM];

long long tree[MAXM<<2];
int maxx[MAXM<<2];

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
    tree[i]=(tree[i<<1]+tree[i<<1|1]);
    maxx[i]=max(maxx[i<<1],maxx[i<<1|1]);
}

void build(int l,int r,int i){
    if(l==r){
        tree[i]=maxx[i]=val[l];
    }
    else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

void update(int jobl,int jobr,int l,int r,int i){
    if(maxx[i]<=2){
        return ;
    }
    if(jobl<=l&&r<=jobr){
        if(l==r){
            // if(d[tree[i]]==0){
            //     fun(tree[i]);
            // }
            tree[i]=d[tree[i]];
            maxx[i]=tree[i];
            return;
        }
        int mid=(l+r)/2;
        if(maxx[i<<1]>2) update(jobl,jobr,l,mid,i<<1);
        if(maxx[i<<1|1]>2) update(jobl,jobr,mid+1,r,i<<1|1);
        up(i);
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

long long query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return tree[i];
    }
    else{
        int mid=(l+r)>>1;
        long long ans=0;
        if(jobl<=mid){
            ans+=query(jobl,jobr,l,mid,i<<1);
        }
        if(jobr>mid){
            ans+=query(jobl,jobr,mid+1,r,i<<1|1);
        }
        return ans;
    }
}

int main()
{
    // euler(1000000);
    for(int i=1;i<=1000000;i++){
        for(int j=i;j<=1000000;j+=i){
            d[j]++;
        }
    }
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    build(1,n,1);
    for(int i=1;i<=m;i++){
        int op,l,r;
        op=read(),l=read(),r=read();
        if(op==1){
            update(l,r,1,n,1);
        }
        else{
            printf("%lld\n",query(l,r,1,n,1));
        }
    }
    return 0;
}