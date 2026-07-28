// LCT模版题，C++版
// 一共n个点，每个点给定点权，一共m条操作，操作类型如下
// 操作 0 x y : 查询点x到点y的路径上，所有点权的异或和，保证x和y连通
// 操作 1 x y : 点x和点y之间增加直接边，如果x和y已经连通则忽略
// 操作 2 x y : 删除点x和点y之间的直接边，如果不存在这条直接边则忽略
// 操作 3 x y : 点x的点权变成y
// 1 <= n <= 10^5
// 1 <= m <= 3 * 10^5
// 测试链接 : https://www.luogu.com.cn/problem/P3690
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100001;

int n, m;
int arr[MAXN];

// 既保存辅助splay内，每个节点的父节点
// 也保存沿虚边向上跳到的原树父节点，认父不认子
int fa[MAXN];
int ls[MAXN];
int rs[MAXN];

// 翻转操作的懒更新标记
bool rev[MAXN];

// 提根之前，先处理沿途的翻转标记，准备一个栈记录沿途节点
int sta[MAXN];

// 本题需要异或和
int xorsum[MAXN];

// 不同题目实现不同的up方法
void up(int x) {
    xorsum[x] = xorsum[ls[x]] ^ xorsum[rs[x]] ^ arr[x];
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
    // 从x开始，一路向上，直至达到树根所在的实链
    for (int y = 0; x != 0; y = x, x = fa[x]) {
        // 先提根，这样的话自己的右边就是应该要断掉的实链
        splay(x);
        // 断开老的实链之后,将之前已经组成的实链接上去
        rs[x] = y;
        // 更新x的信息
        up(x);
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
        up(x);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        xorsum[i] = arr[i];
    }
    for (int i = 1, op, x, y; i <= m; i++) {
        cin >> op >> x >> y;
        if (op == 0) {
            split(x, y);
            cout << xorsum[y] << "\n";
        } else if (op == 1) {
            link(x, y);
        } else if (op == 2) {
            cut(x, y);
        } else {
            splay(x);
            arr[x] = y;
            up(x);
        }
    }
    return 0;
}