// 五彩斑斓的世界，C++版
// 给定一个长度为n的数组arr，一共有m条操作，每条操作类型如下
// 操作 1 l r x : arr[l..r]范围上，所有大于x的数减去x
// 操作 2 l r x : arr[l..r]范围上，查询x出现的次数
// 1 <= n <= 10^6
// 1 <= m <= 5 * 10^5
// 0 <= arr[i]、x <= 10^5
// 测试链接 : https://www.luogu.com.cn/problem/P4117
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000001;
const int MAXM = 500001;
const int MAXV = 100002;

int n, m;
int blen, bnum;

int arr[MAXN];
int op[MAXM];
int ql[MAXM];
int qr[MAXM];
int qx[MAXM];

// maxv代表一个序列块中的最大值
// lazy代表一个序列块中，所有数字需要统计减去多少
// fa代表值域并查集
// pre0代表数组前缀上0的词频统计
// cntv代表一个序列块中每种值的词频统计
int maxv, lazy;
int fa[MAXV];
int pre0[MAXN];
int cntv[MAXV];

// 查询的答案
int ans[MAXM];

// 查询x值变成了什么
int find(int x) {
    if (x != fa[x]) {
        fa[x] = find(fa[x]);
    }
    return fa[x];
}

// 所有x值变成y值
void change(int x, int y) {
    fa[x] = y;
}

// 修改保留在值域并查集，把修改写入arr[l..r]
void down(int l, int r) {
    for (int i = l; i <= r; i++) {
        arr[i] = find(arr[i]);
    }
}

// 全包的时候  我们分为两种情况来讨论   一种是大于最大值的一半  一种是小于最大值的一半
// 这两种情况我们分别是两种方式挂并查集  这样会不会导致死循环呢  比如fa[1]=2  fa[2]=1
// 实际上  只要被包住了  那么这个值以后就不会再出现了
// 其实用笔画一画就知道了 这个lazy线可以保证不会循环
void update(int qi, int l, int r) {
    int jobl = ql[qi], jobr = qr[qi], jobx = qx[qi];
    if (jobx >= maxv - lazy || jobl > r || jobr < l) {
        return;
    }
    if (jobl <= l && r <= jobr) {
        //判断这个问题是否属于这个这个块  即整块
        if ((jobx << 1) <= maxv - lazy) {
            // 判断值和真实的最大值的关系
            for (int v = lazy + 1; v <= lazy + jobx; v++) {
                cntv[v + jobx] += cntv[v];
                cntv[v] = 0;
                change(v, v + jobx);
            }
            lazy += jobx;
        } else {
            for (int v = lazy + jobx + 1; v <= maxv; v++) {
                cntv[v - jobx] += cntv[v];
                cntv[v] = 0;
                change(v, v - jobx);
            }
            for (int v = maxv; v >= 0; v--) {
                if (cntv[v] != 0) {
                    maxv = v;
                    break;
                }
            }
        }
    } else {
        // 先将之前的效果全部落实
        down(l, r);
        for (int i = max(l, jobl); i <= min(r, jobr); i++) {
            if (arr[i] - lazy > jobx) {
                cntv[arr[i]]--;
                arr[i] -= jobx;
                cntv[arr[i]]++;
            }
        }
        // 势能分析 
        for (int v = maxv; v >= 0; v--) {
            if (cntv[v] != 0) {
                maxv = v;
                break;
            }
        }
    }
}

// 这个这个组对这个查询的贡献
void query(int qi, int l, int r) {
    int jobl = ql[qi], jobr = qr[qi], jobx = qx[qi];
    if (jobx == 0 || jobx > maxv - lazy || jobl > r || jobr < l) {
        // 如果是0的查询 那么已经处理过了   如果最大值都比上如今的查询 也没有必要了
        // 或者就是范围不符合
        return;
    }
    if (jobl <= l && r <= jobr) {
        //整块被包含
        ans[qi] += cntv[jobx + lazy];
    } else {
        // 之前可能存在整块修改 将整块修改后的效果落实
        down(l, r);
        for (int i = max(l, jobl); i <= min(r, jobr); i++) {
            if (arr[i] - lazy == jobx) {
                //散块暴力维护   也就是出现在这个块中  但是没有出现整包
                ans[qi]++;
            }
        }
    }
}

// 这里l和r必然是一个组的左右边界
void compute(int l, int r) {
    memset(cntv, 0, sizeof(int) * MAXV);
    maxv = lazy = 0;
    for (int i = l; i <= r; i++) {
        maxv = max(maxv, arr[i]);
        cntv[arr[i]]++;
    }
    for (int v = 0; v <= maxv; v++) {
        fa[v] = v;
    }
    for (int i = 1; i <= m; i++) {
        if (op[i] == 1) {
            update(i, l, r);
        } else {
            query(i, l, r);
        }
    }
}

//0这个数值比较特殊  需要特别维护
void prepare() {
    blen = (int)sqrt(n);
    bnum = (n + blen - 1) / blen;
    for (int i = 1; i <= n; i++) {
        pre0[i] = pre0[i - 1] + (arr[i] == 0 ? 1 : 0);
    }
    for (int i = 1; i <= m; i++) {
        if (op[i] == 2 && qx[i] == 0) {
            ans[i] = pre0[qr[i]] - pre0[ql[i] - 1];
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> op[i] >> ql[i] >> qr[i] >> qx[i];
    }
    prepare();
    for (int i = 1, l, r; i <= bnum; i++) {
        l = (i - 1) * blen + 1;
        r = min(i * blen, n);
        compute(l, r);
    }
    for (int i = 1; i <= m; i++) {
        if (op[i] == 2) {
            cout << ans[i] << '\n';
        }
    }
    return 0;
}