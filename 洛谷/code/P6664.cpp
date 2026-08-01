#include<bits/stdc++.h>
using namespace std;
const int MAXN = 4e5+5;
const int INF = 1e9;

int n,m;

int ex[MAXN];
int ey[MAXN];
int et[MAXN];
int el[MAXN];

int fa[MAXN];
int ls[MAXN];
int rs[MAXN];
bool rev[MAXN];
int sta[MAXN];

int sum[MAXN];
int mintedge[MAXN];

void up(int x){
    int e=x<=n?0:x-n;
    sum[x]=sum[ls[x]]+sum[rs[x]]+el[e];
    mintedge[x]=e;
    if (et[mintedge[ls[x]]] < et[mintedge[x]]) {
        mintedge[x] = mintedge[ls[x]];
    }
    if (et[mintedge[rs[x]]] < et[mintedge[x]]) {
        mintedge[x] = mintedge[rs[x]];
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

void addedge(int e){
    int x=ex[e];
    int y=ey[e];
    makeroot(x);
    if(findroot(y)!=x){
        link(x,n+e);
        link(y,n+e);
    }
    else{
        split(x,y);
        int pre=mintedge[y];
        if(et[pre]<et[e]){
            cut(ex[pre],n+pre);
            cut(ey[pre],n+pre);
            link(x,n+e);
            link(y,n+e);
        }
    }
}

void change(int e,int l){
    splay(e+n);
    el[e]=l;
    up(n+e);
}

int query(int x,int y){
    makeroot(x);
    if(findroot(y)!=x){
        return -1;
    }
    split(x,y);
    return sum[y];
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin>>n>>m;
    et[0]=INF;
    for(int i=1;i<=m;i++){
        string op;
        cin>>op;
        if(op=="find"){
            int e,x,y,t,l;
            cin>>e>>x>>y>>t>>l;
            e++,x++,y++;
            ex[e]=x;
            ey[e]=y;
            et[e]=t;
            el[e]=l;
            addedge(e);
        }
        else if(op=="move"){
            int x,y;
            cin>>x>>y;
            x++,y++;
            cout<<query(x,y)<<endl;
        }
        else{
            int e,l;
            cin>>e>>l;
            e++;
            change(e,l);
        }
    }
    return 0;
}