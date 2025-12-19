#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;
const int INF = 2e9;

int n,m;
int val[MAXN];

int tree[MAXN<<2];
int mintag[MAXN<<2];
int maxtag[MAXN<<2];
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
    tree[i]=max(tree[i<<1],tree[i<<1|1]);
}

void build(int l,int r,int i){
    mintag[i]=INF;
    maxtag[i]=-INF;
    if(l==r){
        tree[i]=val[l];
    }
    else{
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

void addlazy(int i,int v){
    tree[i]+=v;
    tag[i]+=v;
    if(mintag[i]<INF){
        mintag[i]+=v;
    }
    if(maxtag[i]>-INF){
        maxtag[i]+=v;
    }
}

void minlazy(int i,int v){
    tree[i]=min(tree[i],v);
    mintag[i]=min(mintag[i],v);
    maxtag[i]=min(maxtag[i],v);
}

void maxlazy(int i,int v){
    tree[i]=max(tree[i],v);
    mintag[i]=max(mintag[i],v);
    maxtag[i]=max(maxtag[i],v);
}

void down(int i){
    if(tag[i]){
        addlazy(i<<1,tag[i]);
        addlazy(i<<1|1,tag[i]);
        tag[i]=0;
    }
    if(mintag[i]!=INF){
        minlazy(i<<1,mintag[i]);
        minlazy(i<<1|1,mintag[i]);
        mintag[i]=INF;
    }
    if(maxtag[i]!=-INF){
        maxlazy(i<<1,maxtag[i]);
        maxlazy(i<<1|1,maxtag[i]);
        maxtag[i]=-INF;
    }
}

int query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return tree[i];
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        int ans=-INF;
        if(jobl<=mid){
            ans=max(ans,query(jobl,jobr,l,mid,i<<1));
        }
        if(jobr>mid){
            ans=max(ans,query(jobl,jobr,mid+1,r,i<<1|1));
        }
        return ans;
    }
}

void add(int jobl,int jobr,int jobv,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        addlazy(i,jobv);
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
        up(i);
    }
}

void updatemin(int jobl,int jobr,int jobv,int l,int r,int i){
    if(jobv>mintag[i]){
        return ;
    }
    if(jobl<=l&&r<=jobr){
        minlazy(i,jobv);
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        if(jobl<=mid){
            updatemin(jobl,jobr,jobv,l,mid,i<<1);
        }
        if(jobr>mid){
            updatemin(jobl,jobr,jobv,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

void updatemax(int jobl,int jobr,int jobv,int l,int r,int i){
    if(jobv<maxtag[i]){
        return ;
    }
    if(jobl<=l&&r<=jobr){
        maxlazy(i,jobv);
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        if(jobl<=mid){
            updatemax(jobl,jobr,jobv,l,mid,i<<1);            
        }
        if(jobr>mid){
            updatemax(jobl,jobr,jobv,mid+1,r,i<<1|1);            
        }
        up(i);
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    build(1,n,1);
    for(int i=1;i<=m;i++){
        int op,l,r,h;
        op=read(),l=read(),r=read();
        if(op==1){
            h=read();
            add(l,r,h,1,n,1);
        }
        else if(op==2){
            h=read();
            updatemin(l,r,h,1,n,1);
        }
        else if(op==3){
            h=read();
            updatemax(l,r,h,1,n,1);
        }
        else{
            printf("%d\n",query(l,r,1,n,1));
        }
    }
    return 0;
}