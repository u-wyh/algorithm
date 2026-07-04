#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m;

int fa[MAXN];
int ls[MAXN];
int rs[MAXN];
int sta[MAXN];
bool rev[MAXN];

bool isroot(int x){
    return ls[fa[x]]!=x&&rs[fa[x]]!=x;
}

int lr(int x){
    return ls[fa[x]]==x?0:1;
}

void reverse(int x){
    if(x!=0){
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
    for(int y=0;x!=0;y=x,x=fa[x]){
        splay(x);
        rs[x]=y;
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
        down(ls[x]);
        x=ls[x];
    }
    splay(x);
    return x;
}

void link(int x,int y){
    makeroot(x);
    if(findroot(y)!=x){
        fa[x]=y;
    }
}

void cut(int x,int y){
    makeroot(x);
    if(findroot(y)==x&&fa[y]==x&&rs[x]==y&&ls[y]==0){
        fa[y]=rs[x]=0;
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        string s;
        int x,y;
        cin>>s>>x>>y;
        if(s=="Connect"){
            link(x,y);
        }
        else if(s=="Destroy"){
            cut(x,y);
        }
        else{
            if(findroot(x)==findroot(y)){
                cout<<"Yes"<<endl;
            }
            else{
                cout<<"No"<<endl;
            }
        }
    }
    return 0;
}