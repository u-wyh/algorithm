#include<bits/stdc++.h>
using namespace std;
const int MAXN = 150005;
const int MAXM = 1e5+5;

int n,m;

int fa[MAXN];
int ls[MAXN];
int rs[MAXN];
int sta[MAXN];
bool rev[MAXN];
int val[MAXN];
int node[MAXN];

struct Edge{
    int x,y,a,b,id;
};
Edge edge[MAXM];

bool cmp(Edge &a,Edge &b){
    if(a.a!=b.a){
        return a.a<b.a;
    }
    return a.b<b.b;
}

void up(int x){
    node[x]=x;
    if(ls[x]&&val[node[x]]<val[node[ls[x]]]){
        node[x]=node[ls[x]];
    }
    if(rs[x]&&val[node[x]]<val[node[rs[x]]]){
        node[x]=node[rs[x]];
    }
}

// 判断节点x是不是辅助splay的顶部节点
bool isroot(int x) {
    return ls[fa[x]] != x && rs[fa[x]] != x;
}

// x不是辅助splay的顶部节点才能调用，返回x是其父的哪侧儿子
int lr(int x) {
    return ls[fa[x]] == x ? 0 : 1;
}

// 翻转以x为根的辅助splay，交换左右儿子，打上翻转标记
void reverse(int x) {
    if (x != 0) {
        swap(ls[x], rs[x]);
        rev[x] = !rev[x];
    }
}

// 处理翻转懒更新
void down(int x) {
    if (rev[x]) {
        reverse(ls[x]);
        reverse(rs[x]);
        rev[x] = false;
    }
}

// x向上旋转
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

// x提到辅助splay的顶部
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
    if(findroot(y)!=x){
        fa[x]=y;
        up(y);
    }
}

void cut(int x,int y){
    makeroot(x);
    if(findroot(x)==findroot(y)&&fa[y]==x&&ls[y]==0&&rs[x]==y){
        rs[x]=fa[y]=0;
        up(x);
    }
}

int query(int x,int y){
    split(x,y);
    return node[y];
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>edge[i].x>>edge[i].y>>edge[i].a>>edge[i].b;
    }
    
    int ans=INT_MAX;
    sort(edge+1,edge+m+1,cmp);
    for(int i=1;i<=n;i++){
        val[i]=0;
        node[i]=i;
    }
    for(int i=1;i<=m;i++){
        val[i+n]=edge[i].b;
        node[i+n]=i+n;
    }

    for(int i=1;i<=m;i++){
        int x=edge[i].x;
        int y=edge[i].y;
        if(x!=y){
            if(findroot(x)!=findroot(y)){
                link(x,i+n);
                link(y,i+n);
            }
            else{
                int oldnode=query(x,y);
                if(val[oldnode]>val[i+n]){
                    cut(oldnode,edge[oldnode-n].x);
                    cut(oldnode,edge[oldnode-n].y);
                    link(i+n,x);
                    link(i+n,y);
                }
            }
        }
        if(findroot(1)==findroot(n)){
            ans=min(ans,edge[i].a+val[query(1,n)]);
        }
    }

    if(ans==INT_MAX){
        ans=-1;
    }
    cout<<ans<<endl;
    return 0;
}