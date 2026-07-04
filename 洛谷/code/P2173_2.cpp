#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m,C,q;

int fa[MAXN];
int ls[MAXN];
int rs[MAXN];
int sta[MAXN];
bool rev[MAXN];

int arr[MAXN];
int maxv[MAXN];

int nodedegree[MAXN];
map<pair<int,int>,int>edgecolor;

void up(int x){
    maxv[x]=max(arr[x],max(maxv[ls[x]],maxv[rs[x]]));
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
    }
}

void cut(int x,int y){
    makeroot(x);
    if(findroot(y)==x&&fa[y]==x&&ls[y]==0&&rs[x]==y){
        fa[y]=rs[x]=0;
        up(x);
    }
}

int node(int c,int x){
    return c*n+x;
}

pair<int,int>edge(int x,int y){
    int a=min(x,y);
    int b=max(x,y);
    return {a,b};
}

void connect(int c,int x,int y){
    int u=node(c,x);
    int v=node(c,y);
    nodedegree[u]++;
    nodedegree[v]++;
    link(u,v);
    edgecolor[edge(x,y)]=c;
}

void disconnect(int c,int x,int y){
    edgecolor.erase(edge(x,y));
    x=node(c,x);
    y=node(c,y);
    nodedegree[x]--;
    nodedegree[y]--;
    cut(x,y);
}

void updatenode(int x,int v){
    for(int c=0;c<C;c++){
        int u=node(c,x);
        splay(u);
        arr[u]=v;
        up(u);
    }
}

int updateedge(int x,int y,int c){
    auto it=edgecolor.find(edge(x,y));
    if(it==edgecolor.end()){
        return 3;
    }
    int p=it->second;
    if(p==c){
        return 4;
    }
    if(nodedegree[node(c,x)]>=2||nodedegree[node(c,y)]>=2){
        return 1;
    }
    if(findroot(node(c,x))==findroot(node(c,y))){
        return 2;
    }
    disconnect(p,x,y);
    connect(c,x,y);
    return 4;
}

int query(int c,int x,int y){
    int u=node(c,x);
    int v=node(c,y);
    if(findroot(u)!=findroot(v)){
        return -1;
    }
    split(u,v);
    return maxv[v];
}

int main()
{
    cin>>n>>m>>C>>q;
    for(int i=1;i<=n;i++){
        int v;
        cin>>v;
        for(int c=0;c<C;c++){
            int cur=node(c,i);
            arr[cur]=v;
            maxv[cur]=v;
        }
    }
    for(int i=1;i<=m;i++){
        int x,y,c;
        cin>>x>>y>>c;
        connect(c,x,y);
    }
    for(int i=1;i<=q;i++){
        int op,x,y,c;
        cin>>op;
        if(op==0){
            cin>>x>>y;
            updatenode(x,y);
        }
        else if(op==1){
            cin>>x>>y>>c;
            int ans=updateedge(x,y,c);
            if(ans==1){
                cout<<"Error 1."<<endl;
            }
            else if(ans==2){
                cout<<"Error 2."<<endl;
            }
            else if(ans==3){
                cout<<"No such edge."<<endl;
            }
            else{
                cout<<"Success."<<endl;
            }
        }
        else{
            cin>>c>>x>>y;
            cout<<query(c,x,y)<<endl;
        }
    }
    return 0;
}