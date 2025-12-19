#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 2e6+5;

int n,m,q;
int ans;
int val[MAXN];

int need[MAXN];

int tree[MAXN<<2];

int head[MAXN<<2];
int nxt[MAXM];
int to[MAXM];
int cnt=1;

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
    tree[i]=tree[i<<1]+tree[i<<1|1];
}

void build(int l,int r,int i){
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

inline void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void add(int jobl,int jobr,int jobv,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        addedge(i,jobv);
        need[jobv]++;
    }
    else{
        int mid=(l+r)>>1;
        if(jobl<=mid){
            add(jobl,jobr,jobv,l,mid,i<<1);
        }
        if(jobr>mid){
            add(jobl,jobr,jobv,mid+1,r,i<<1|1);
        }
    }
}

void update(int pos,int l,int r,int i){
    if(tree[i]==0){
        return ;
    }
    if(l==r){
        tree[i]--;
        if(tree[i]==0){
            for(int ei=head[i];ei;ei=nxt[ei]){
                int v=to[ei];
                need[v]--;
                if(need[v]==0){
                    ans++;
                }
            }
        }
    }
    else{
        int mid=(l+r)>>1;
        if(pos<=mid){
            update(pos,l,mid,i<<1);
        }
        else{
            update(pos,mid+1,r,i<<1|1);
        }
        up(i);
        if(tree[i]==0){
            for(int ei=head[i];ei;ei=nxt[ei]){
                int v=to[ei];
                need[v]--;
                if(need[v]==0){
                    ans++;
                }
            }
        }
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
        int l=read(),r=read();
        add(l,r,i,1,n,1);
    }
    q=read();
    int lastans=0;
    while(q--){
        int x=read();
        x=(x+lastans-1)%n+1;
        update(x,1,n,1);
        printf("%d\n",ans);
        lastans=ans;
    }
    return 0;
}