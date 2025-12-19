#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXL = MAXN*2;
const int MAXH = 20;

int n,q,p;
int val[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

int dep[MAXN];
int euler[MAXL];
int first[MAXN];
int dfncnt;
int lg[MAXL];
int st[MAXL][MAXH];

struct node{
    int l,r;
    int d;
};
node tree[MAXN<<2];

inline void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void dfs(int u,int fa){
    dep[u]=dep[fa]+1;
    first[u]=++dfncnt;
    euler[dfncnt]=u;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa){
            dfs(v,u);
            euler[++dfncnt]=u;
        }
    }
}

void prepare(){
    int m=dfncnt;
    lg[0]=-1;
    for(int i=1;i<=m;i++){
        lg[i]=lg[i>>1]+1;
    }
    for(int i=1;i<=m;i++){
        st[i][0]=euler[i];
    }
    for(int j=1;j<=lg[m];j++){
        for(int i=1;i+(1<<j)-1<=m;i++){
            int a=st[i][j-1];
            int b=st[i+(1<<(j-1))][j-1];
            st[i][j]=(dep[a]<dep[b])?a:b;
        }
    }
}

inline int lca(int a,int b){
    int l=first[a],r=first[b];
    if(l>r){
        swap(l,r);
    }
    int j=lg[r-l+1];
    a=st[l][j];
    b=st[r-(1<<j)+1][j];
    return dep[a]<dep[b]?a:b;
}

int dist(int a,int b){
    return dep[a]+dep[b]-2*dep[lca(a,b)];
}

node merge(node a,node b){
    if(a.d==-1){
        return b;
    }
    if(b.d==-1){
        return a;
    }

    node res;
    if(a.d>b.d){
        res=a;
    }
    else{
        res=b;
    }

    int d=dist(a.l,b.l);
    if(d>res.d){
        res={a.l,b.l,d};
    }
    d=dist(a.l,b.r);
    if(d>res.d){
        res={a.l,b.r,d};
    }
    d=dist(a.r,b.l);
    if(d>res.d){
        res={a.r,b.l,d};
    }
    d=dist(a.r,b.r);
    if(d>res.d){
        res={a.r,b.r,d};
    }
    return res;
}

void build(int l,int r,int i){
    if(l==r){
        tree[i]={l,l,0};
    }
    else{
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        tree[i]=merge(tree[i<<1],tree[i<<1|1]);
    }
}

void update(int pos,int l,int r,int i){
    if(l==r){
        if(val[l]==0){
            tree[i]={l,l,0};
        }
        else{
            tree[i]={l,l,-1};
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
        tree[i]=merge(tree[i<<1],tree[i<<1|1]);
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    p=log2(n)+2;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
    }
    dfs(1,0);
    prepare();
    build(1,n,1);
    cin>>q;
    while(q--){
        char op;
        cin>>op;
        if(op=='G'){
            cout<<tree[1].d<<endl;
        }
        else{
            int x;
            cin>>x;
            val[x]=1-val[x];
            update(x,1,n,1);
        }
    }
    return 0;
}