#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int MAXM = 1e5+5;
const int INF = 1e9;

int n,m;

struct Edge{
    int x,y,a,b;
};
Edge edge[MAXM];

int fa[MAXN];
int ls[MAXN];
int rs[MAXN];
bool rev[MAXN];
int sta[MAXN];

int maxaedge[MAXN];
int maxbedge[MAXN];

void up(int x){
    maxaedge[x] = x <= n ? 0 : x - n;
   if (edge[maxaedge[ls[x]]].a > edge[maxaedge[x]].a) {
       maxaedge[x] = maxaedge[ls[x]];
   }
   if (edge[maxaedge[rs[x]]].a > edge[maxaedge[x]].a) {
       maxaedge[x] = maxaedge[rs[x]];
   }
   maxbedge[x] = x <= n ? 0 : x - n;
   if (edge[maxbedge[ls[x]]].b > edge[maxbedge[x]].b) {
       maxbedge[x] = maxbedge[ls[x]];
   }
   if (edge[maxbedge[rs[x]]].b > edge[maxbedge[x]].b) {
       maxbedge[x] = maxbedge[rs[x]];
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

bool cmp(Edge &a,Edge &b){
    return a.a<b.a;
}

int compute(){
    sort(edge+1,edge+m+1,cmp);
    int ans=INF;
    for(int i=1;i<=m;i++){
        int x=edge[i].x;
        int y=edge[i].y;
        if(x!=y){
            makeroot(x);
            if(findroot(y)!=x){
                link(x,n+i);
                link(y,n+i);
            }
            else{
                split(x,y);
                int pre=maxbedge[y];
                if(edge[i].b<edge[pre].b){
                    cut(edge[pre].x,pre+n);
                    cut(edge[pre].y,pre+n);
                    link(x,n+i);
                    link(y,n+i);
                }
            }
        }

        makeroot(1);
        if(findroot(n)==1){
            split(1,n);
            ans=min(ans,edge[maxaedge[n]].a+edge[maxbedge[n]].b);
        }
    }
    return ans==INF?-1:ans;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>edge[i].x>>edge[i].y>>edge[i].a>>edge[i].b;
    }
    cout<<compute()<<endl;
    return 0;
}