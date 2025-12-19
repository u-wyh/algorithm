#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9+7;
const int MAXN = 1e5+5;

int n,m;
int nums[MAXN];

int minn[MAXN<<2];

int tree[MAXN];
int pre[MAXN];
int h[MAXN];
mt19937_64 rng(time(0));

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
    minn[i]=min(minn[i<<1],minn[i<<1|1]);
}

void build(int l,int r,int i){
    if(l==r){
        minn[i]=nums[l];
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
        minn[i]=jobv;
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

int query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return minn[i];
    }
    else{
        int ans=INT_MAX;
        int mid=(l+r)>>1;
        if(jobl<=mid){
            ans=min(ans,query(jobl,jobr,l,mid,i<<1));
        }
        if(jobr>mid){
            ans=min(ans,query(jobl,jobr,mid+1,r,i<<1|1));
        }
        return ans;
    }
}

inline int lowbit(int x){
    return x&-x;
}

void add(int x,int v){
    while(x<=n){
        tree[x]+=v;
        x+=lowbit(x);
    }
}

int sum(int x){
    int ans=0;
    while(x){
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}

signed main()
{
    for(int i=1;i<MAXN;i++){
        h[i]=rng()%MOD;
    }
    for(int i=1;i<MAXN;i++){
        pre[i]=h[i]+pre[i-1];
    }
    int T=read();
    while(T--){
        n=read(),m=read();
        for(int i=1;i<=n;i++){
            nums[i]=read();
        }
        build(1,n,1);
        for(int i=1;i<=n;i++){
            tree[i]=0;
        }
        for(int i=1;i<=n;i++){
            add(i,h[nums[i]]);
        }
        while(m--){
            int op,x,y,l,r;
            op=read();
            if(op==1){
                x=read(),y=read();
                update(x,y,1,n,1);
                add(x,h[y]-h[nums[x]]);
                nums[x]=y;
            }
            else{
                l=read(),r=read();
                int val=query(l,r,1,n,1);
                int hashval=sum(r)-sum(l-1);
                // cout<<val<<":  ";
                if(hashval==(pre[val+r-l]-pre[val-1])){
                    cout<<"YES"<<endl;
                }
                else{
                    cout<<"NO"<<endl;
                }
            }
        }
    }
    return 0;
}