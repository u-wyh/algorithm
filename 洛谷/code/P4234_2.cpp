#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5+5;
const int MAXM = 2e5+5;

int n,m,ans;

struct Edge{
    int u,v,w;
};
Edge edge[MAXM];

int fa[MAXN];
int ls[MAXN];
int rs[MAXN];
bool rev[MAXN];
int sta[MAXN];
int minedge[MAXN];
bool removed[MAXN];

bool cmp(Edge &a,Edge &b){
    return a.w<b.w;
}

void up(int x) {
    int cur = x <= n ? 0 : x - n;
    int l = minedge[ls[x]];
    int r = minedge[rs[x]];
    if (cur == 0 || (l != 0 && l < cur)) {
        cur = l;
    }
    if (cur == 0 || (r != 0 && r < cur)) {
        cur = r;
    }
    minedge[x] = cur;
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

void compute(){
    edge[0].w=100000;
    ans=1e4+5;
    sort(edge+1,edge+m+1,cmp);
    int edgecnt=0;
    int first=1;
    for(int i=1;i<=m;i++){
        int x=edge[i].u;
        int y=edge[i].v;
        if(x==y){
            removed[i]=true;
        }
        else{
            makeroot(x);
            if(findroot(y)==x){
                split(x,y);
                int old=minedge[y];
                removed[minedge[y]]=true;
                cut(edge[old].u,old+n);
                cut(edge[old].v,old+n);
                link(x,i+n);
                link(y,i+n);
            }
            else{
                edgecnt++;
                link(x,i+n);
                link(y,i+n);
            }
        }
        while(removed[first]){
            first++;
        }
        if(edgecnt==n-1){
            ans=min(ans,edge[i].w-edge[first].w);
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>edge[i].u>>edge[i].v>>edge[i].w;
    }

    compute();

    cout<<ans<<endl;
    return 0;
}