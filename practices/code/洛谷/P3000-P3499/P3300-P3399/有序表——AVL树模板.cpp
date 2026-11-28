// https://www.luogu.com.cn/problem/P3369
// 题意：维护一个允许重复元素的整数集合。
// 1. 插入 x。2. 删除一个 x。
// 3. 查询小于 x 的元素个数加 1。
// 4. 查询第 x 小的数。
// 5. 查询 x 的前驱。6. 查询 x 的后继。
// 输入：第一行 n，后 n 行各给操作编号与 x。
// 输出：对 3、4、5、6 操作各输出一个答案。
// 题目保证操作 4、5、6 的答案存在。
// 数据范围：1 <= n <= 10^5，|x| <= 10^7。
// 难度评分：2200（洛谷分级换算）
// 算法标签：AVL树、平衡树
#include <iostream>
#include <algorithm>
#include <climits>
#include <cstring>
using namespace std;
const int MAXN = 100001;

int cnt = 0;//用于赋予节点编号
int head = 0;//整棵树的头结点  这个节点是可以变化的  会根据树的形态调整
int key[MAXN];//节点的权值
int height[MAXN];//节点的树高  左右孩子树高的最大值加上一
int ls[MAXN];
int rs[MAXN];//左右孩子节点编号  注意这个也不是有值之后就保持不变的   会根据树的形态发生相应变化
int key_count[MAXN];//统计这个节点上的数字出现了多少次  词频统计
int sz[MAXN];//以该节点为首的子树上所有数字的词频之和

void up(int i) {
    sz[i] = sz[ls[i]] + sz[rs[i]] + key_count[i];
    height[i] = max(height[ls[i]], height[rs[i]]) + 1;
}

//左右旋 目的把形态不符合AVL树调整成AVL树
//函数的作用是将以i为首的子树左右旋  并返回最终树的头结点
int leftRotate(int i) {
    int r = rs[i];
    rs[i] = ls[r];
    ls[r] = i;
    // 这里要注意更新顺序
    up(i);
    up(r);
    return r;
}

int rightRotate(int i) {
    int l = ls[i];
    ls[i] = rs[l];
    rs[l] = i;
    up(i);
    up(l);
    return l;
}

//将这个节点为首的树调整好  使之不违反AVL树的定义  即左右孩子树高不超过一
//并返回调整好后的头结点
int maintain(int i) {
    int lh = height[ls[i]];
    int rh = height[rs[i]];
    if (lh - rh > 1) {
        if (height[ls[ls[i]]] >= height[rs[ls[i]]]) {
            i = rightRotate(i);
        } else {
            ls[i] = leftRotate(ls[i]);
            i = rightRotate(i);
        }
    } else if (rh - lh > 1) {
        if (height[rs[rs[i]]] >= height[ls[rs[i]]]) {
            i = leftRotate(i);
        } else {
            rs[i] = rightRotate(rs[i]);
            i = leftRotate(i);
        }
    }
    return i;
}

//在以i节点为首的子树上加入一个num  并返回调整过后的头结点
int add(int i, int num) {
    if (i == 0) {
        //表示这是第一次出现
        key[++cnt] = num;
        key_count[cnt] = sz[cnt] = height[cnt] = 1;
        //新建一个节点
        return cnt;
    }
    if (key[i] == num) {
        key_count[i]++;
    } else if (key[i] > num) {
        ls[i] = add(ls[i], num);
    } else {
        rs[i] = add(rs[i], num);
    }
    up(i);
    //每次都要向上汇总  确保数据正确
    return maintain(i);
    //调整树的结构  使之平衡
}

//加入一个值为num的数字
void add(int num) {
    head = add(head, num);
}

//查询以i节点为首的子树上小于num的数字的数量
int getRank(int i, int num) {
    if (i == 0) {
        return 0;
    }
    if (key[i] >= num) {
        return getRank(ls[i], num);
    } else {
        return sz[ls[i]] + key_count[i] + getRank(rs[i], num);
    }
}

//查询num这个数字排名  也就是所有比他小的数字数量加一
int getRank(int num) {
    return getRank(head, num) + 1;
}

int removeMostLeft(int i, int mostLeft) {
    if (i == mostLeft) {
        return rs[i];
    } else {
        ls[i] = removeMostLeft(ls[i], mostLeft);
        up(i);
        return maintain(i);
    }
}

//查询以i节点为首的子树上删去一个num
int remove(int i, int num) {
    if (key[i] < num) {
        rs[i] = remove(rs[i], num);
    } else if (key[i] > num) {
        ls[i] = remove(ls[i], num);
    } else {
        if (key_count[i] > 1) {
            key_count[i]--;
        } else {
            if (ls[i] == 0 && rs[i] == 0) {
                return 0;
            } else if (ls[i] != 0 && rs[i] == 0) {
                i = ls[i];
            } else if (ls[i] == 0 && rs[i] != 0) {
                i = rs[i];
            } else {
                int mostLeft = rs[i];
                while (ls[mostLeft] != 0) {
                    mostLeft = ls[mostLeft];
                }
                rs[i] = removeMostLeft(rs[i], mostLeft);
                ls[mostLeft] = ls[i];
                rs[mostLeft] = rs[i];
                i = mostLeft;
            }
        }
    }
    up(i);
    return maintain(i);
}

//在树上删除数字num
void remove(int num) {
    if (getRank(num) != getRank(num + 1)) {
        //表示这个数字存在
        head = remove(head, num);
    }
}

int index(int i, int x) {
    if (sz[ls[i]] >= x) {
        return index(ls[i], x);
    } else if (sz[ls[i]] + key_count[i] < x) {
        return index(rs[i], x - sz[ls[i]] - key_count[i]);
    }
    return key[i];
}

int index(int x) {
    return index(head, x);
}

int pre(int i, int num) {
    if (i == 0) {
        return INT_MIN;
    }
    if (key[i] >= num) {
        return pre(ls[i], num);
    } else {
        return max(key[i], pre(rs[i], num));
    }
}

int pre(int num) {
    return pre(head, num);
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

int post(int num) {
    return post(head, num);
}

void clear() {
    memset(key + 1, 0, cnt * sizeof(int));
    memset(height + 1, 0, cnt * sizeof(int));
    memset(ls + 1, 0, cnt * sizeof(int));
    memset(rs + 1, 0, cnt * sizeof(int));
    memset(key_count + 1, 0, cnt * sizeof(int));
    memset(sz + 1, 0, cnt * sizeof(int));
    cnt = 0;
    head = 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 1, op, x; i <= n; i++) {
        cin >> op >> x;
        if (op == 1) {
            add(x);
        } else if (op == 2) {
            remove(x);
        } else if (op == 3) {
            cout << getRank(x) << endl;
        } else if (op == 4) {
            cout << index(x) << endl;
        } else if (op == 5) {
            cout << pre(x) << endl;
        } else {
            cout << post(x) << endl;
        }
    }
    clear();
    return 0;
}