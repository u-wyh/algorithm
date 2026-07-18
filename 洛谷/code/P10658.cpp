#include<bits/stdc++.h>
using namespace std;
const int MAXN = 150005;

int n,m;

int father[MAXN];

int fa[MAXN];
int ls[MAXN];
int rs[MAXN];
int sta[MAXN];
bool rev[MAXN];

int val[MAXN];
int sum[MAXN];
int all[MAXN];

int find(int x){
    return x==father[x]?x:father[x]=find(father[x]);
}

void up(int x){
    all[x]=all[ls[x]]+all[rs[x]]+sum[x];
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

// 打通当前原树根到x的路径，使其成为一条实链
// 可以认为这个函数就是最关键的函数
void access(int x) {
    x=find(x);
    for(int y=0;x!=0;y=x,x=fa[x]){
        splay(x);
        rs[x]=y;
        up(x);
        fa[x]=find(fa[x]);
    }
}

// 让x变成原树的根，不改变连通方式
// 这个主要是为了access服务,因为access需要的是树根节点
void makeroot(int x) {
    // 保证x和树根在同一个实链上，也就是同一个辅助splay树
    access(x);
    // 提根x
    splay(x);
    // 因为此时x已经是根节点，所以相当于是最顶层了
    // 翻转左右节点
    reverse(x);
}

int findroot(int x) {
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

void split(int x, int y) {
    makeroot(x);
    access(y);
    splay(y);
}

void condense(int x, int root) {
    if (x != 0) {
        father[x] = root;
        sum[root] += sum[x];
        condense(ls[x], root);
        condense(rs[x], root);
    }
}

void link(int x,int y){
    x=find(x);
    y=find(y);
    if(x==y){
        return ;
    }
    makeroot(x);
    if(findroot(y)!=x){
        fa[x]=y;
    }
    else{
        condense(rs[x],x);
        rs[x]=0;
        up(x);
    }
}

void update(int x,int y){
    int delta=y-val[x];
    val[x]=y;
    x=find(x);
    makeroot(x);
    sum[x]+=delta;
    up(x);
}

int query(int x,int y){
    x = find(x);
    y = find(y);
    if (findroot(x) != findroot(y)) {
        return -1;
    }
    split(x, y);
    return all[y];
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>val[i];
        father[i]=i;
        sum[i]=val[i];
        all[i]=val[i];
    }

    for(int i=1;i<=m;i++){
        int op,x,y;
        cin>>op>>x>>y;
        if(op==1){
            link(x,y);
        }
        else if(op==2){
            update(x,y);
        }
        else{
            cout<<query(x,y)<<endl;
        }
    }
    return 0;
}
