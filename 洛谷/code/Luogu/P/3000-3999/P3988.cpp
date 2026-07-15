#include<bits/stdc++.h>
using namespace std;
const int MAXN = 7e5+5;

int n;
int tree[MAXN<<2];

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

void build(int l,int r,int i){
    tree[i]=r-l+1;
    if(l==r){
        return ;
    }
    else{
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
    }
}

void add(int pos,int l,int r,int i){
    tree[i]--;
    if(l==r){
        return ;
    }
    else{
        int mid=(l+r)>>1;
        if(pos<=mid){
            add(pos,l,mid,i<<1);
        }
        else{
            add(pos,mid+1,r,i<<1|1);
        }
    }
}

int query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return tree[i];
    }
    else{
        int ans=0;
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

int query(int k,int l,int r,int i){
    if(l==r){
        return l;
    }
    else{
        int mid=(l+r)>>1;
        if(tree[i<<1]>=k){
            return query(k,l,mid,i<<1);
        }
        else{
            return query(k-tree[i<<1],mid+1,r,i<<1|1);
        }
    }
}

int main()
{
    n=read();
    build(1,n,1);
    int cur=1;
    for(int i=1;i<=n;i++){
        int m=read();
        int len=n-i+1;
        int u=query(1,cur,1,n,1);
        // now是移动后牌顶数值的目前排名
        int now=(u+m)%len;
        if(now==0){
            now=len;
        }
        int x=query(now,1,n,1);
        printf("%d\n",x);
        add(x,1,n,1);
        if(now==len){
            cur=query(1,1,n,1);
        }
        else{
            cur=query(now,1,n,1);
        }
    }
    return 0;
}