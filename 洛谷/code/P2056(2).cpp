#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXL = MAXN*2;
const int MAXM = 5e5+5;
const int MAXT = 2e7+5;
const int MAXH = 20;

int n,q,p;
int val[MAXN];
int t[MAXN];

char op[MAXM];
int x[MAXM];
int ans[MAXM];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

int headp[MAXM<<2];
int nxtp[MAXT];
int top[MAXT];
int cntp=1;

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
node backup[MAXH];
node res;

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

void pre(){
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

inline void addEdge(int u,int v){
    nxtp[cntp]=headp[u];
    top[cntp]=v;
    headp[u]=cntp++;
}

void add(int jobl,int jobr,int jobv,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        addEdge(i,jobv);
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

void prepare(){
    dfs(1,0);
    pre();
    for(int i=1;i<=n;i++){
        t[i]=1;
    }
    for(int i=2;i<=q+1;i++){
        if(op[i]=='C'){
            val[x[i]]^=1;
            if(val[x[i]]==1){
                add(t[x[i]],i-1,x[i],1,q+1,1);
            }
            else{
                t[x[i]]=i;
            }
        }
    }
    for(int i=1;i<=n;i++){
        if(val[i]==0){
            add(t[i],q+1,i,1,q+1,1);
        }
    }
    res={0,0,-1};
}

void update(int v){
    if(res.d==-1){
        res={v,v,0};
        return ;
    }
    
    int d1=dist(v,res.l);
    int d2=dist(v,res.r);
    if(d1>d2){
        if(d1>res.d){
            res={v,res.l,d1};
        }
    }
    else{
        if(d2>res.d){
            res={v,res.r,d2};
        }
    }
}

void dfs(int l,int r,int i,int dep){
    backup[dep]=res;
    for(int ei=headp[i];ei;ei=nxtp[ei]){
        int v=top[ei];
        update(v);
    }
    if(l==r){
        if(op[l]=='G'){
            ans[l]=res.d;
        }
    }
    else{
        int mid=(l+r)>>1;
        dfs(l,mid,i<<1,dep+1);
        dfs(mid+1,r,i<<1|1,dep+1);
    }
    res=backup[dep];
}

int main()
{
    scanf("%d",&n);
    p=log2(n)+2;
    for(int i=1;i<n;i++){
        int u,v;
        scanf("%d %d",&u,&v);
        addedge(u,v);
        addedge(v,u);
    }
    cin>>q;
    for(int i=2;i<=q+1;i++){
        scanf(" %c",&op[i]);
        if(op[i]=='C'){
            scanf("%d",&x[i]);
        }
    }
    prepare();
    dfs(1,q+1,1,1);
    for(int i=2;i<=q+1;i++){
        if(op[i]=='G'){
            printf("%d\n",ans[i]);
        }
    }
    return 0;
}