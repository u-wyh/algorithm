// 水管局长，C++版
// 一共n个点、m条无向边，给定每条边的两个端点和边权
// 接下来有q条操作，每条操作是如下两种类型中的一种
// 操作 1 x y : 打印点x到点y的所有路径中，最大边权的最小值
// 操作 2 x y : 删除点x和点y之间的直接边，该边一定存在
// 题目保证任何时刻图都连通，并且无重边无自环
// 1 <= n <= 10^3
// 1 <= m、q <= 10^5
// 测试链接 : https://www.luogu.com.cn/problem/P4172
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+1e3+5;

int n,m,q;

struct Edge{
    int x,y,w;
};
Edge edge[MAXN];

int qop[MAXN];
int qx[MAXN];
int qy[MAXN];

int father[MAXN];

bool deleted[MAXN];
map<pair<int,int>,int>edgemap;

int fa[MAXN];
int ls[MAXN];
int rs[MAXN];
bool rev[MAXN];
int sta[MAXN];

int maxedge[MAXN];
int ans[MAXN];

bool cmp(Edge &a,Edge &b){
    return a.w<b.w;
}

int find(int x){
    return x==father[x]?x:father[x]=find(father[x]);
}

pair<int,int> key(int x,int y){
    if(x>y){
        swap(x,y);
    }
    return {x,y};
}

void up(int x){
    maxedge[x]=(x<=n)?0:x-n;
    if(edge[maxedge[ls[x]]].w>edge[maxedge[x]].w){
        maxedge[x]=maxedge[ls[x]];
    }
    if(edge[maxedge[rs[x]]].w>edge[maxedge[x]].w){
        maxedge[x]=maxedge[rs[x]];
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

void prepare(){
    for(int i=1;i<=n;i++){
        father[i]=i;
    }
    sort(edge+1,edge+m+1,cmp);
    for(int i=1;i<=m;i++){
        edgemap[key(edge[i].x,edge[i].y)]=i;
    }
    for(int i=1;i<=q;i++){
        if(qop[i]==2){
            deleted[edgemap[key(qx[i],qy[i])]]=true;
        }
    }
    int edgecnt=0;
    for(int i=1;i<=m&&edgecnt!=n-1;i++){
        if(!deleted[i]){
            int x=edge[i].x;
            int y=edge[i].y;
            int fx=find(x);
            int fy=find(y);
            if(fx!=fy){
                father[fx]=fy;
                link(x,n+i);
                link(y,n+i);
                edgecnt++;
            }
        }
    }
}

void addedge(int e){
    split(edge[e].x,edge[e].y);
    int maxe=maxedge[edge[e].y];
    if(edge[e].w<edge[maxe].w){
        cut(edge[maxe].x,maxe+n);
        cut(edge[maxe].y,maxe+n);
        link(edge[e].x,e+n);
        link(edge[e].y,e+n);
    }
}

int main()
{
    cin>>n>>m>>q;
    for(int i=1;i<=m;i++){
        cin>>edge[i].x>>edge[i].y>>edge[i].w;
    }
    for(int i=1;i<=q;i++){
        cin>>qop[i]>>qx[i]>>qy[i];
    }

    prepare();

    for(int i=q;i>=1;i--){
        if(qop[i]==1){
            split(qx[i],qy[i]);
            ans[i]=edge[maxedge[qy[i]]].w;
        }
        else{
            addedge(edgemap[key(qx[i],qy[i])]);
        }
    }
    for(int i=1;i<=q;i++){
        if(qop[i]==1){
            cout<<ans[i]<<endl;
        }
    }
    return 0;
}