#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5+5;

int n,q;

struct node{
    int l,r,op;
}nums[MAXN];
int len,m=1;
int help[MAXN*4];

int val[MAXN<<4];
int tree[MAXN<<4];
bool change[MAXN<<4];
int tag[MAXN<<4];

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

int find(int val){
    int l=1,r=m,ans=m;
    while(l<=r){
        int mid=(l+r)/2;
        if(help[mid]>=val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

void up(int i){
    tree[i]=tree[i<<1]+tree[i<<1|1];
}

void build(int l,int r,int i){
    change[i]=false;
    if(l==r){
        val[i]=tree[i]=help[l+1]-help[l];
    }
    else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        val[i]=val[i<<1]+val[i<<1|1];
        tree[i]=tree[i<<1]+tree[i<<1|1];
    }
}

void lazy(int i,int v){
    tree[i]=val[i]*v;
    change[i]=true;
    tag[i]=v;
}

void down(int i){
    if(change[i]){
        lazy(i<<1,tag[i]);
        lazy(i<<1|1,tag[i]);
        change[i]=false;
    }
}

void update(int jobl,int jobr,int jobv,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        lazy(i,jobv);
    }
    else{
        int mid=(l+r)/2;
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

int main()
{
    n=read(),q=read();
    help[++len]=1;
    for(int i=1;i<=q;i++){
        nums[i].l=read(),nums[i].r=read(),nums[i].op=read();
        help[++len]=nums[i].l;
        help[++len]=nums[i].r;
        if(nums[i].l!=1)
            help[++len]=nums[i].l-1;
        if(nums[i].r!=n)
            help[++len]=nums[i].r+1;
    }
    sort(help+1,help+len+1);
    for(int i=2;i<=len;i++){
        if(help[i]!=help[i-1]){
            help[++m]=help[i];
        }
    }
    help[m+1]=n+1;
    build(1,m,1);
    // cout<<tree[1]<<endl;
    for(int i=1;i<=q;i++){
        int l=find(nums[i].l);
        int r=find(nums[i].r);
        update(l,r,nums[i].op-1,1,m,1);
        printf("%d\n",tree[1]);
    }
    return 0;
}