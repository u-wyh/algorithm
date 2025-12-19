#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e6+5;

int n,q;
int val[MAXN];
int fa[MAXN];
int lst[MAXN];
int ans[MAXN];

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int id[MAXN];
int cnt=1;

int tree[MAXN<<2];
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

inline void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    id[cnt]=w;
    head[u]=cnt++;
}

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

void up(int i){
    tree[i]=min(tree[i<<1],tree[i<<1|1]);
}

void lazy(int i,int r,int v){
    tag[i]=v;
    tree[i]=v-r+1;
}

void down(int i,int mid,int r){
    if(tag[i]){
        lazy(i<<1,mid,tag[i]);
        lazy(i<<1|1,r,tag[i]);
        tag[i]=0;
    }
}

void update(int jobl,int jobr,int jobv,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        lazy(i,r,jobv);
    }
    else{
        int mid=(l+r)>>1;
        down(i,mid,r);
        if(jobl<=mid){
            update(jobl,jobr,jobv,l,mid,i<<1);
        }
        if(jobr>mid){
            update(jobl,jobr,jobv,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

int query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return tree[i];
    }
    else{
        int mid=(l+r)>>1;
        down(i,mid,r);
        int ans=INT_MAX;
        if(jobl<=mid){
            ans=min(ans,query(jobl,jobr,l,mid,i<<1));
        }
        if(jobr>mid){
            ans=min(ans,query(jobl,jobr,mid+1,r,i<<1|1));
        }
        return ans;
    }
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    q=read();
    for(int i=1;i<=q;i++){
        int l,r;
        l=read(),r=read();
        addedge(r,l,i);
    }
    for(int i=1;i<=n;i++){
        if(lst[val[i]]){
            update(lst[val[i]]+1,i,i,1,n,1);
            fa[lst[val[i]]]=lst[val[i]]+1;
        }
        else{
            update(1,i,i,1,n,1);
        }
        lst[val[i]]=i;
        for(int ei=head[i];ei;ei=nxt[ei]){
            int l=to[ei];
            int r=find(l);
            ans[id[ei]]=query(l,r,1,n,1);
        }
    }
    for(int i=1;i<=q;i++){
        printf("%d\n",ans[i]);
    }
    return 0;
}