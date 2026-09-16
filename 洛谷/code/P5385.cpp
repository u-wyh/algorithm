// https://www.luogu.com.cn/problem/P5385
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5+5;
const int MAXE = 2e5+5;
const int MAXT = MAXE*25;
const int INF = 1e9;

int n,m,q,t;

struct Edge{
    int x,y;
};
Edge edge[MAXE];

int fa[MAXN];
int ls[MAXN];
int rs[MAXN];
bool rev[MAXN];
int sta[MAXN];
int minedge[MAXN];
int val[MAXN];

int del[MAXE];
int root[MAXE];
int lson[MAXT];
int rson[MAXT];
int sum[MAXT];
int cntt;

void up(int x){
    minedge[x]=x;
    if(val[minedge[ls[x]]]<val[minedge[x]]){
        minedge[x]=minedge[ls[x]];
    }
    if(val[minedge[rs[x]]]<val[minedge[x]]){
        minedge[x]=minedge[rs[x]];
    }
}

bool isroot(int x) {
    return ls[fa[x]] != x && rs[fa[x]] != x;
}

int lr(int x) {
    return ls[fa[x]] == x ? 0 : 1;
}

void reverse(int x) {
    if (x != 0) {
        swap(ls[x], rs[x]);
        rev[x] = !rev[x];
    }
}

void down(int x) {
    if (rev[x]) {
        reverse(ls[x]);
        reverse(rs[x]);
        rev[x] = false;
    }
}

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
    up(f);
    up(x);
}

void splay(int x){
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

void access(int x){
    for (int y = 0; x != 0; y = x, x = fa[x]) {
        splay(x);
        rs[x] = y;
        up(x);
    }
}

void makeroot(int x){
    access(x);
    splay(x);
    reverse(x);
}

int findroot(int x){
    access(x);
    splay(x);
    down(x);
    while (ls[x] != 0) {
        x = ls[x];
        down(x);
    }
    splay(x);
    return x;
}

void split(int x,int y){
    makeroot(x);
    access(y);
    splay(y);
}

void link(int x,int y){
    makeroot(x);
    if(findroot(y)!=x){
        fa[x]=y;
    }
}

void cut(int x,int y){
    makeroot(x);
    if(findroot(y)==x&&fa[y]==x&&ls[y]==0&&rs[x]==y){
        fa[y]=rs[x]=0;
        up(x);
    }
}

int update(int jobv,int l,int r,int i){
    int rt=++cntt;
    lson[rt]=lson[i];
    rson[rt]=rson[i];
    sum[rt]=sum[i]+1;

    if(l==r){
        return rt;
    }

    int mid=(l+r)>>1;
    if(jobv<=mid){
        lson[rt]=update(jobv,l,mid,lson[rt]);
    }
    else{
        rson[rt]=update(jobv,mid+1,r,rson[rt]);
    }
    return rt;
}

void prepare(){
    val[0]=INF;
    minedge[0]=0;
    for(int i=1;i<=n;i++){
        val[i]=INF;
        minedge[i]=i;
    }

    for(int i=1;i<=m;i++){
        int x=edge[i].x;
        int y=edge[i].y;
        int e=n+i;

        val[e]=i;
        minedge[e]=e;

        if(x==y){
            del[i]=m+1;
        }
        else{
            makeroot(x);
            if(findroot(y)!=x){
                del[i]=0;
                link(x,e);
                link(y,e);
            }
            else{
                split(x,y);
                int oldnode=minedge[y];
                int old=oldnode-n;
                del[i]=old;
                cut(edge[old].x,oldnode);
                cut(edge[old].y,oldnode);
                link(x,e);
                link(y,e);
            }
        }
    }

    for(int i=1;i<=m;i++){
        root[i]=update(del[i],0,m+1,root[i-1]);
    }
}

int query(int jobv,int l,int r,int u,int v){
    if(r<=jobv){
        return sum[u]-sum[v];
    }
    if(l>jobv){
        return 0;
    }
    int mid=(l+r)>>1;
    int ans=0;
    ans+=query(jobv,l,mid,lson[u],lson[v]);
    if(jobv>mid){
        ans+=query(jobv,mid+1,r,rson[u],rson[v]);
    }
    return ans;
}

int main()
{
    cin>>n>>m>>q>>t;
    for(int i=1;i<=m;i++){
        cin>>edge[i].x>>edge[i].y;
    }
    prepare();
    int lastans=0;
    for(int i=1;i<=q;i++){
        int l,r;
        cin>>l>>r;

        if(t>0){
            l=(l+1ll*t*lastans)%m+1;
            r=(r+1ll*t*lastans)%m+1;
        }
        if(l>r){
            swap(l,r);
        }

        lastans=query(l-1,0,m+1,root[r],root[l-1]);
        lastans=n-lastans;
        cout<<lastans<<endl;
    }
    return 0;
}