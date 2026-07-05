#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n,m;
int val[MAXN];

int fa[MAXN];
int ls[MAXN];
int rs[MAXN];
bool rev[MAXN];
int sta[MAXN];
long long sum[MAXN];

int tail[MAXN];

void up(int x){
    sum[x]=sum[ls[x]]+sum[rs[x]]+val[x];
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

void link(int x,int y){
    fa[y]=x;
}

// void cut(int x,int y){
//     int rx=findroot(y);
//     makeroot(y);
//     down(y);
//     fa[ls[y]]=0;
//     ls[y]=0;
//     up(y);
//     makeroot(rx);
// }

void cut(int x,int y){
    int rx = findroot(y);

    makeroot(x);
    access(y);
    splay(y);

    ls[y] = 0;
    fa[x] = 0;
    up(y);

    makeroot(rx);
}

int pre(int x) {
    access(x);
    splay(x);

    int p = ls[x];

    down(p);
    while (rs[p]) {
        p = rs[p];
        down(p);
    }

    splay(p);
    return p;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>val[i];
        sum[i]=val[i];
        tail[i]=i;
    }
    for(int i=1;i<=m;i++){
        char op;
        int x,y;
        cin>>op;
        if(op=='M'){
            cin>>x>>y;
            swap(x,y);

            int rx=findroot(x);
            int ry=findroot(y);
            if(rx==ry){
                continue;
            }
            link(tail[rx],ry);
            tail[rx]=tail[ry];
        }
        else if(op=='D'){
            cin>>x;
            int rx=findroot(x);
            if(rx==x){
                continue;
            }
            int p=pre(x);
            tail[x]=tail[rx];
            tail[rx]=p;
            cut(p,x);
        }
        else{
            cin>>x>>y;
        
            int rx=findroot(x);
            int ry=findroot(y);
            if(rx!=ry){
                cout<<-1<<endl;
                continue;
            }
            makeroot(x);
            access(y);
            splay(y);
            cout<<sum[y]<<endl;
            makeroot(rx);
        }
    }
    return 0;
}