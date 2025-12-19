#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m;
int val[MAXN];

int maxx[MAXN<<2];
int maxval[MAXN<<2];
bool vis[MAXN<<2];
int addval[MAXN<<2],maxadd[MAXN<<2];
int upval[MAXN<<2],maxup[MAXN<<2];

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
    maxx[i]=max(maxx[i<<1],maxx[i<<1|1]);
    maxval[i]=max(maxval[i<<1],maxval[i<<1|1]);
}

void build(int l,int r,int i){
    if(l==r){
        maxval[i]=val[l];
        maxx[i]=val[l];
    }
    else{
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

void addlazy(int i,int v,int val){
    maxval[i]=max(maxval[i],maxx[i]+val);
    maxx[i]+=v;
    if(vis[i]){
        maxup[i]=max(maxup[i],upval[i]+val);
        upval[i]+=v;
    }
    else{
        maxadd[i]=max(maxadd[i],addval[i]+val);
        addval[i]+=v;
    }
}

void updatelazy(int i,int v,int val){
    if(vis[i]){
        maxup[i]=max(maxup[i],val);
    }
    else{
        vis[i]=true;
        maxup[i]=val;
    }
    maxval[i]=max(maxval[i],val);
    maxx[i]=v,upval[i]=v,addval[i]=0;
}

void down(int i){
    addlazy(i<<1,addval[i],maxadd[i]);
    addlazy(i<<1|1,addval[i],maxadd[i]);
    addval[i]=maxadd[i]=0;

    if(vis[i]){
        vis[i]=false;
        updatelazy(i<<1,upval[i],maxup[i]);
        updatelazy(i<<1|1,upval[i],maxup[i]);
        upval[i]=maxup[i]=0;
    }
}

int query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return maxx[i];
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        int ans=INT_MIN;
        if(jobl<=mid){
            ans=max(ans,query(jobl,jobr,l,mid,i<<1));
        }
        if(jobr>mid){
            ans=max(ans,query(jobl,jobr,mid+1,r,i<<1|1));
        }
        return ans;
    }
}

int querymax(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return maxval[i];
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        int ans=INT_MIN;
        if(jobl<=mid){
            ans=max(ans,querymax(jobl,jobr,l,mid,i<<1));
        }
        if(jobr>mid){
            ans=max(ans,querymax(jobl,jobr,mid+1,r,i<<1|1));
        }
        return ans;
    }
}

void add(int jobl,int jobr,int jobv,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        addlazy(i,jobv,jobv);
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

void update(int jobl,int jobr,int jobv,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        updatelazy(i,jobv,jobv);
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

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&val[i]);
    }
    build(1,n,1);
    scanf("%d",&m);
    for(int i=1;i<=m;i++){
        char op;
        int l,r,v;
        scanf(" %c %d %d",&op,&l,&r);
        if(op=='Q'){
            printf("%d\n",query(l,r,1,n,1));
        }
        else if(op=='A'){
            printf("%d\n",querymax(l,r,1,n,1));
        }
        else if(op=='P'){
            scanf("%d",&v);
            add(l,r,v,1,n,1);
        }
        else{
            scanf("%d",&v);
            update(l,r,v,1,n,1);
        }
    }
    return 0;
}