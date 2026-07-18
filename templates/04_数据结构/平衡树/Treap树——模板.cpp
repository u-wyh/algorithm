// Treap树的实现(C++版)
// 实现一种结构，支持如下操作，要求单次调用的时间复杂度O(log n)
// 1，增加x，重复加入算多个词频
// 2，删除x，如果有多个，只删掉一个
// 3，查询x的排名，x的排名为，比x小的数的个数+1
// 4，查询数据中排名为x的数
// 5，查询x的前驱，x的前驱为，小于x的数中最大的数，不存在返回整数最小值
// 6，查询x的后继，x的后继为，大于x的数中最小的数，不存在返回整数最大值
// 所有操作的次数 <= 10^5
// -10^7 <= x <= +10^7
// 测试链接 : https://www.luogu.com.cn/problem/P3369
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
// 旋转使"重要节点"（高优先级）靠近根部，形成自然平衡  高优先级越接近根部  
// 那么插入元素的时候  比目前根优先级大的概率实际上不大了  也就是类似于按照他们的key值分流左右
// 从而保证了类似于完全二叉树
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100001;

//treap树按照随机生成的节点权值组织堆结构  不是按照子树大小或者层高
int cnt = 0;
int head = 0;
int key[MAXN];//按照搜索二叉树组织
int key_count[MAXN];
int ls[MAXN];
int rs[MAXN];
int sz[MAXN];
double priority[MAXN];//按照堆组织  随机生成

void up(int i) {
    sz[i] = sz[ls[i]] + sz[rs[i]] + key_count[i];
}

// 只会在删除元素的时候使用左右旋  而且使用起来也很简单  不想avl树那样恶心
int leftRotate(int i) {
    int r = rs[i];
    rs[i] = ls[r];
    ls[r] = i;
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

int add(int i, int num) {
    if (i == 0) {
        key[++cnt] = num;
        key_count[cnt] = sz[cnt] = 1;
        priority[cnt] = static_cast<double>(rand()) / RAND_MAX;
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
    //如果节点的权值不对  那么就开始调整
    if (ls[i] != 0 && priority[ls[i]] > priority[i]) {
        return rightRotate(i);
    }
    if (rs[i] != 0 && priority[rs[i]] > priority[i]) {
        return leftRotate(i);
    }
    return i;
}

void add(int num) {
    head = add(head, num);
}

//查询以i为首的子树上有多少个数字小于num
int small(int i, int num) {
    if (i == 0) {
        return 0;
    }
    if (key[i] >= num) {
        return small(ls[i], num);
    } else {
        return sz[ls[i]] + key_count[i] + small(rs[i], num);
    }
}

int getRank(int num) {
    return small(head, num) + 1;
}

//查询以i为首的子树上排名为x的数字是多少
int index(int i, int x) {
    if (sz[ls[i]] >= x) {
        return index(ls[i], x);
    } else if (sz[ls[i]] + key_count[i] < x) {
        return index(rs[i], x - sz[ls[i]] - key_count[i]);
    }
    return key[i];
}

//查询排名为x的数字是多少
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
                // 选择一个优先级大的孩子顶替上来 自己旋转下去
                if (priority[ls[i]] >= priority[rs[i]]) {
                    i = rightRotate(i);//将原来的头结点下调一层  在右孩子树上删除它
                    rs[i] = remove(rs[i], num);
                } else {
                    i = leftRotate(i);
                    ls[i] = remove(ls[i], num);
                }
            }
        }
    }
    up(i);
    return i;
}

void remove(int num) {
    if (getRank(num) != getRank(num + 1)) {
        head = remove(head, num);
    }
}

void clear() {
    fill(key + 1, key + cnt + 1, 0);
    fill(key_count + 1, key_count + cnt + 1, 0);
    fill(ls + 1, ls + cnt + 1, 0);
    fill(rs + 1, rs + cnt + 1, 0);
    fill(sz + 1, sz + cnt + 1, 0);
    fill(priority + 1, priority + cnt + 1, 0);
    cnt = 0;
    head = 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    srand(time(0));
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