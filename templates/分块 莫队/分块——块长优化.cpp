// 由乃打扑克，C++版
// 给定一个长度为n的数组arr，接下来有m条操作，操作类型如下
// 操作 1 l r v : 查询arr[l..r]范围上，第v小的数
// 操作 2 l r v : arr[l..r]范围上每个数加v，v可能是负数
// 1 <= n、m <= 10^5
// -2 * 10^4 <= 数组中的值 <= +2 * 10^4
// 测试链接 : https://www.luogu.com.cn/problem/P5356
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
// 这道题我们可以看出来设置不同的块长可以对时间产生影响
// 这道题的思路就是块内维护一个有序数组  从而加速查询
// 时间复杂度分析：
// 区间加操作  根号n（块间操作）+ （根号n+n*logn）块内操作
// 区间查询操作  log(maxx-minn)*(根号n*log根号n+ 根号n)
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100001;
const int MAXB = 1001;

int n, m;
int arr[MAXN];
int sortv[MAXN];

int blen, bnum;
int bi[MAXN];
int bl[MAXB];
int br[MAXB];
int lazy[MAXB];

//将位置从l~r上的元素加上v   并整合到排序数组中   l~r一定是一个块中的
void innerAdd(int l, int r, int v) {
    for (int i = l; i <= r; i++) {
        arr[i] += v;
    }
    for (int i = bl[bi[l]]; i <= br[bi[l]]; i++) {
        sortv[i] = arr[i];
    }
    sort(sortv + bl[bi[l]], sortv + br[bi[l]] + 1);
}

//将l~r上的元素全部加上v
void add(int l, int r, int v) {
    if (bi[l] == bi[r]) {
        innerAdd(l, r, v);
    } else {
        //处理两个散块
        innerAdd(l, br[bi[l]], v);
        innerAdd(bl[bi[r]], r, v);
        //处理中间的整块
        for (int i = bi[l] + 1; i <= bi[r] - 1; i++) {
            lazy[i] += v;
        }
    }
}

//得到区间最小值
int getMin(int l, int r) {
    int lb = bi[l], rb = bi[r], ans = 10000000;
    if (lb == rb) {
        //本身就是同一块中的   全部遍历
        for (int i = l; i <= r; i++) {
            ans = min(ans, arr[i] + lazy[lb]);
        }
    } else {
        //两个散块
        for (int i = l; i <= br[lb]; i++) {
            ans = min(ans, arr[i] + lazy[lb]);
        }
        for (int i = bl[rb]; i <= r; i++) {
            ans = min(ans, arr[i] + lazy[rb]);
        }
        //中间的整块
        for (int i = lb + 1; i <= rb - 1; i++) {
            ans = min(ans, sortv[bl[i]] + lazy[i]);
        }
    }
    return ans;
}

//得到区间最大值
int getMax(int l, int r) {
    int lb = bi[l], rb = bi[r], ans = -10000000;
    if (lb == rb) {
        for (int i = l; i <= r; i++) {
            ans = max(ans, arr[i] + lazy[lb]);
        }
    } else {
        for (int i = l; i <= br[lb]; i++) {
            ans = max(ans, arr[i] + lazy[lb]);
        }
        for (int i = bl[rb]; i <= r; i++) {
            ans = max(ans, arr[i] + lazy[rb]);
        }
        for (int i = lb + 1; i <= rb - 1; i++) {
            ans = max(ans, sortv[br[i]] + lazy[i]);
        }
    }
    return ans;
}


// 返回第i块内<= v的数字个数
int blockCnt(int i, int v) {
    v -= lazy[i];//减去累加值
    int l = bl[i], r = br[i];
    //处理特殊情况
    if (sortv[l] > v) {
        return 0;
    }
    if (sortv[r] <= v) {
        return r - l + 1;
    }
    int find = l;
    while (l <= r) {
        int m = (l + r) >> 1;
        if (sortv[m] <= v) {
            find = m;
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    return find - bl[i] + 1;
}

// 返回arr[l..r]范围上<= v的数字个数
int getCnt(int l, int r, int v) {
    int lb = bi[l], rb = bi[r], ans = 0;
    if (lb == rb) {
        for (int i = l; i <= r; i++) {
            if (arr[i] + lazy[lb] <= v) {
                ans++;
            }
        }
    } else {
        for (int i = l; i <= br[lb]; i++) {
            if (arr[i] + lazy[lb] <= v) {
                ans++;
            }
        }
        for (int i = bl[rb]; i <= r; i++) {
            if (arr[i] + lazy[rb] <= v) {
                ans++;
            }
        }
        for (int i = lb + 1; i <= rb - 1; i++) {
            ans += blockCnt(i, v);
        }
    }
    return ans;
}

//查询从l到r位置上的第k小
int query(int l, int r, int k) {
    if (k < 1 || k > r - l + 1) {
        return -1;
    }
    int minv = getMin(l, r);
    int maxv = getMax(l, r);
    int ans = -1;
    while (minv <= maxv) {
        int midv = minv + (maxv - minv) / 2;//这里要注意 有可能出错  
        if (getCnt(l, r, midv) >= k) {
            ans = midv;
            maxv = midv - 1;
        } else {
            minv = midv + 1;
        }
    }
    return ans;
}

void prepare() {
    blen = (int)sqrt(n / 2);//块长优化
    bnum = (n + blen - 1) / blen;
    for (int i = 1; i <= n; i++) {
        bi[i] = (i - 1) / blen + 1;
    }
    for (int i = 1; i <= bnum; i++) {
        bl[i] = (i - 1) * blen + 1;
        br[i] = min(i * blen, n);
    }
    for (int i = 1; i <= n; i++) {
        sortv[i] = arr[i];
    }
    for (int i = 1; i <= bnum; i++) {
        sort(sortv + bl[i], sortv + br[i] + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    prepare();
    for (int i = 1, op, l, r, v; i <= m; i++) {
        cin >> op >> l >> r >> v;
        if (op == 1) {
            cout << query(l, r, v) << '\n';
        } else {
            add(l, r, v);
        }
    }
    return 0;
}