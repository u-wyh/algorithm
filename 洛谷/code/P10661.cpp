// https://www.luogu.com.cn/problem/P10661
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int MAXH = 20;

int n,m,p;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cntg=1;

int dep[MAXN];
int st[MAXN][MAXH];
int dfncnt;
int dfn[MAXN];
int seg[MAXN];
int sz[MAXN];

int tree[MAXN<<2];
int len[MAXN<<2];
int tag[MAXN<<2];

int fa[MAXN];
int ls[MAXN];
int rs[MAXN];
bool rev[MAXN];
int sta[MAXN];

int root;

inline void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

void dfs(int u,int f){
    dep[u]=dep[f]+1;
    st[u][0]=f;
    for(int i=1;i<=p;i++){
        st[u][i]=st[st[u][i-1]][i-1];
    }
    dfn[u]=++dfncnt;
    seg[dfncnt]=u;
    sz[u]=1;

    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=f){
            dfs(v,u);
            sz[u]+=sz[v];
        }
    }
}

// 判断x是不是y的祖先 
bool isancestor(int x,int y){
    return (dfn[y]>=dfn[x])&&(dfn[x]+sz[x]>dfn[y]);
}

// x是y的子树中节点  找到x距离y的儿子
int gettop(int x,int y){
    for(int i=p;i>=0;i--){
        if(dep[st[x][i]]>dep[y]){
            x=st[x][i];
        }
    }
    return x;
}

void build(int l,int r,int i){
    len[i]=r-l+1;
    if(l==r){
        tree[i]=dep[seg[l]];
    }
    else{
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        tree[i]=tree[i<<1]+tree[i<<1|1];
    }
}

void lazy(int i,int v){
    tree[i]+=v*len[i];
    tag[i]+=v;
}

void down1(int i){
    if(tag[i]){
        lazy(i<<1,tag[i]);
        lazy(i<<1|1,tag[i]);
        tag[i]=0;
    }
}

void add(int jobl,int jobr,int jobv,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        lazy(i,jobv);
    }
    else{
        int mid=(l+r)>>1;
        down1(i);
        if(jobl<=mid){
            add(jobl,jobr,jobv,l,mid,i<<1);
        }
        if(jobr>mid){
            add(jobl,jobr,jobv,mid+1,r,i<<1|1);
        }
        tree[i]=tree[i<<1]+tree[i<<1|1];
    }
}

int query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return tree[i];
    }
    else{
        int mid=(l+r)>>1;
        down1(i);
        int ans=0;
        if(jobl<=mid){
            ans+=query(jobl,jobr,l,mid,i<<1);
        }
        if(jobr>mid){
            ans+=query(jobl,jobr,mid+1,r,i<<1|1);
        }
        return ans;
    }
}

bool isroot(int x) {
    return ls[fa[x]] != x && rs[fa[x]] != x;
}

// x不是辅助splay的顶部节点才能调用，返回x是其父的哪侧儿子
int lr(int x) {
    return ls[fa[x]] == x ? 0 : 1;
}

// 翻转以x为根的辅助splay，交换左右儿子，打上翻转标记
void reverse(int x) {
    if (x != 0) {
        swap(ls[x], rs[x]);
        rev[x] = !rev[x];
    }
}

// 处理翻转懒更新
void down(int x) {
    if (rev[x]) {
        reverse(ls[x]);
        reverse(rs[x]);
        rev[x] = false;
    }
}

// x向上旋转
void rotate(int x) {
    int f = fa[x], g = fa[f];
    if (lr(x) == 0) {
        ls[f] = rs[x];
        if (ls[f] != 0) {
            fa[ls[f]] = f;
        }
        rs[x] = f;
    } else {
        rs[f] = ls[x];
        if (rs[f] != 0) {
            fa[rs[f]] = f;
        }
        ls[x] = f;
    }
    if (!isroot(f)) {
        if (lr(f) == 0) {
            ls[g] = x;
        } else {
            rs[g] = x;
        }
    }
    fa[f] = x;
    fa[x] = g;
}

// x提到辅助splay的顶部
void splay(int x) {
    int siz = 0;
    sta[++siz] = x;
    for (int y = x; !isroot(y); y = fa[y]) {
        sta[++siz] = fa[y];
    }
    while (siz != 0) {
        down(sta[siz--]);
    }
    while (!isroot(x)) {
        int f = fa[x];
        if (!isroot(f)) {
            if (lr(x) == lr(f)) {
                rotate(f);
            } else {
                rotate(x);
            }
        }
        rotate(x);
    }
}

// 在root为根的情况下  给x的子树加上v
void add(int root,int x,int v){
    if(isancestor(root,x)){
        add(dfn[x],dfn[x]+sz[x]-1,v,1,n,1);
    }
    else if(isancestor(x,root)){
        add(1,n,v,1,n,1);
        int u=gettop(root,x);
        add(dfn[u],dfn[u]+sz[u]-1,-v,1,n,1);
    }
    else{
        add(dfn[x],dfn[x]+sz[x]-1,v,1,n,1);
    }
}

// 返回 splay 中深度最小（中序最左）的节点
int leftmost(int x) {
    down(x);
    while (ls[x]) {
        x = ls[x];
        down(x);
    }
    return x;
}

void access(int x) {
    for (int y = 0; x != 0; y = x, x = fa[x]) {
        splay(x);

        if (rs[x]) {
            int t = leftmost(rs[x]);   // 取最左节点
            add(root, t, 1);
        }
        rs[x] = y;
        if (y) {
            int t = leftmost(y);       // 同样取最左
            add(root, t, -1);
        }
    }
}

// void access(int x) {
//     for (int y = 0; x != 0; y = x, x = fa[x]) {
//         splay(x);
//         if(rs[x]){
//             add(root,rs[x],1);
//         }
//         rs[x] = y;
//         if(y){
//             add(root,y,-1);
//         }
//     }
// }

void makeroot(int x) {
    access(x);
    splay(x);
    reverse(x);
}

void prepare(){
    dfs(1,0);
    build(1,n,1);
    for(int i=2;i<=n;i++){
        fa[i]=st[i][0];
    }
    root=1;
}

double request(int x){
    int siz=0;
    int all=0;
    if(isancestor(root,x)){
        siz=sz[x];
        all=query(dfn[x],dfn[x]+sz[x]-1,1,n,1);
    }
    else if(isancestor(x,root)){
        int u=gettop(root,x);
        siz=n-sz[u];
        all=query(1,n,1,n,1);
        all-=query(dfn[u],dfn[u]+sz[u]-1,1,n,1);
    }
    else{
        siz=sz[x];
        all=query(dfn[x],dfn[x]+sz[x]-1,1,n,1);
    }
    return all*1.0/siz;
}

void release(int x){
    access(x);
}

void recenter(int x){
    makeroot(x);
    root=x;
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;
    p=log2(n)+1;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
    }

    prepare();

    cout<<fixed<<setprecision(10);

    while(m--){
        string op;
        int x;
        cin>>op>>x;
        if(op=="REQUEST"){
            cout<<request(x)<<endl;
        }
        else if(op=="RELEASE"){
            release(x);
        }
        else{
            recenter(x);
        }
    }
    return 0;
}