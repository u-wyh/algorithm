// 可持久化平衡树，FHQ-Treap实现，不用词频压缩，C++版
// 认为一开始是0版本的树，为空树，实现如下操作，操作一共发生n次
// v 1 x : 基于v版本的树，增加一个x，生成新版本的树
// v 2 x : 基于v版本的树，删除一个x，生成新版本的树
// v 3 x : 基于v版本的树，查询x的排名，生成新版本的树状况=v版本状况
// v 4 x : 基于v版本的树，查询数据中排名为x的数，生成新版本的树状况=v版本状况
// v 5 x : 基于v版本的树，查询x的前驱，生成新版本的树状况=v版本状况
// v 6 x : 基于v版本的树，查询x的后继，生成新版本的树状况=v版本状况
// 不管什么操作，都基于某个v版本，操作完成后得到新版本的树，但v版本不会变化
// 如果x的前驱不存在，返回-2^31 + 1，如果x的后继不存在，返回+2^31 - 1
// 1 <= n <= 5 * 10^5
// -10^9 <= x <= +10^9
// 测试链接 : https://www.luogu.com.cn/problem/P3835
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
//每次结束后 要把ls[0]=rs[0]=0  因为有的题目可能会要求0版本是空树
//并且有的操作直接是在0版本基础上进行
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 500001;
const int MAXM = MAXN * 50;//正常情况下是要开100倍

int cnt = 0;
int head[MAXN];//用于记录每一个版本的头结点是什么
int key[MAXM];
int ls[MAXM];
int rs[MAXM];
int sz[MAXM];
double priority[MAXM];

int copy(int i) {
    ++cnt;
    key[cnt] = key[i];
    ls[cnt] = ls[i];
    rs[cnt] = rs[i];
    sz[cnt] = sz[i];
    priority[cnt] = priority[i];
    return cnt;
}

void up(int i) {
    sz[i] = sz[ls[i]] + sz[rs[i]] + 1;
}

void split(int l, int r, int i, int num) {
    if (i == 0) {
        rs[l] = ls[r] = 0;
    } else {
        i = copy(i);//每次开始时都要新建一个节点
        if (key[i] <= num) {
            rs[l] = i;
            split(i, r, rs[i], num);
        } else {
            ls[r] = i;
            split(l, i, ls[i], num);
        }
        up(i);
    }
}

int merge(int l, int r) {
    if (l == 0 || r == 0) {
        return l + r;
    }
    if (priority[l] >= priority[r]) {
        // 只有真实被用到的才会被拷贝
        l = copy(l);
        rs[l] = merge(rs[l], r);
        up(l);
        return l;
    } else {
        r = copy(r);
        ls[r] = merge(l, ls[r]);
        up(r);
        return r;
    }
}

void add(int v, int i, int num) {
    split(0, 0, i, num);
    int l = rs[0];
    int r = ls[0];
    //每次在merge之前要清空 解决脏数据 普通的fhq不需要  因为这里的0不仅仅是0号节点  他也可以代表0版本的头结点
    ls[0] = rs[0] = 0;
    ++cnt;
    key[cnt] = num;
    sz[cnt] = 1;
    priority[cnt] = (double)rand() / RAND_MAX;
    //为新建的节点编号
    head[v] = merge(merge(l, cnt), r);//记录该版本的头结点
}

void remove(int v, int i, int num) {
    split(0, 0, i, num);
    int lm = rs[0];
    int r = ls[0];
    split(0, 0, lm, num - 1);
    int l = rs[0];
    int m = ls[0];
    ls[0] = rs[0] = 0;//每次要清空 解决脏数据
    head[v] = merge(merge(l, merge(ls[m], rs[m])), r);//记录该版本的头结点
}

int small(int i, int num) {
    if (i == 0) {
        return 0;
    }
    if (key[i] >= num) {
        return small(ls[i], num);
    } else {
        return sz[ls[i]] + 1 + small(rs[i], num);
    }
}

int index(int i, int x) {
    if (sz[ls[i]] >= x) {
        return index(ls[i], x);
    } else if (sz[ls[i]] + 1 < x) {
        return index(rs[i], x - sz[ls[i]] - 1);
    } else {
        return key[i];
    }
}

int pre(int i, int num) {
    if (i == 0) {
        return INT_MIN + 1;
    }
    if (key[i] >= num) {
        return pre(ls[i], num);
    } else {
        return max(key[i], pre(rs[i], num));
    }
}

int post(int i, int num) {
    if (i == 0) {
        return INT_MAX;
    }
    if (key[i] <= num) {
        return post(rs[i], num);
    } else {
        return min(key[i], post(ls[i], num));
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    srand(time(0));
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        int version, op, x;
        cin >> version >> op >> x;
        if (op == 1) {
            add(i, head[version], x);
        } else if (op == 2) {
            remove(i, head[version], x);
        } else {
            //以下操作都是查询操作  不会改变数据结构
            //但是还是要记录一下头结点的编号
            head[i] = head[version];
            if (op == 3) {
                cout << small(head[i], x) + 1 << "\n";
            } else if (op == 4) {
                cout << index(head[i], x) << "\n";
            } else if (op == 5) {
                cout << pre(head[i], x) << "\n";
            } else {
                cout << post(head[i], x) << "\n";
            }
        }
    }
    return 0;
}