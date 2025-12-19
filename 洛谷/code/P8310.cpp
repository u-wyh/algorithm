#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;
const int MAXM = 1e5+5;
const int MOD = 19260817;

struct node{
    int sum,add,mul,len;
}tree[MAXN<<2],tree1[MAXN<<2];
int n,m;
int arr[MAXN];
struct question{
    int op,l,r,w;
}nums[MAXM];
int last=0;

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
    tree[i].sum=(tree[i<<1].sum+tree[i<<1|1].sum)%MOD;
}

void build(int l,int r,int i){
    tree[i].len=r-l+1;
    tree[i].add=0;
    tree[i].mul=1;
    if(l==r){
        tree[i].sum=arr[l]%MOD;
    }
    else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

void mullazy(int i,int v){
    tree[i].sum*=v;
    tree[i].add*=v;
    tree[i].mul*=v;
    tree[i].sum%=MOD;
    tree[i].add%=MOD;
    tree[i].mul%=MOD;
}

void addlazy(int i,int v){
    tree[i].sum+=tree[i].len*v;
    tree[i].add+=v;
    tree[i].sum%=MOD;
    tree[i].add%=MOD;
}

void down(int i){
    if(tree[i].mul!=1){
        mullazy(i<<1,tree[i].mul);
        mullazy(i<<1|1,tree[i].mul);
        tree[i].mul=1;
    }
    if(tree[i].add){
        addlazy(i<<1,tree[i].add);
        addlazy(i<<1|1,tree[i].add);
        tree[i].add=0;
    }
}

void add(int jobl,int jobr,int jobv,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        addlazy(i,jobv);
    }
    else{
        int mid=(l+r)/2;
        down(i);
        if(jobl<=mid){
            add(jobl,jobr,jobv,l,mid,i<<1);
        }
        if(jobr>mid){
            add(jobl,jobr,jobv,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

void mul(int jobl,int jobr,int jobv,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        mullazy(i,jobv);
    }
    else{
        int mid=(l+r)/2;
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
    if(jobl<=l&&r<=jobr){
        return tree[i].sum;
    }
    else {
        int mid=(l+r)/2;
        down(i);
        int ans=0;
        if(jobl<=mid){
            ans+=query(jobl,jobr,l,mid,i<<1);
        }
        ans%=MOD;
        if(jobr>mid){
            ans+=query(jobl,jobr,mid+1,r,i<<1|1);
        }
        return ans%MOD;
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        arr[i]=read();
    }
    build(1,n,1);
    for(int i=1;i<=4*n;i++){
        tree1[i]=tree[i];
    }
    for(int i=1;i<=m;i++){
        nums[i].op=read();
        if(nums[i].op==1){
            nums[i].l=read(),nums[i].r=read();
            nums[i].w=read();
            add(nums[i].l,nums[i].r,nums[i].w,1,n,1);
        }
        else if(nums[i].op==2){
            nums[i].l=read(),nums[i].r=read();
            nums[i].w=read();
            mul(nums[i].l,nums[i].r,nums[i].w,1,n,1);
        }
        else if(nums[i].op==3){
            nums[i].l=read(),nums[i].r=read();
            cout<<query(nums[i].l,nums[i].r,1,n,1)<<endl;
        }
        else{
            swap(tree1,tree);
            for(int j=i-1;j>last;j--){
                if(nums[j].op==1){
                    add(nums[j].l,nums[j].r,nums[j].w,1,n,1);
                }
                else if(nums[j].op==2){
                    mul(nums[j].l,nums[j].r,nums[j].w,1,n,1);
                }
            }
            last=i;
        }
    }
    return 0;
}
