#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 1024;

int n,q,m,len;
int nums[MAXN];
bitset<MAXM>all;
bitset<MAXM>ans;
bitset<MAXM>tree[MAXN<<2];
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

void write(int x)
{
    if(x<0)
        putchar('-'),x=-x;
    if(x>9)
        write(x/10);
    putchar(x%10+'0');
    return;
}

void build(int l,int r,int i){
    if(l==r){
        tree[i].set(nums[l]);
        return ;
    }
    else{
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        tree[i]=tree[i<<1]^tree[i<<1|1];
    }
}

inline void lazy(int i,int x){
    tree[i]=((tree[i]<<x)|(tree[i]>>(len-x)))&all;
    tag[i]=(tag[i]+x)%len;
}

void down(int i){
    if(tag[i]){
        lazy(i<<1,tag[i]);
        lazy(i<<1|1,tag[i]);
        tag[i]=0;
    }
}

void add(int jobl,int jobr,int jobv,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        lazy(i,jobv);
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        if(jobl<=mid){
            add(jobl,jobr,jobv,l,mid,i<<1);
        }
        if(jobr>mid){
            add(jobl,jobr,jobv,mid+1,r,i<<1|1);
        }
        tree[i]=tree[i<<1]^tree[i<<1|1];
    }
}

void query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        ans^=tree[i];
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        if(jobl<=mid){
            query(jobl,jobr,l,mid,i<<1);
        }
        if(jobr>mid){
            query(jobl,jobr,mid+1,r,i<<1|1);
        }
    }
}

int main()
{
    n=read(),m=read(),q=read();
    len=1<<m;
    for(int i=1;i<=n;i++){
        nums[i]=read();
    }
    for(int i=0;i<len;i++){
        all.set(i);
    }
    build(1,n,1);
    while(q--){
        int op,l,r,x;
        op=read(),l=read(),r=read();
        if(op==1){
            x=read();
            if(x)
                add(l,r,x,1,n,1);
        }
        else{
            ans.reset();
            query(l,r,1,n,1);
            int res=0;
            for(int i=0;i<len;i++){
                if(ans[i]){
                    res^=i;
                }
            }
            write(res);
            putchar('\n');
        }
    }
    return 0;
}