#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5+5;

int n,m;
int val[MAXN];
int prime[]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
int p[]={0,3,6,8,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30};
int q[]={7,56,192,768,1<<10,1<<11,1<<12,1<<13,1<<14,1<<15,1<<16,1<<17,1<<18,1<<19,1<<20,1<<21,1<<22,1<<23,1<<24,1<<25,1<<26,1<<27,1<<28,1<<29,1<<30};

int g[MAXN<<2];
int f[MAXN<<2];
int tag[MAXN<<2];

int fun(int val){
    int ans=0;
    for(int i=0;i<=24;i++){
        int cnt=0;
        while(val%prime[i]==0){
            cnt++;
            val/=prime[i];
        }
        if(cnt){
            ans+=cnt<<p[i];
        }
        if(val==1){
            break;
        }
    }
    return ans;
}

int gcd(int val1,int val2){
    int ans=0;
    ans=((val1>>10)&(val2>>10))<<10;
    ans+=min((val1&7),(val2&7));
    ans+=min((val1&56),(val2&56));
    ans+=min((val1&192),(val2&192));
    ans+=min((val1&768),(val2&768));
    return ans;
}

int lcm(int val1,int val2){
    int ans=0;
    ans=((val1>>10)|(val2>>10))<<10;
    ans+=max((val1&7),(val2&7));
    ans+=max((val1&56),(val2&56));
    ans+=max((val1&192),(val2&192));
    ans+=max((val1&768),(val2&768));
    return ans;
}

void up(int i){
    g[i]=gcd(g[i<<1],g[i<<1|1]);
    f[i]=lcm(f[i<<1],f[i<<1|1]);
}

void build(int l,int r,int i){
    tag[i]=-1;
    if(l==r){
        f[i]=g[i]=fun(val[l]);
        // cout<<i<<":  "<<f[i]<<endl;
    }
    else{
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

void lazy(int i,int v){
    g[i]=v;
    f[i]=v;
    tag[i]=v;
}

void down(int i){
    if(tag[i]!=-1){
        lazy(i<<1,tag[i]);
        lazy(i<<1|1,tag[i]);
        tag[i]=-1;
    }
}

void update(int jobl,int jobr,int jobv,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        lazy(i,jobv);
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        if(jobl<=mid){
            update(jobl,jobr,jobv,l,mid,i<<1);
        }
        if(jobr>mid){
            update(jobl,jobr,jobv,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

int lcm(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return f[i];
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        if(jobl<=mid&&jobr>mid){
            return lcm(lcm(jobl,jobr,l,mid,i<<1),lcm(jobl,jobr,mid+1,r,i<<1|1));
        }
        else if(jobl<=mid){
            return lcm(jobl,jobr,l,mid,i<<1);
        }
        else{
            return lcm(jobl,jobr,mid+1,r,i<<1|1);
        }
    }
}

int gcd(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return g[i];
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        if(jobl<=mid&&jobr>mid){
            return gcd(gcd(jobl,jobr,l,mid,i<<1),gcd(jobl,jobr,mid+1,r,i<<1|1));
        }
        else if(jobl<=mid){
            return gcd(jobl,jobr,l,mid,i<<1);
        }
        else{
            return gcd(jobl,jobr,mid+1,r,i<<1|1);
        }
    }
}

int compute(int val,int mod){
    long long ans=1;
    for(int i=0;i<=24;i++){
        int t=(val&q[i])>>p[i];
        for(int j=1;j<=t;j++){
            ans=(ans*prime[i])%mod;
        }
    }
    return ans;
}

int compute2(int val,int mod){
    int ans=1;
    for(int i=0;i<=24;i++){
        int t=(val&q[i])>>p[i];
        ans=(ans*(t+1))%mod;
    }
    return ans;
}

int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&val[i]);
    }
    build(1,n,1);
    for(int i=1;i<=m;i++){
        char op;
        int l,r,x;
        scanf(" %c %d %d %d",&op,&l,&r,&x);
        if(op=='L'){
            int ans=lcm(l,r,1,n,1);
            ans=compute(ans,x);
            printf("%d\n",ans%x);
        }
        else if(op=='G'){
            int ans=gcd(l,r,1,n,1);
            ans=compute(ans,x);
            printf("%d\n",ans%x);
        }
        else if(op=='C'){
            update(l,r,fun(x),1,n,1);
        }
        else{
            int ans=gcd(l,r,1,n,1);
            ans=compute2(ans,x);
            printf("%d\n",ans%x);
        }
    }
    return 0;
}
/*
10 10
42 68 35 1 70 25 79 59 63 65 
L 2 6 28
L 2 6 43
G 2 7 5
G 3 4 83
L 7 9 96
G 2 7 39
S 3 8 100
L 4 5 12
G 4 4 65
L 2 4 69
*/