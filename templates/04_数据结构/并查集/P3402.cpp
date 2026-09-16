// 可持久化并查集模版题，C++版
// 数字从1到n，一开始每个数字所在的集合只有自己
// 实现如下三种操作，第i条操作发生后，所有数字的状况记为i版本，操作一共发生m次
// 操作 1 x y : 基于上个操作生成的版本，将x的集合与y的集合合并，生成当前的版本
// 操作 2 x   : 拷贝第x号版本的状况，生成当前的版本
// 操作 3 x y : 拷贝上个操作生成的版本，生成当前的版本，查询x和y是否属于一个集合
// 1 <= n <= 10^5
// 1 <= m <= 2 * 10^5
// 测试链接 : https://www.luogu.com.cn/problem/P3402
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
//可持久化并查集不做扁平化的原因是：如果扁平化要修改的东西太多了 
#include <bits/stdc++.h>
using namespace std;
const int MAXM = 200001;
const int MAXT = 8000001;

int n, m;
// rootfa[i] = j，表示father数组，i版本的头节点编号为j
int rootfa[MAXM];
// rootsiz[i] = j，表示siz数组，i版本的头节点编号为j
int rootsiz[MAXM];

// 可持久化father数组和可持久化siz数组，共用一个ls、rs、val
// 因为可持久化时，分配的节点编号不同，所以可以共用
//这个看个人 如果想要两套系统也不是不行
//对于siz数组和fa数组  他们都用的是cnt编号
//两套系统共用一个sz数组
int ls[MAXT];
int rs[MAXT];
int val[MAXT];//其实是fa  sz数组合二为一
int cnt = 0;

// 建立可持久化的father数组
int buildfa(int l, int r) {
    int rt = ++cnt;
    if (l == r) {
        val[rt] = l;//初始是fa信息是自己
    } else {
        int mid = (l + r) / 2;
        ls[rt] = buildfa(l, mid);
        rs[rt] = buildfa(mid + 1, r);
    }
    return rt;
}

// 建立可持久化的siz数组
int buildsiz(int l, int r) {
    int rt = ++cnt;
    if (l == r) {
        val[rt] = 1;//初始时 sz数组是1
    } else {
        int mid = (l + r) / 2;
        ls[rt] = buildsiz(l, mid);
        rs[rt] = buildsiz(mid + 1, r);
    }
    return rt;
}

// 来自讲解157，题目1，修改数组中一个位置的值，生成新版本的数组
// 如果i属于可持久化father数组的节点，那么修改的就是father数组
// 如果i属于可持久化siz数组的节点，那么修改的就是siz数组
int update(int jobi, int jobv, int l, int r, int i) {
    int rt = ++cnt;
    ls[rt] = ls[i];
    rs[rt] = rs[i];
    if (l == r) {
        val[rt] = jobv;
    } else {
        int mid = (l + r) / 2;
        if (jobi <= mid) {
            ls[rt] = update(jobi, jobv, l, mid, ls[rt]);
        } else {
            rs[rt] = update(jobi, jobv, mid + 1, r, rs[rt]);
        }
    }
    return rt;
}

// 来自讲解157，题目1，查询数组中一个位置的值
// 如果i属于可持久化father数组的节点，那么查询的就是father数组
// 如果i属于可持久化siz数组的节点，那么查询的就是siz数组
int query(int jobi, int l, int r, int i) {
    if (l == r) {
        return val[i];
    }
    int mid = (l + r) / 2;
    if (jobi <= mid) {
        return query(jobi, l, mid, ls[i]);
    } else {
        return query(jobi, mid + 1, r, rs[i]);
    }
}

// 基于v版本，查询x的集合头节点，不做扁平化
int find(int x, int v) {
    int fa = query(x, 1, n, rootfa[v]);
    while(x != fa) {
        //表明这个节点和他的父亲节点一样 说明是代表节点
        x = fa;
        fa = query(x, 1, n, rootfa[v]);
    }
    return x;
}

// v版本已经拷贝了v-1版本，合并x所在的集合和y所在的集合，去更新v版本
void Union(int x, int y, int v) {
    int fx = find(x, v);
    int fy = find(y, v);
    if (fx != fy) {
        int xsiz = query(fx, 1, n, rootsiz[v]);
        int ysiz = query(fy, 1, n, rootsiz[v]);
        if (xsiz >= ysiz) {
            rootfa[v] = update(fy, fx, 1, n, rootfa[v]);
            rootsiz[v] = update(fx, xsiz + ysiz, 1, n, rootsiz[v]);
        } else {
            rootfa[v] = update(fx, fy, 1, n, rootfa[v]);
            rootsiz[v] = update(fy, xsiz + ysiz, 1, n, rootsiz[v]);
        }
    }
}

int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    rootfa[0] = buildfa(1, n);
    rootsiz[0] = buildsiz(1, n);
    for (int v = 1, op, x, y; v <= m; v++) {
        cin >> op;
        rootfa[v] = rootfa[v - 1];
        rootsiz[v] = rootsiz[v - 1];//先继承上一个版本的信息
        if (op == 1) {
            cin >> x >> y;
            Union(x, y, v);
        } else if (op == 2) {
            cin >> x;
            rootfa[v] = rootfa[x];
            rootsiz[v] = rootsiz[x];
        } else {
            cin >> x >> y;
            if (find(x, v) == find(y, v)) {
                cout << 1 << "\n";
            } else {
                cout << 0 << "\n";
            }
        }
    }
    return 0;
}