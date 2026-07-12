#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m;
int val[MAXN];

int fa[MAXN];
int ls[MAXN];
int rs[MAXN];

bool rev[MAXN];
int sta[MAXN];
int eorval[MAXN];

void up(int x){
    eorval[x]=eorval[ls[x]]^eorval[rs[x]]^val[x];
}

bool isroot(int x){
    return ls[fa[x]]!=x&&rs[fa[x]]!=x;
}

int lr(int x){
    return ls[fa[x]]==x?0:1;
}

void reverse(int x){
    if(x){
        swap(ls[x],rs[x]);
        rev[x]=!rev[x];
    }
}

void down(int x){
    if(rev[x]){
        reverse(ls[x]);
        reverse(rs[x]);
        rev[x]=false;
    }
}

void rotate(int x){
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
    int sz=0;
    sta[++sz]=x;
    for(int y=x;!isroot(y);y=fa[y]){
        sta[++sz]=fa[y];
    }
    while(sz){
        down(sta[sz--]);
    }
    while(!isroot(x)){
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
    for(int y=0;x!=0;y=x,x=fa[x]){
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
    while(ls[x]!=0){
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
    }
}

void cut(int x,int y){
    makeroot(x);
    if(findroot(y)==x&&fa[y]==x&&ls[y]==0&&rs[x]==y){
        fa[y]=rs[x]=0;
        up(x);
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>val[i];
        eorval[i]=val[i];
    }
    for(int i=1;i<=m;i++){
        int op,x,y;
        cin>>op>>x>>y;
        if(op==0){
            split(x,y);
            cout<<eorval[y]<<endl;
        }
        else if(op==1){
            link(x,y);
        }
        else if(op==2){
            cut(x,y);
        }
        else{
            splay(x);
            val[x]=y;
            up(x);
        }
    }
    return 0;
}