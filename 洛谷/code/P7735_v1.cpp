#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m;
int colcnt;

int fa[MAXN];
int ls[MAXN];
int rs[MAXN];

int col[MAXN];
int lcol[MAXN];
int rcol[MAXN];
int lazy[MAXN];
int cnt[MAXN];
int sz[MAXN];
bool rev[MAXN];
int sta[MAXN];

void clear(){
    for(int i=1;i<=n;i++){
        fa[i]=0;
        ls[i]=0;
        rs[i]=0;
        lazy[i]=0;
        rev[i]=0;
        col[i]=lcol[i]=rcol[i]=i;
        cnt[i]=1;
        sz[i]=1;
    }
    colcnt=n;
}

void up(int x){
    sz[x]=sz[ls[x]]+sz[rs[x]]+1;
    cnt[x]=cnt[ls[x]]+cnt[rs[x]]+1;
    lcol[x]=ls[x]?lcol[ls[x]]:col[x];
    rcol[x]=rs[x]?rcol[rs[x]]:col[x];

    if(ls[x]&&rcol[ls[x]]==col[x]){
        cnt[x]--;
    }
    if(rs[x]&&lcol[rs[x]]==col[x]){
        cnt[x]--;
    }
}

bool isroot(int x){
    return ls[fa[x]]!=x&&rs[fa[x]]!=x;
}

int lr(int x){
    return ls[fa[x]]==x?0:1;
}

void reverse(int x) {
    if (x != 0) {
        swap(ls[x], rs[x]);
        swap(lcol[x],rcol[x]);
        rev[x] = !rev[x];
    }
}

void updatecolor(int x,int v){
    if(x){
        col[x]=lcol[x]=rcol[x]=v;
        cnt[x]=1;
        lazy[x]=v;
    }
}

void down(int x){
    if(lazy[x]){
        updatecolor(ls[x],lazy[x]);
        updatecolor(rs[x],lazy[x]);
        lazy[x]=0;
    }

    if(rev[x]){
        reverse(ls[x]);
        reverse(rs[x]);
        rev[x]=false;
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

void access(int x){
    for(int y=0;x;y=x,x=fa[x]){
        splay(x);
        rs[x]=y;
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
    while(ls[x]){
        x=ls[x];
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
    fa[x]=y;
}

void pathupdate(int x,int y){
    split(x,y);
    updatecolor(y,++colcnt);
}

int pathquery(int x,int y){
    split(x,y);
    return sz[y]-cnt[y];
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin>>T;
    while(T--){
        cin>>n>>m;
        clear();
        for(int i=1;i<n;i++){
            int u,v;
            cin>>u>>v;
            link(u,v);
        }

        for(int i=1;i<=m;i++){
            int op,x,y;
            cin>>op>>x>>y;
            if(op==1){
                pathupdate(x,y);
            }
            else{
                cout<<pathquery(x,y)<<"\n";
            }
        }
    }
    return 0;
}