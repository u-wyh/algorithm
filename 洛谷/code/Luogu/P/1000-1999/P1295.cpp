#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int INF = 1e18;

int n,limit;

int h[MAXN];
int w[MAXN];
int f[MAXN];

int minf[MAXN<<2];
int minh[MAXN<<2];
int maxh[MAXN<<2];
int minval[MAXN<<2];
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
    minf[i]=min(minf[i<<1],minf[i<<1|1]);
    minh[i]=min(minh[i<<1],minh[i<<1|1]);
    maxh[i]=max(maxh[i<<1],maxh[i<<1|1]);
    minval[i]=min(minval[i<<1],minval[i<<1|1]);
}

void build(int l,int r,int i){
    minf[i]=INF;
    minh[i]=0;
    maxh[i]=0;
    minval[i]=INF;
    tag[i]=0;
    if(l<r){
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

void lazy(int i,int val){
    tag[i]=val;
    maxh[i]=val;
    minh[i]=val;
    minval[i]=val+minf[i];
}

// void lazy(int i,int val){
//     tag[i]=val;
//     maxh[i]=val;
//     minh[i]=val;
//     if(minf[i] < INF - val){
//         minval[i]=val+minf[i];
//     } else {
//         minval[i]=INF;
//     }
// }

void down(int i){
    if(tag[i]){
        lazy(i<<1,tag[i]);
        lazy(i<<1|1,tag[i]);
        tag[i]=0;
    }
}

void updatef(int pos,int jobv,int l,int r,int i){
    if(l==r){
        minf[i]=jobv;
        minval[i]=jobv+maxh[i];
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        if(pos<=mid){
            updatef(pos,jobv,l,mid,i<<1);
        }
        else{
            updatef(pos,jobv,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

void updateh(int jobl,int jobr,int jobv,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        if(minh[i]>=jobv){
            return ;
        }
        if(maxh[i]<=jobv){
            lazy(i,jobv);
            return ;
        }
        int mid=(l+r)>>1;
        down(i);
        updateh(jobl,jobr,jobv,l,mid,i<<1);
        updateh(jobl,jobr,jobv,mid+1,r,i<<1|1);
        // updateh(l,mid,jobv,l,mid,i<<1);
        // updateh(mid+1,r,jobv,mid+1,r,i<<1|1);
        up(i);
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        if(jobl<=mid){
            updateh(jobl,jobr,jobv,l,mid,i<<1);
        }
        if(jobr>mid){
            updateh(jobl,jobr,jobv,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

int query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return minval[i];
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        int ans=INF;
        if(jobl<=mid){
            ans=min(ans,query(jobl,jobr,l,mid,i<<1));
        }
        if(jobr>mid){
            ans=min(ans,query(jobl,jobr,mid+1,r,i<<1|1));
        }
        return ans;
    }
}

signed main()
{
    n=read(),limit=read();
    for(int i=1;i<=n;i++){
        h[i]=read();
        w[i]=h[i];
    }
    build(0,n,1);
    updatef(0,0,0,n,1);;

    int now=1,len=0;
    for(int i=1;i<=n;i++){
        len+=w[i];
        while(len>limit){
            len-=w[now];
            now++;
        }
        updateh(now-1,i-1,h[i],0,n,1);
        f[i]=query(now-1,i-1,0,n,1);
        updatef(i,f[i],0,n,1);
    }
    cout<<f[n]<<endl;
    return 0;
}