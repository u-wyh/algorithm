// https://www.luogu.com.cn/problem/P10659
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e4+5;
const int INF = 1e15;

int n,m,root;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cntg=1;

int fa[MAXN];
int dep[MAXN];
int sz[MAXN];
int son[MAXN];
int dfncnt;
int dfn[MAXN];
int seg[MAXN];
int top[MAXN];

int cnt;
int ls[MAXN];
int rs[MAXN];
double priority[MAXN];

int val[MAXN];
int sum[MAXN];
int maxx[MAXN];
int minn[MAXN];

int add[MAXN];
bool rev[MAXN];

int lt[20];
int rt[20];

void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

void dfs1(int u,int f){
    sz[u]=1;
    fa[u]=f;
    dep[u]=dep[f]+1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=f){
            dfs1(v,u);
            sz[u]+=sz[v];
            if(sz[v]>sz[son[u]]){
                son[u]=v;
            }
        }
    }
}

void dfs2(int u,int t){
    top[u]=t;
    dfn[u]=++dfncnt;
    seg[dfncnt]=dfn[u];
    if(son[u]){
        dfs2(son[u],t);
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa[u]&&v!=son[u]){
            dfs2(v,v);
        }
    }
}

void up(int i) {
    sz[i] = sz[ls[i]] + sz[rs[i]] + 1;
    sum[i]=sum[ls[i]]+sum[rs[i]]+val[i];
    maxx[i]=max(val[i],max(maxx[ls[i]],maxx[rs[i]]));
    minn[i]=min(val[i],min(minn[ls[i]],minn[rs[i]]));
}

void addlazy(int i,int v){
    if(i==0){
        return ;
    }
    val[i]+=v;
    sum[i]+=v*sz[i];
    add[i]+=v;
    maxx[i]+=v;
    minn[i]+=v;
}

//懒更新的下发
void down(int i) {
    if (rev[i]) {
        swap(ls[i], rs[i]);
        rev[ls[i]] ^= 1;
        rev[rs[i]] ^= 1;
        rev[i] = false;
    }
    if(add[i]){
        addlazy(ls[i],add[i]);
        addlazy(rs[i],add[i]);
        add[i]=0;
    }
}

//这道题也是根据排名分裂
//这道题利用的也是位置信息 所以使用排名
//使用中序遍历得到答案
void split(int l, int r, int i, int rank) {
    if (i == 0) {
        rs[l] = ls[r] = 0;
    } else {
        down(i);
        if (sz[ls[i]] + 1 <= rank) {
            rs[l] = i;
            split(i, r, rs[i], rank - sz[ls[i]] - 1);
        } else {
            ls[r] = i;
            split(l, i, ls[i], rank);
        }
        up(i);
    }
}

int merge(int l, int r) {
    if (l == 0 || r == 0) {
        return l + r;
    }
    if (priority[l] >= priority[r]) {
        down(l);//下发懒信息
        rs[l] = merge(rs[l], r);
        up(l);
        return l;
    } else {
        down(r);
        ls[r] = merge(l, ls[r]);
        up(r);
        return r;
    }
}

void update(int lt,int rt,int v){
    split(0,0,root,rt);
    int lm=rs[0];
    int r=ls[0];
    split(0,0,lm,lt-1);
    int l=rs[0];
    int m=ls[0];
    addlazy(m,v);
    root=merge(merge(l,m),r);
}

void query(int x,int y,int op){
    int anssum=0;
    int ansmax=-INF;
    int ansmin=INF;

    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]]){
            swap(x,y);
        }
        split(0,0,root,dfn[x]);
        int lm=rs[0];
        int r=ls[0];
        split(0,0,lm,dfn[top[x]]-1);
        int l=rs[0];
        int m=ls[0];

        anssum+=sum[m];
        ansmax=max(ansmax,maxx[m]);
        ansmin=min(ansmin,minn[m]);
        root=merge(merge(l,m),r);
        x=fa[top[x]];
    }
    if(dep[x]<dep[y]){
        swap(x,y);
    }
    split(0,0,root,dfn[x]);
    int lm=rs[0];
    int r=ls[0];
    split(0,0,lm,dfn[y]-1);
    int l=rs[0];
    int m=ls[0];
    anssum+=sum[m];
    ansmax=max(ansmax,maxx[m]);
    ansmin=min(ansmin,minn[m]);
    root=merge(merge(l,m),r);

    if(op==1){
        cout<<anssum<<endl;
    }
    else if(op==2){
        cout<<ansmax<<endl;
    }
    else{
        cout<<ansmin<<endl;
    }
}

void change(int x,int y,int v){
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]]){
            swap(x,y);
        }
        update(dfn[top[x]],dfn[x],v);
        x=fa[top[x]];
    }
    update(min(dfn[x],dfn[y]),max(dfn[x],dfn[y]),v);
}

void invert(int x,int y){
    int cnts=0;
    while(top[x]!=top[y]){
        lt[++cnts]=dfn[top[y]];
        rt[cnts]=dfn[y];
        y=fa[top[y]];
    }
    lt[++cnts]=dfn[x];
    rt[cnts]=dfn[y];

    int all=0;
    // 从下面往上剪
    for(int i=1;i<=cnts;i++){
        split(0,0,root,rt[i]);
        int lm=rs[0];
        int r=ls[0];
        split(0,0,lm,lt[i]-1);
        int l=rs[0];
        int mid=ls[0];
        root=merge(l,r);
        all=merge(mid,all);
    }

    rev[all]^=1;
    // 从上面往下重新放回
    for(int i=cnts;i>=1;i--){
        int len=rt[i]-lt[i]+1;
        split(0,0,all,len);
        int mid=rs[0];
        all=ls[0];
        split(0,0,root,lt[i]-1);
        int l=rs[0];
        int r=ls[0];
        root=merge(merge(l,mid),r);
    }
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    srand(time(0));
    cin>>n>>m>>root;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
    }

    dfs1(root,0);
    dfs2(root,root);

    maxx[0]=-INF;
    minn[0]=INF;
    root=0;
    for(int i=1;i<=n;i++){
        ++cnt;
        sz[cnt]=1;
        maxx[cnt]=minn[cnt]=0;
        priority[cnt]=(double)rand()/RAND_MAX;
        root=merge(root,cnt);
    }

    while(m--){
        string op;
        int x,y;
        cin>>op>>x>>y;
        if(op=="Increase"){
            int w;
            cin>>w;
            change(x,y,w);
        }
        else if(op=="Invert"){
            invert(x,y);
        }
        else if(op=="Sum"){
            query(x,y,1);
        }
        else if(op=="Major"){
            query(x,y,2);
        }
        else{
            query(x,y,3);
        }
    }
    return 0;
}