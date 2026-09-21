// https://www.luogu.com.cn/problem/P13661
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m,q;
int a[MAXN];
int b[MAXN];

int rt[MAXN];
long long sum[MAXN];

int fa[MAXN];
int ls[MAXN];
int rs[MAXN];
bool rev[MAXN];
int sta[MAXN];

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
    // 从x开始，一路向上，直至达到树根所在的实链
    for (int y = 0; x != 0; y = x, x = fa[x]) {
        // 先提根，这样的话自己的右边就是应该要断掉的实链
        splay(x);
        // 断开老的实链之后,将之前已经组成的实链接上去
        rs[x] = y;
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

// 建立根到x的实链，根变成辅助splay的顶，返回x所在原树的根
int findroot(int x) {
    access(x);
    splay(x);
    // 注意要找最左的节点,但是不要忘记左右翻转
    // 根节点就是辅助splay中最左的节点
    down(x);
    while (ls[x] != 0) {
        x = ls[x];
        down(x);
    }
    splay(x);
    return x;
}

// 点x到点y的路径暴露出来，这条路径成为一条实链，组成一棵以y为顶部的辅助splay树
void split(int x, int y) {
    // 先让x成为树根
    makeroot(x);
    // 建立xy之间的实链
    access(y);
    // 让一个节点成为辅助splay树的树根
    splay(y);
}

// 原树中连接x和y，如果原本连通则忽略
void link(int x, int y) {
    makeroot(x);
    if (findroot(y) != x) {
        // 这里认为建立的是虚儿子节点  所以不需要up
        fa[x] = y;
    }
}

// 原树中切断x和y之间的直接边，没有直接边则忽略
void cut(int x, int y) {
    makeroot(x);
    if (findroot(y) == x && fa[y] == x && ls[y] == 0 && rs[x] == y) {
        fa[y] = rs[x] = 0;
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>a[i]>>b[i];
    }

    int right=0;
    for(int left=1;left<=m;left++){
        while(right<m){
            int x=a[right+1];
            int y=b[right+1];

            if(findroot(x)==findroot(y)){
                break;
            }
            right++;
            link(x,y);
        }
        rt[left]=right;
        cut(a[left],b[left]);
    }

    for(int i=1;i<=m;i++){
        sum[i]=sum[i-1]+rt[i]-i+1;
    }

    cin>>q;
    while(q--){
        int l,r;
        cin>>l>>r;

        int ll=l,rr=r,pos=l-1;
        while(ll<=rr){
            int mid=(ll+rr)>>1;
            if(rt[mid]<=r){
                pos=mid;
                ll=mid+1;
            }
            else{
                rr=mid-1;
            }
        }

        long long ans=0;
        ans+=sum[pos]-sum[l-1];
        int len=r-pos;
        ans+=1ll*len*(len+1)/2;
        cout<<ans<<endl;
    }
    return 0;
}