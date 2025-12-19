#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int MAXT = MAXN*10;

int n,m;

int root[MAXN];
int ls[MAXT];
int rs[MAXT];
long long sum[MAXT];
int version;

int pool[MAXT];
int top;

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

void prepare(){
    top=0;
    for(int i=1;i<MAXT;i++){
        pool[++top]=i;
    }
}

int newnode(){
    return pool[top--];
}

void del(int x){
    pool[++top]=x;
    ls[x]=0;
    rs[x]=0;
    sum[x]=0;
}

void up(int x){
    sum[x]=sum[ls[x]]+sum[rs[x]];
}

int add(int pos,int jobv,int l,int r,int i){
    int rt=i;
    if(rt==0){
        rt=newnode();
    }
    if(l==r){
        sum[rt]+=jobv;
    }
    else{
        int mid=(l+r)>>1;
        if(pos<=mid){
            ls[rt]=add(pos,jobv,l,mid,ls[rt]);
        }
        else{
            rs[rt]=add(pos,jobv,mid+1,r,rs[rt]);
        }
        up(rt);
    }
    return rt;
}

long long query(int jobl,int jobr,int l,int r,int i){
    if(i==0){
        return 0;
    }
    if(jobl<=l&&r<=jobr){
        return sum[i];
    }
    else{
        int mid=(l+r)>>1;
        long long ans=0;
        if(jobl<=mid){
            ans+=query(jobl,jobr,l,mid,ls[i]);
        }
        if(jobr>mid){
            ans+=query(jobl,jobr,mid+1,r,rs[i]);
        }
        return ans;
    }
}

int kth(int jobk,int l,int r,int i){
    if(i==0){
        return -1;
    }
    if(l==r){
        return l;
    }
    else{
        int mid=(l+r)>>1;
        if(sum[ls[i]]>=jobk){
            return kth(jobk,l,mid,ls[i]);
        }
        else{
            return kth(jobk-sum[ls[i]],mid+1,r,rs[i]);
        }
    }
}

int merge(int l,int r,int t1,int t2){
    if(t1==0||t2==0){
        return t1+t2;
    }
    if(l==r){
        sum[t1]+=sum[t2];
    }
    else{
        int mid=(l+r)>>1;
        ls[t1]=merge(l,mid,ls[t1],ls[t2]);
        rs[t1]=merge(mid+1,r,rs[t1],rs[t2]);
        up(t1);
    }
    del(t2);
    return t1;
}

int tree1,tree2;

void split(int jobl,int jobr,int l,int r,int t1){
    if(t1==0){
        tree1=t1;
        tree2=0;
        return ;
    }
    if(jobl<=l&&r<=jobr){
        tree1=0;
        tree2=t1;
        return ;
    }
    int t2=newnode();
    int mid=(l+r)>>1;
    if(jobl<=mid){
        split(jobl,jobr,l,mid,ls[t1]);
        ls[t1]=tree1;
        ls[t2]=tree2;
    }
    if(jobr>mid){
        split(jobl,jobr,mid+1,r,rs[t1]);
        rs[t1]=tree1;
        rs[t2]=tree2;
    }
    up(t1);
    up(t2);
    tree1=t1;
    tree2=t2;
}

int main()
{
    prepare();
    n=read(),m=read();
    version=1;
    for(int i=1;i<=n;i++){
        int x=read();
        root[version]=add(i,x,1,n,root[version]);
    }
    for(int i=1;i<=m;i++){
        int op,x,y,z;
        op=read(),x=read(),y=read();
        if(op==0){
            z=read();
            split(y,z,1,n,root[x]);
            root[x]=tree1;
            root[++version]=tree2;
        }
        else if(op==1){
            root[x]=merge(1,n,root[x],root[y]);
        }
        else if(op==2){
            z=read();
            root[x]=add(z,y,1,n,root[x]);
        }
        else if(op==3){
            z=read();
            cout<<query(y,z,1,n,root[x])<<endl;
        }
        else{
            cout<<kth(y,1,n,root[x])<<endl;
        }
    }
    return 0;
}