#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MOD = 51061;

int n,m;

int fa[MAXN];
int ls[MAXN];
int rs[MAXN];
int sta[MAXN];

int val[MAXN];
int sum[MAXN];
int sz[MAXN];

bool rev[MAXN];
int addv[MAXN];
int mulv[MAXN];

void up(int x){
    sz[x]=(sz[ls[x]]+sz[rs[x]]+1)%MOD;
    sum[x]=(sum[ls[x]]+sum[rs[x]]+val[x])%MOD;
}

bool isroot(int x) {
    return ls[fa[x]] != x && rs[fa[x]] != x;
}

int lr(int x) {
    return ls[fa[x]] == x ? 0 : 1;
}

void reverse(int x){
    if(x){
        swap(ls[x],rs[x]);
        rev[x]=!rev[x];
    }
}

void addlazy(int x,int v){
    if(x){
        val[x]=(val[x]+v)%MOD;
        sum[x]=(sum[x]+1ll*v*sz[x])%MOD;
        addv[x]=(addv[x]+v)%MOD;
    }
}

void mullazy(int x,int v){
    if(x){
        val[x]=(1ll*val[x]*v)%MOD;
        sum[x]=(1ll*sum[x]*v)%MOD;
        mulv[x]=(1ll*mulv[x]*v)%MOD;
        addv[x]=(1ll*addv[x]*v)%MOD;
    }
}

void down(int x){
    if(x){
        if(rev[x]){
            reverse(ls[x]);
            reverse(rs[x]);
            rev[x]=false;
        }

        if(mulv[x]!=1){
            mullazy(ls[x],mulv[x]);
            mullazy(rs[x],mulv[x]);
            mulv[x]=1;
        }

        if(addv[x]){
            addlazy(ls[x],addv[x]);
            addlazy(rs[x],addv[x]);
            addv[x]=0;
        }
    }
}

void rotate(int x) {
    int f = fa[x];
    int g = fa[f];

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
    int top = 0;
    sta[++top] = x;

    for (int y = x; !isroot(y); y = fa[y]) {
        sta[++top] = fa[y];
    }

    while (top != 0) {
        down(sta[top--]);
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

    up(x);
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
    if(findroot(y)!=x){
        fa[x]=y;
        up(y);
    }
}

void cut(int x,int y){
    makeroot(x);
    if(findroot(y)==x&&fa[y]==x&&ls[y]==0&&rs[x]==y){
        rs[x]=fa[y]=0;
        up(x);
    }
}

void path_add(int x,int y,int v){
    split(x,y);
    addlazy(y,v%MOD);
}

void path_mul(int x,int y,int v){
    split(x,y);
    mullazy(y,v%MOD);
}

int path_query(int x,int y){
    split(x,y);
    return sum[y];
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;

    for(int i=1;i<=n;i++){
        val[i]=1;
        sum[i]=1;
        sz[i]=1;
        addv[i]=0;
        mulv[i]=1;
    }

    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        link(u,v);
    }

    for(int i=1;i<=m;i++){
        string op;
        cin>>op;
        if(op=="+"){
            int u,v,c;
            cin>>u>>v>>c;
            path_add(u,v,c);
        }
        else if(op=="-"){
            int u1,v1,u2,v2;
            cin>>u1>>v1>>u2>>v2;
            cut(u1,v1);
            link(u2,v2);
        }
        else if(op=="*"){
            int u,v,c;
            cin>>u>>v>>c;
            path_mul(u,v,c);
        }
        else{
            int u,v;
            cin>>u>>v;
            cout<<path_query(u,v)<<endl;
        }
    }
    return 0;
}