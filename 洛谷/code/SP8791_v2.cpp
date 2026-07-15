#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m;

int fa[MAXN];
int ls[MAXN];
int rs[MAXN];

bool isroot(int x) {
    return ls[fa[x]] != x && rs[fa[x]] != x;
}

int lr(int x) {
    return ls[fa[x]] == x ? 0 : 1;
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
}

void splay(int x) {
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

int access(int x){
    int ans=0;
    for(ans=0;x!=0;ans=x,x=fa[x]){
        splay(x);
        rs[x]=ans;
        ans=x;
    }
    return ans;
}

void makeson(int x,int y){
    access(x);
    splay(x);
    fa[x]=y;
}

void cut(int x){
    access(x);
    splay(x);
    fa[ls[x]]=0;
    ls[x]=0;
}

int lca(int x,int y){
    if(x==y){
        return x;
    }
    access(x);
    return access(y);
}

int main()
{
    cin>>n>>m;
    for(int i=1,x,y;i<=m;i++){
        string s;
        cin>>s;
        if(s=="link"){
            cin>>x>>y;
            makeson(x,y);
        }
        else if(s=="cut"){
            cin>>x;
            cut(x);
        }
        else{
            cin>>x>>y;
            cout<<lca(x,y)<<endl;
        }
    }
    return 0;
}