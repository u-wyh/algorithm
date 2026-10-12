// 用途：隐式 FHQ Treap 支持序列区间翻转。
// 时间：单次期望 O(log n)。
// 空间：O(n)。
// 例题：https://www.luogu.com.cn/problem/P3391
// 题意：多次把序列中指定连续区间逆序。
// 思路：按位置分裂出区间，对中段打翻转标记后合并。
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100001;

int head = 0;
int cnt = 0;
int key[MAXN];
int ls[MAXN];
int rs[MAXN];
int sz[MAXN];
double priority[MAXN];
bool rev[MAXN];//懒更新信息
int ans[MAXN];
int ansi;

void up(int i) {
    sz[i] = sz[ls[i]] + sz[rs[i]] + 1;
}

//懒更新的下发
void down(int i) {
    if (rev[i]) {
        swap(ls[i], rs[i]);
        rev[ls[i]] ^= 1;
        rev[rs[i]] ^= 1;
        rev[i] = false;
    }
}

//这道题也是根据排名分裂
//这道题利用的也是位置信息 所以使用排名
//使用中序遍历得到答案
void split(int l, int r, int i, int rank) {
    if (i == 0) {
        rs[l] = ls[r] = 0;
    } else {
        down(i);
        if (sz[ls[i]] + 1 <= rank) {
            rs[l] = i;
            split(i, r, rs[i], rank - sz[ls[i]] - 1);
        } else {
            ls[r] = i;
            split(l, i, ls[i], rank);
        }
        up(i);
    }
}

int merge(int l, int r) {
    if (l == 0 || r == 0) {
        return l + r;
    }
    if (priority[l] >= priority[r]) {
        down(l);//下发懒信息
        rs[l] = merge(rs[l], r);
        up(l);
        return l;
    } else {
        down(r);
        ls[r] = merge(l, ls[r]);
        up(r);
        return r;
    }
}

void inorder(int i) {
    if (i != 0) {
        down(i);
        inorder(ls[i]);
        ans[++ansi] = key[i];
        inorder(rs[i]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    srand(time(0));
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        key[++cnt] = i;
        sz[cnt] = 1;
        priority[cnt] = (double)rand() / RAND_MAX;
        head = merge(head, cnt);
    }
    for (int i = 1, x, y, l, m, lm, r; i <= k; i++) {
        cin >> x >> y;
        split(0, 0, head, y);
        lm = rs[0];//表示<=y的树的头结点
        r = ls[0];//表示>y的树的头结点
        split(0, 0, lm, x - 1);
        l = rs[0];//表示<=x-1的树的头结点
        m = ls[0];//表示>=x的树的头结点
        rev[m] ^= 1;
        head = merge(merge(l, m), r);
    }
    ansi = 0;
    inorder(head);
    for (int i = 1; i <= ansi; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}
